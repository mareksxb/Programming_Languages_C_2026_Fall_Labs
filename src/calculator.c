
#include <stdio.h>

int main(void) {
    double a, b;
    char op;

    printf("Simple Calculator (+ - * /)\\n");
    printf("Enter expression (e.g., 3.5 * 2): ");

    if (scanf("%lf %c %lf", &a, &op, &b) != 3) {
        printf("Input error. Expected format: <number> <op> <number>\\n");
        return 1;
    }

    switch (op) {
        case '+':
            printf("= %.6f\\n", a + b);
            break;
        case '-':
            printf("= %.6f\\n", a - b);
            break;
        case '*':
            printf("= %.6f\\n", a * b);
            break;
        case '/':
            if (b == 0.0) {
                printf("Error: division by zero!\\n");
                return 1;
            }
            printf("= %.6f\\n", a / b);
            break;
        default:
            printf("Unknown operator '%c'. Use + - * /.\\n", op);
            return 1;
    }

    return 0;
}
