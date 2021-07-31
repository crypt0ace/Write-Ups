// gcc -fno-stack-protector pwnme.c -o pwnme
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct member {
	int id;
	char *name;
} member;

void main(int argc, char **argv)
{
	struct member *m1, *m2, *m3;

	m1 = malloc(sizeof(struct member));
	m1->id = 1;
	m1->name = malloc(8);

	m2 = malloc(sizeof(struct member));
	m2->id = 2;
	m2->name = malloc(8);

	strcpy(m1->name, argv[1]);
	strcpy(m2->name, argv[2]);

	exit(0);
}
