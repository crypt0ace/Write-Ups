// gcc pwnme.c -o pwnme
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#define UID 1000
#define GID 1000

int main (int argc, char **argv)
{
	FILE *fp;
	struct stat st;
	char content[255];

	stat(argv[1], &st);

//	printf("%d %d\n", st.st_uid, st.st_gid);
	if ( ((st.st_uid ^ UID) & (st.st_gid ^ GID)) == 0) {
		puts("Access Granted.");

		fp = fopen(argv[1], "r");
		fgets(content, 255, (FILE*)fp);
		fclose(fp);

		printf("%s\n", content);

	} else {
		puts("Access Denied.");
		exit(-1);
	}

	return 0;
}
