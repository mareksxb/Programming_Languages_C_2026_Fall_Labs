// week5_task1_file_io.c
// Name: Nihad  Surname: Abbasov  Student ID: 251ADB076
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
// Writes a few lines to a text file, then reads the file back line by line.
//
// Build: make lab5   Run: ./bin/week5_task1_file_io

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    const char *filename = DEFAULT_FILENAME;
    char line[LINE_LEN];
    int line_count = 0;

    // BONUS: a file name given on the command line replaces the default one.
    if (argc > 1) {
        filename = argv[1];
    }

    // 1. Open the file for writing. "w" creates it, or empties it if it already exists.
    printf("Writing lines to %s...\n", filename);
    fp = fopen(filename, "w");

    // 2. fopen() returns NULL when the file cannot be opened (no permission, bad path...).
    //    Writing through a NULL pointer would crash, so report the reason and stop.
    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // 3. fprintf() works like printf(), but writes into the file instead of the console.
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");

    // 4. fclose() flushes the buffered text to disk, so a failed write shows up here.
    if (fclose(fp) != 0) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // 5. Open the same file again, this time for reading.
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // 6. fgets() reads one line at a time (including its '\n') and returns NULL at end of file.
    printf("Reading contents:\n");
    while (fgets(line, sizeof line, fp) != NULL) {
        printf("%s", line);
        line_count++;
    }

    // 7. Close the file to release it.
    fclose(fp);

    printf("Lines read: %d\n", line_count);

    return EXIT_SUCCESS;
}
