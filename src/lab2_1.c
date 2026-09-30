#include <stdio.h>
int sum_to_n(int r) {
  int sum = 0;
  for (int a = 1; a <= r; a++) {
    sum += a;
  }
  return sum;
}
int main(void) {
  int b;
  printf("Enter b= ");
  if (scanf("%d", &b) != 1) return 1;
  if (b < 1) {
    printf("b must be at least 1\n");
  } else {
    printf("Sum = %d\n", sum_to_n(b));
  }
  return 0;
}