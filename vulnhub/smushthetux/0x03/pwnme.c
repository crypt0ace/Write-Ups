// gcc -mpreferred-stack-boundary=2 -fno-stack-protector pwnme.c -o pwnme
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mystrcpy(const char * text) {
	char buff[512];

        if(strlen(text) > 512){
                puts("Nice Try.");
                exit(-1);
        } else {
		strcpy(buff, text);
        }

	return 0;

}


int main(int argc, char **argv) {

	mystrcpy(argv[1]);

	return 0;
}
