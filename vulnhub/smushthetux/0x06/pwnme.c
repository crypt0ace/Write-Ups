// gcc -fno-stack-protector pwnme.c -o pwnme
#include <stdio.h>
#include <string.h>
int dummy(const char * data) {
	char buff[64];
	if(strlen(data) > 64)
		puts("Bad dog!");
	else {
	sprintf(buff, data);
	puts(buff);

	}

	return 0;
}

int main(int argc, char **argv) {
	dummy(argv[1]);
	return 0;
}

