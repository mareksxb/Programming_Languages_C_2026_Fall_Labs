/*
 * week4_1_dynamic_array.c
 * Author: Nihad Abbasov
 * Student ID: 251ADB076
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    // The size is only known at run time, so the array has to be allocated
    // on the heap. sizeof(int) keeps the byte count correct on any platform.
    arr = malloc(n * sizeof(int));

    // malloc returns NULL when it cannot reserve the memory. Using that
    // pointer would crash the program, so stop here instead.
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        // %d skips spaces and newlines, so the numbers can be typed on one
        // line or on separate lines. scanf returns 1 only if it read a number.
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);  // release the memory first so this exit does not leak
            printf("Invalid input.\n");
            return 1;
        }
    }

    // long long so that adding many large ints cannot overflow the sum.
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    // Cast to double before dividing, otherwise integer division would
    // cut the result (7 and 8 would give 7.00 instead of 7.50).
    double average = (double)sum / n;

    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    // Every successful malloc needs a matching free.
    free(arr);

    return 0;
}
