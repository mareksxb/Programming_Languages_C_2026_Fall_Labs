#include <stdio.h>

#define MAX_N 20

long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(void) {
    int n;

    printf("Enter a non-negative integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input, please enter an integer.\n");
        return 1;
    }

    if (n < 0) {
        printf("Error: factorial is not defined for negative numbers.\n");
        return 1;
    }
    if (n > MAX_N) {
        printf("Error: n is too large (max %d), n! would not fit in a long long.\n", MAX_N);
        return 1;
    }

    printf("%d! = %lld\n", n, factorial(n));

    return 0;
}
