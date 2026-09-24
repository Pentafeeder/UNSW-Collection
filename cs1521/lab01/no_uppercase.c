#include <stdio.h>
#include <ctype.h>

int main(void) {
	int letter = getchar();
	while (letter != EOF) {
		if (letter >= 'A' && letter <= 'Z') {
			letter += 32;
		}
		putchar(letter);
		letter = getchar();
	}
	return 0;
}
