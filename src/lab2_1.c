#include <stdio.h>

int sum_to_n(int n) {
    int sum= 0;

    for(int i= 1; i <=n; i++){
        sum += i;
    }
    return sum;
}

int main(void) {
    int n;

    printf("Enter a positive integer n: ");
    scanf("%d", &n);
    if (n < 1){
        printf("error: n must be bigger than 0.\n");
    }
    else{
        printf("sum from 1 to %d = %d\n", n, sum_to_n(n));
    }

    return 0;
}
