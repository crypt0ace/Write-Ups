// gcc pwnme.c -o pwnme
#include <stdio.h>

int main( void ) {
	puts("Content of /home/tux:");
	system("ls -l /home/tux");

	return 0;
}
