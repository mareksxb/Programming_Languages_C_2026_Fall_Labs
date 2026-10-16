#include <stdio.h>
long long factorial(int r) {
  long long fact = 1;
  for (int a = 1; a <= r; a++) {
    fact *= a;
  }
  return fact;
}
int main(void) {
  int b;
  printf("Enter b: ");
  scanf("%d", &b);
  if (b < 0) {
    printf("b cannot be negative\n");
  } else {
    printf("Factorial = %lld\n", factorial(b));
  }
  return 0;
}