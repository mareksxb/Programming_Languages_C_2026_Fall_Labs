#include <stdio.h>
int is_prime(int r) {
    if (r < 2) return 0;
    for (int a = 2; a < r; a++) {
        if (r % a == 0) return 0;}
    return 1;
}
int main(void) {
    int b;
    printf("Enter r: ");
    if (scanf("%d", &b) != 1) return 1;
    if (b < 2) {
        printf("b must be at least 2\n");}
     else {
        printf("Primes: ");
        for (int c = 2; c <= b; c++) {
            if (is_prime(c)) 
            printf("%d\n ", c);}}
    return 0;
}