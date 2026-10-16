#include <stdio.h>
#include <stdlib.h>
int main() {
  int n;
  int* arr = NULL;
  int sum = 0;
  float average = 0.0;

  printf("Enter number of elements: ");

  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  arr = (int*)malloc(n * sizeof(int));

  if (arr == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("Invalid input.\n");
      free(arr);
      return 1;
    }
    sum += arr[i];
  }

  average = (float)sum / n;

  printf("Sum = %d\n", sum);
  printf("Average = %.2f\n", average);

  free(arr);

  return 0;
}