#include <stdio.h>
#include <string.h>
struct Student {
    char name[50];
    int ID;
    float Grade;
};
int main() {
    struct Student s1;
    struct Student s2;
    strcpy(s1.name, "Alice Johnson");
    s1.ID = 1001;
    s1.Grade = 9.1;
    strcpy(s2.name, "Bob Smith");
    s2.ID = 1002;
    s2.Grade = 8.7;
    printf("Student 1: %s, ID: %d, Grade: %.1f\n", s1.name, s1.ID, s1.Grade);
    printf("Student 2: %s, ID: %d, Grade: %.1f\n", s2.name, s2.ID, s2.Grade);
    return 0;
}
