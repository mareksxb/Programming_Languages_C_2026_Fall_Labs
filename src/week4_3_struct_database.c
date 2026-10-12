/*
 * week4_3_struct_database.c
 * Author: Nihad Abbasov
 * Student ID: 251ADB076
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Same record type as in Task 2: one struct holds everything about a student.
struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    int n;
    struct Student *students = NULL;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    // The number of records is only known at run time, so one block big
    // enough for n structs is allocated on the heap.
    students = malloc(n * sizeof(struct Student));

    // malloc returns NULL when it cannot reserve the memory. Using that
    // pointer would crash the program, so stop here instead.
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for student %d: ", i + 1);
        // %49s leaves room for the '\0' in name[50], so a long name cannot
        // overflow the buffer. scanf returns how many fields it filled, so
        // anything less than 3 means the input was wrong or missing.
        if (scanf("%49s %d %f", students[i].name, &students[i].id,
                  &students[i].grade) != 3) {
            free(students);  // release the memory first so this exit does not leak
            printf("Invalid input.\n");
            return 1;
        }
    }

    // Empty line separates the input prompts from the table.
    printf("\n");
    printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
    for (int i = 0; i < n; i++) {
        printf("%-6d %-11s %.1f\n",
               students[i].id, students[i].name, students[i].grade);
    }

    // One malloc for the whole array, so one free releases all records.
    free(students);

    return 0;
}
