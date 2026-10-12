/*
 * week4_2_struct_student.c
 * Author: Nihad Abbasov
 * Student ID: 251ADB076
 * Description:
 *   Demonstrates defining and using a struct in C.
 *   Define a 'Student' struct with name, id and grade, create two
 *   instances with the values from the instructions, and print them.
 *
 *   This program reads no input. Output must match the format in the
 *   Week 4 instructions exactly (it is checked by the autograder).
 */

#include <stdio.h>
#include <string.h>

// A struct groups the data that belongs to one student into a single type,
// so name, id and grade always travel together.
struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    struct Student student1;
    struct Student student2;

    // Arrays cannot be assigned with '=' in C, so the name is copied
    // into the char array with strcpy. The other fields use the dot operator.
    strcpy(student1.name, "Alice Johnson");
    student1.id = 1001;
    student1.grade = 9.1f;

    strcpy(student2.name, "Bob Smith");
    student2.id = 1002;
    student2.grade = 8.7f;

    printf("Student 1: %s, ID: %d, Grade: %.1f\n",
           student1.name, student1.id, student1.grade);
    printf("Student 2: %s, ID: %d, Grade: %.1f\n",
           student2.name, student2.id, student2.grade);

    return 0;
}
