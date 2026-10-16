// week5_task4_struct_binary_io.c   (BONUS)
// Name: __Reshma______  Surname: __Rajendran______  Student ID:
// __251ADB037______
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <string.h>

typedef struct Student {
  char name[50];
  int age;
  float gpa;
} Student;

int save_student_binary(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "wb");

  if (fp == NULL) {
    return -1;
  }

  if (fwrite(s, sizeof(Student), 1, fp) != 1) {
    fclose(fp);
    return -1;
  }

  if (fclose(fp) != 0) {
    return -1;
  }

  return 0;
}

int load_student_binary(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "rb");

  if (fp == NULL) {
    return -1;
  }

  if (fread(out, sizeof(Student), 1, fp) != 1) {
    fclose(fp);
    return -1;
  }

  if (fclose(fp) != 0) {
    return -1;
  }

  return 0;
}

long file_size(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  long size;

  if (fp == NULL) {
    return -1;
  }

  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return -1;
  }

  size = ftell(fp);

  if (size == -1L) {
    fclose(fp);
    return -1;
  }

  if (fclose(fp) != 0) {
    return -1;
  }

  return size;
}

int save_student_text(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "w");

  if (fp == NULL) {
    return -1;
  }

  if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
    fclose(fp);
    return -1;
  }

  if (fclose(fp) != 0) {
    return -1;
  }

  return 0;
}

int main(void) {
  Student original = {0};
  Student loaded = {0};
  long text_size;
  long binary_size;

  strcpy(original.name, "Alice");
  original.age = 21;
  original.gpa = 3.75f;

  printf("Saving student in binary format...\n");

  if (save_student_binary(&original, "student.bin") == -1) {
    fprintf(stderr, "Error saving binary file.\n");
    return 1;
  }

  if (save_student_text(&original, "student.txt") == -1) {
    fprintf(stderr, "Error saving text file.\n");
    return 1;
  }

  printf("Loading student from binary file...\n");

  if (load_student_binary("student.bin", &loaded) == -1) {
    fprintf(stderr, "Error loading binary file.\n");
    return 1;
  }

  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  text_size = file_size("student.txt");
  binary_size = file_size("student.bin");

  if (text_size == -1 || binary_size == -1) {
    fprintf(stderr, "Error checking file sizes.\n");
    return 1;
  }

  printf("Text file size: %ld bytes\n", text_size);
  printf("Binary file size: %ld bytes\n", binary_size);
  return 0;
}