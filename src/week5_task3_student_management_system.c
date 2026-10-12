// week5_task3_student_management_system.c
// Name: Nihad  Surname: Abbasov  Student ID: 251ADB076
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// Keeps the students in an array, loads them from students.txt at startup
// and saves them back to the file when the program exits.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  load_students(Student arr[], int max);          // returns number of records loaded
int  save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    // Load the records saved by an earlier run (0 on the very first run).
    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;                         // end of input: save and exit instead of looping forever
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;   // non-numbers become invalid
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;
            case 2:
                add_student(students, &count);
                break;
            case 3:
                // Write everything back so the data is still there on the next run.
                if (save_students(students, count) != 0) {
                    fprintf(stderr, "Error: could not save data to %s\n", DATA_FILE);
                }
                printf("Data saved. Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input (EOF).
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        // Line was longer than the buffer: discard the rest of it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}

// Loads up to max records from DATA_FILE into arr and returns how many were loaded.
int load_students(Student arr[], int max) {
    if (arr == NULL || max <= 0) {
        return 0;
    }

    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        // No file yet (first run) is not an error: start with an empty list.
        return 0;
    }

    char line[LINE_LEN];
    int count = 0;

    // Checking count < max first means we stop reading as soon as the array is full.
    while (count < max && fgets(line, sizeof line, fp) != NULL) {
        // No '\n' and not at the end of the file: the line did not fit in the buffer.
        // A valid record is never that long, so skip the rest of this line.
        if (strchr(line, '\n') == NULL && !feof(fp)) {
            int c;
            while ((c = fgetc(fp)) != '\n' && c != EOF) { }
            continue;
        }

        // %49[^,] reads the name up to the first comma (spaces allowed, at most 49 chars).
        // Only lines with all three fields are kept; blank or malformed lines are skipped.
        Student s;
        if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3) {
            arr[count] = s;
            count++;
        }
    }

    fclose(fp);
    return count;
}

// Overwrites DATA_FILE with all current records, one "name,id,gpa" line each.
int save_students(const Student arr[], int count) {
    if (count < 0 || (arr == NULL && count > 0)) {
        return -1;
    }

    // "w" empties the file first, so afterwards it holds exactly the records in the array.
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }

    // ferror() tells whether any write failed; fclose() flushes the buffer and can fail too.
    int write_error = ferror(fp);
    if (fclose(fp) != 0 || write_error) {
        return -1;
    }
    return 0;
}

// Asks for name, ID and GPA, checks them and adds the student to the end of arr.
void add_student(Student arr[], int *count) {
    char name[NAME_LEN];        // read_line() shortens a longer name so it fits the struct field
    char id_text[LINE_LEN];
    char gpa_text[LINE_LEN];
    char *end;

    if (arr == NULL || count == NULL) {
        return;
    }

    // Check the limit first, so we never write past the end of the array.
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    // read_line() returns -1 at end of input: then there is nothing to add.
    if (read_line("Enter name: ", name, sizeof name) != 0 ||
        read_line("Enter ID: ", id_text, sizeof id_text) != 0 ||
        read_line("Enter GPA: ", gpa_text, sizeof gpa_text) != 0) {
        return;
    }

    // In the file the fields are separated by commas, so the name must not be
    // empty (or only spaces) and must not contain a comma.
    int name_ok = name[strspn(name, " \t")] != '\0' && strchr(name, ',') == NULL;

    // strtol() has to use up the whole text, otherwise it was not a plain number
    // ("abc", "12x"). Numbers that do not fit into an int are rejected too.
    errno = 0;
    long id = strtol(id_text, &end, 10);
    int id_ok = end != id_text && *end == '\0' && errno == 0 && id >= INT_MIN && id <= INT_MAX;

    // Same check for the GPA, plus the 0.0-4.0 range. Written as "gpa >= 0 && gpa <= 4"
    // the test is also false for "nan", so that is rejected as well.
    float gpa = strtof(gpa_text, &end);
    int gpa_ok = end != gpa_text && *end == '\0' && gpa >= 0.0f && gpa <= 4.0f;

    if (!name_ok || !id_ok || !gpa_ok) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // The name fits: read_line() limited it to NAME_LEN - 1 characters.
    strcpy(arr[*count].name, name);
    arr[*count].id = (int)id;
    arr[*count].gpa = gpa;
    (*count)++;

    printf("Student added successfully!\n");
}

// Prints all students as a table, or a message when there are none.
void list_students(const Student arr[], int count) {
    if (arr == NULL || count <= 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}
