// gcc -fno-stack-protector pwnme.c -o pwnme
#include <stdio.h>
#include <stdint.h>
#define MAX_LEN 1024

struct foo {
	uint16_t len;
	char content[MAX_LEN];
} foo;

int foo_cpy(FILE *fp) {
	struct foo bar;

	fread(&bar.len, sizeof(uint16_t), 1, fp);
	if ((bar.len+1 & 0xff) > MAX_LEN) {
		puts("Bad dog!");
	} else {
		puts("Good.");
		fseek(fp, 2, SEEK_SET);
		fread(&bar.content, 1, bar.len, fp);
		printf("%s\n", bar.content);
	}

	fclose(fp);

	return 0;
}

int main(int argc, char **argv) {
	FILE * fp;
	fp = fopen(argv[1], "r");
	foo_cpy(fp);
	return 0;
}
