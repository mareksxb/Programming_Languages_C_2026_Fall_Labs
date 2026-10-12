// week5_task2_struct_save_load.c
// Name: Nihad  Surname: Abbasov  Student ID: 251ADB076
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
// Saves one Student record to a text file and loads it back.
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int save_student(const Student *s, const char *filename);  // 0 on success, -1 on error
int load_student(const char *filename, Student *out);      // 0 on success, -1 on error

int main(void) {
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *filename = "student.txt";

    // The functions only report success or failure; main() decides what to do about it.
    printf("Saving student to file...\n");
    if (save_student(&s1, filename) != 0) {
        fprintf(stderr, "Error: could not save student to %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("Loading student from file...\n");
    if (load_student(filename, &loaded) != 0) {
        fprintf(stderr, "Error: could not load student from %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    return EXIT_SUCCESS;
}

// Writes the student as one line "name age gpa", e.g. "Alice 21 3.75".
int save_student(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    // "w" creates the file, or overwrites an older version of it.
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;  // no exit() here: the caller decides how to handle the error
    }

    fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);

    // ferror() tells whether the write failed; fclose() flushes the buffer and can fail too.
    int write_error = ferror(fp);
    if (fclose(fp) != 0 || write_error) {
        return -1;
    }
    return 0;
}

// Reads one "name age gpa" record from the file into *out.
int load_student(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    // %49s stops after 49 characters, so a long name cannot overflow name[50]
    // (the last byte is needed for '\0'). fscanf() returns how many fields it filled.
    int fields = fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);

    fclose(fp);  // close the file whether the read worked or not

    return (fields == 3) ? 0 : -1;
}
