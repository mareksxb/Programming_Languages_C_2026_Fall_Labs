#include <stdio.h>

long long factorial(int n);

int main(void) {
    int n = 0;

    printf("Enter a non-negative integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    if (n < 0) {
        printf("Error: n must be greater than or equal to 0.\n");
        return 1;
    }

    long long result = factorial(n);
    printf("Factorial of %d is: %lld\n", n, result);

    return 0;
}


long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}