#include <stdio.h>
#include <string.h>
#define MAX 1024
int main(void) {
	char string[MAX];
	
	
	while (fgets(string, MAX, stdin) != NULL) {
		int size = strlen(string);
		if (size % 2 == 0) {
			fputs(string, stdout);
		}
	}

	return 0;
}
