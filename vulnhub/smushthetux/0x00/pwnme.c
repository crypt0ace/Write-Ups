// gcc pwnme.c -o pwnme -fno-stack-protector
#include <stdio.h>
#include <string.h>

void vuln( char * arg ) {
	char buf[256];
	strcpy(buf, arg);
}

int main(int argc, char **argv) {
	printf("Val: %s\n", argv[1]);
	vuln(argv[1]);

	return 0;
}
