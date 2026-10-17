#include <stdio.h>


int is_prime(int n);

int main(void) {
    int n = 0;

    printf("Enter an integer n (>= 2): ");
    if (scanf("%d", &n) != 1) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    if (n < 2) {
        printf("Error: n must be greater than or equal to 2.\n");
        return 1;
    }

    printf("Prime numbers up to %d:\n", n);
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}


int is_prime(int n) {
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1; 
}