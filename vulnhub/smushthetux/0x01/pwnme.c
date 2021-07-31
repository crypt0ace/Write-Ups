// gcc pwnme.c -o pwnme -fno-stack-protector
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char text[1024];
	scanf("%1024s", text);
	printf(text);

	exit(0);
}
