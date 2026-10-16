// week5_task3_student_management_system.c
// Name: __Reshma______  Surname: __Rajendran______  Student ID:
// 251ADB037________
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILENAME "students.txt"

typedef struct {
  char name[50];
  int id;
  float gpa;
} Student;

void read_line(char* buf, int len) {
  if (fgets(buf, len, stdin) != NULL) {
    size_t l = strlen(buf);
    if (l > 0 && buf[l - 1] == '\n') {
      buf[l - 1] = '\0';
    }
  } else {
    if (len > 0) buf[0] = '\0';
  }
}

int load_students(Student arr[], int max) {
  FILE* file = fopen(FILENAME, "r");
  if (file == NULL) return 0;

  char line[150];
  int count = 0;

  while (count < max && fgets(line, sizeof(line), file) != NULL) {
    if (line[0] == '\n' || line[0] == '\0') continue;
    Student s = {0};
    int parsed = sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa);
    if (parsed == 3) {
      arr[count++] = s;
    }
  }
  fclose(file);
  return count;
}

int save_students(const Student arr[], int count) {
  FILE* file = fopen(FILENAME, "w");
  if (file == NULL) return -1;

  for (int i = 0; i < count; i++) {
    fprintf(file, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
  }
  fclose(file);
  return 0;
}

void add_student(Student arr[], int* count) {
  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  char name_buf[100], id_buf[50], gpa_buf[50];

  printf("Enter name: ");
  read_line(name_buf, sizeof(name_buf));
  printf("Enter ID: ");
  read_line(id_buf, sizeof(id_buf));
  printf("Enter GPA: ");
  read_line(gpa_buf, sizeof(gpa_buf));

  if (strlen(name_buf) == 0 || strlen(name_buf) >= 50 ||
      strchr(name_buf, ',') != NULL) {
    printf("Invalid input. Student not added.\n");
    return;
  }
  if (strlen(id_buf) == 0) {
    printf("Invalid input. Student not added.\n");
    return;
  }
  for (size_t i = 0; i < strlen(id_buf); i++) {
    if (!isdigit((unsigned char)id_buf[i])) {
      printf("Invalid input. Student not added.\n");
      return;
    }
  }
  int id = atoi(id_buf);

  char* endptr;
  float gpa = strtof(gpa_buf, &endptr);
  if (endptr == gpa_buf || *endptr != '\0' || gpa < 0.0f || gpa > 4.0f) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  strcpy(arr[*count].name, name_buf);
  arr[*count].id = id;
  arr[*count].gpa = gpa;
  (*count)++;
  printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }
  printf("ID    Name                 GPA\n");
  for (int i = 0; i < count; i++) {
    printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}

int main(void) {
  Student students[MAX_STUDENTS];
  int student_count = load_students(students, MAX_STUDENTS);
  printf("Loaded %d student(s) from %s\n", student_count, FILENAME);

  char choice_buf[50];
  while (1) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");
    printf("Select an option: ");

    read_line(choice_buf, sizeof(choice_buf));
    int choice = atoi(choice_buf);

    if (choice == 1) {
      list_students(students, student_count);
    } else if (choice == 2) {
      add_student(students, &student_count);
    } else if (choice == 3 || choice_buf[0] == '\0') {
      if (save_students(students, student_count) == 0) {
        printf("Data saved. Goodbye!\n");
      } else {
        perror("Error saving data");
      }
      break;
    } else {
      printf("Invalid option. Please try again.\n");
    }
  }
  return EXIT_SUCCESS;
}