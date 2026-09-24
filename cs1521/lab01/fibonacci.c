#include <stdio.h>
#include <stdlib.h>

#define SERIES_MAX 30

int fib(int n);

int main(void) {
    int num;
    while (scanf("%d ", &num) == 1) {
        int result = fib(num);
        printf("%d\n", result);
    }
    return EXIT_SUCCESS;
}

int fib(int n) {
    if (n == 0) {
        return 0;
    } 
    
    if (n == 1) {
        return 1;
    } 
    
    return fib(n - 2) + fib(n - 1);
}