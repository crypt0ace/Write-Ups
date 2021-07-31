// gcc -fno-stack-protector pwnme.c -o pwnme
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char **argv) {
	char *p1, *p2;

	p1 = malloc(64);
	p2 = malloc(64);

	strcpy(p1, argv[1]);

	free(p2);
	free(p1);

	exit(0);
}

