#include <stdio.h>

int sum_to_n(int n);

int main(void) {
    int n = 0;

    printf("Enter a positive integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    if (n < 1) {
        printf("Error: n must be greater than or equal to 1.\n");
        return 1;
    }

    int result = sum_to_n(n);
    printf("Sum from 1 to %d is: %d\n", n, result);

    return 0;
}

int sum_to_n(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}