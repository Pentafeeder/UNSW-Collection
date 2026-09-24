#include <stdio.h>

int main(int argc, char *argv[]) {
	(void) argc, (void) argv; // keep the compiler quiet, should be removed
	printf("Program name: %s\n", argv[0]);
	if (argc == 1) {
		printf("There are no other arguments\n");
	} else if (argc > 1) {
		printf("There are %d arguments:\n", argc - 1);
		int counter = 1;
		while (counter < argc) {
			printf("\tArgument %d is \"%s\"\n", counter, argv[counter]);
			counter++;
		}
	}
	return 0;
}
