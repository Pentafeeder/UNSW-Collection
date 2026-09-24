#include <stdio.h>
#include <stdlib.h>

void collatz_chain(int n);

int main(int argc, char *argv[])
{
	(void) argc, (void) argv; // keep the compiler quiet, should be removed
	collatz_chain(atoi(argv[1]));
	return EXIT_SUCCESS;
}

void collatz_chain(int n) {
	printf("%d\n", n);
	if (n == 1) {
	} else if (n % 2 == 1) {
		collatz_chain(n * 3 + 1);
	} else if (n % 2 == 0) {
		collatz_chain(n / 2);
	}
}