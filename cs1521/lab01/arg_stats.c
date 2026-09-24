#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	(void) argc, (void) argv; // keep the compiler quiet, should be removed
	int first_arg = atoi(argv[1]);
	int min = first_arg;
	int max = first_arg;
	int sum = 0;
	int prod = first_arg;
	int mean = 0;
	
	for (int counter = 1; counter < argc; counter++) {
		int value = atoi(argv[counter]);
		sum += value;
		if (value < min) {
			min = value;
		}
		
		if (value > max) {
			max = value;
		}

		if (counter != 1) {
			prod *= value;
		}
	}

	mean = sum / (argc - 1);

	printf("MIN:  %d\n", min);
	printf("MAX:  %d\n", max);
	printf("SUM:  %d\n", sum);
	printf("PROD: %d\n", prod);
	printf("MEAN: %d\n", mean);
	return 0;
}
