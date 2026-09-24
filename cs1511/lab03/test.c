#include <stdio.h>

int main() {
    int n, row, col;
    printf("Enter size: ");
    scanf("%d", &n);
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (row == col || row == n - col - 1) {
                printf("*");
            } else if (row % (n / 2) == col % ((n / 2))- 4 && col < n/2 + 1) {
                printf("*");
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
    return 0;
}