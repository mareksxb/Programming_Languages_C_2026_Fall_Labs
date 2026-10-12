#include <stdio.h>

#define MAX_N 65535

int sum_to_n(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main(void) {
    int n;

    printf("Enter a positive integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input, please enter an integer.\n");
        return 1;
    }

    if (n < 1) {
        printf("Error: n must be a positive integer (n >= 1).\n");
        return 1;
    }
    if (n > MAX_N) {
        printf("Error: n is too large (max %d), the sum would not fit in an int.\n", MAX_N);
        return 1;
    }

    printf("Sum of 1..%d = %d\n", n, sum_to_n(n));

    return 0;
}
