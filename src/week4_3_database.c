#include <stdio.h>
#include <stdlib.h>
struct Student {
  char name[50];
  int ID;
  float Grade;
};
int main() {
  int n;
  struct Student* students = NULL;
  printf("Enter number of students: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid number.\n");
    return 1;
  }
  students = (struct Student*)malloc(n * sizeof(struct Student));
  if (students == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }
  for (int i = 0; i < n; i++) {
    printf("Enter data for student %d: ", i + 1);
    if (scanf("%49s %d %f", students[i].name, &students[i].ID,
              &students[i].Grade) != 3) {
      printf("Invalid input.\n");
      free(students);
      return 1;
    }
  }
  printf("\n");
  printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
  for (int i = 0; i < n; i++) {
    printf("%-6d %-11s %.1f\n", students[i].ID, students[i].name,
           students[i].Grade);
  }
  free(students);
  return 0;
}