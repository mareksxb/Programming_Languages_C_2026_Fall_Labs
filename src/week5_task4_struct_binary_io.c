// week5_task4_struct_binary_io.c   (BONUS)
// Name: Nihad  Surname: Abbasov  Student ID: 251ADB076
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

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
int  save_student_binary(const Student *s, const char *filename);  // 0 on success, -1 on error
int  load_student_binary(const char *filename, Student *out);      // 0 on success, -1 on error
long file_size(const char *filename);                              // bytes, -1 on error

// Helper for the size comparison: same text format as in Task 2 ("name age gpa").
static int save_student_text(const Student *s, const char *filename);

int main(void) {
    Student s1 = {0};          // zero-initialised so unused name bytes are not garbage on disk
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s1, bin_file) != 0) {
        fprintf(stderr, "Error: could not save student to %s\n", bin_file);
        return EXIT_FAILURE;
    }

    // The same record as text, only to compare the two file sizes.
    if (save_student_text(&s1, txt_file) != 0) {
        fprintf(stderr, "Error: could not save student to %s\n", txt_file);
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");
    if (load_student_binary(bin_file, &loaded) != 0) {
        fprintf(stderr, "Error: could not load student from %s\n", bin_file);
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    long txt_size = file_size(txt_file);
    long bin_size = file_size(bin_file);
    if (txt_size < 0 || bin_size < 0) {
        fprintf(stderr, "Error: could not get the file sizes\n");
        return EXIT_FAILURE;
    }

    // The text file holds only the characters "Alice 21 3.75\n". The binary file is
    // always sizeof(Student): the whole 50-byte name array, padding, the int and the float.
    printf("Text file size: %ld bytes\n", txt_size);
    printf("Binary file size: %ld bytes\n", bin_size);

    return EXIT_SUCCESS;
}

// Writes the struct to the file exactly as it is stored in memory.
int save_student_binary(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    // "wb" = write in binary mode, so the bytes are stored without any text conversion.
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }

    // One item of sizeof(Student) bytes; fwrite() returns how many items it wrote.
    size_t items = fwrite(s, sizeof(Student), 1, fp);

    // fclose() flushes the buffer, so a failed write can also show up here.
    if (fclose(fp) != 0 || items != 1) {
        return -1;
    }
    return 0;
}

// Reads one struct back from a file written by save_student_binary().
int load_student_binary(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // fread() returns 0 items if the file is shorter than one whole struct.
    size_t items = fread(out, sizeof(Student), 1, fp);

    fclose(fp);  // close the file whether the read worked or not

    return (items == 1) ? 0 : -1;
}

// Returns the size of the file in bytes, or -1 if it cannot be determined.
long file_size(const char *filename) {
    if (filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // After jumping to the end, the current position equals the number of bytes.
    long size = -1;
    if (fseek(fp, 0, SEEK_END) == 0) {
        size = ftell(fp);  // ftell() itself returns -1 on error
    }

    fclose(fp);
    return size;
}

// Saves the record as one text line, the same format as save_student() in Task 2.
static int save_student_text(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);

    int write_error = ferror(fp);
    if (fclose(fp) != 0 || write_error) {
        return -1;
    }
    return 0;
}
