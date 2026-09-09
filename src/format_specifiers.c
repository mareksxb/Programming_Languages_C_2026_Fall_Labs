
#include <stdio.h>
#include <string.h>

int main(void) {
    int i = -42;
    unsigned int u = 42u;
    int hex = 255;
    double f = 1234.56789;
    char c = 'A';
    char word[64];
    char line[128];

    printf("=== printf demo ===\\n");
    printf("int (%%d): %d\\n", i);
    printf("unsigned (%%u): %u\\n", u);
    printf("hex (%%x): %x\\n", hex);
    printf("octal (%%o): %o\\n", hex);
    printf("char (%%c): %c\\n", c);
    printf("float default (%%f): %f\\n", f);
    printf("float scientific (%%e): %e\\n", f);
    printf("float 2 decimals (%%.2f): %.2f\\n", f);
    printf("width/pad (%%10.2f): %10.2f\\n", f);
    printf("left align (%%-10.2f): %-10.2f<end>\\n", f);

    printf("\\nEnter a single word (no spaces): ");
    if (scanf("%63s", word) == 1) {
        printf("You typed: '%s'\\n", word);
    } else {
        printf("Failed to read word.\\n");
        return 1;
    }

    // consume the leftover newline from previous input, if any
    int ch;
    while ((ch = getchar()) != '\\n' && ch != EOF) { /* discard */ }

    printf("Enter a full line (may contain spaces): ");
    if (fgets(line, sizeof(line), stdin) != NULL) {
        // remove trailing newline if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\\n') {
            line[len - 1] = '\\0';
        }
        printf("Line: \"%s\" (length=%zu)\\n", line, strlen(line));
    } else {
        printf("Failed to read line.\\n");
        return 1;
    }

    // scanf with validation example
    int n;
    printf("Enter an integer: ");
    if (scanf("%d", &n) == 1) {
        printf("You entered %d (hex=%x, octal=%o)\\n", n, n, n);
    } else {
        printf("That was not an integer.\\n");
    }

    return 0;
}
