#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

void display_file(const char* filename, int number_lines, int show_ends, int squeeze_blank, int show_tabs) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char buffer[BUFFER_SIZE];
    int line_number = 1;
    int blank_line_count = 0;
    int prev_blank = 0;
    int prev_newline = 0;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (squeeze_blank && buffer[0] == '\n') {
            if (prev_blank) {
                continue;
            } else {
                prev_blank = 1;
            }
        } else {
            prev_blank = 0;
        }

        if (number_lines) {
            printf("%6d  ", line_number);
        }

        for (int i = 0; buffer[i] != '\0'; i++) {
            if (show_tabs && buffer[i] == '\t') {
                printf("^I");
            } else {
                putchar(buffer[i]);
            }
        }

        if (show_ends && buffer[strlen(buffer) - 1] != '\n') {
            printf("$");
        }

        line_number++;
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    int number_lines = 0;
    int show_ends = 0;
    int squeeze_blank = 0;
    int show_tabs = 0;

    int opt;
    while ((opt = getopt(argc, argv, "nsetT")) != -1) {
        switch (opt) {
            case 'n':
                number_lines = 1;
                break;
            case 's':
                squeeze_blank = 1;
                break;
            case 'e':
                show_ends = 1;
                break;
            case 't':
                show_tabs = 1;
                break;
            case 'T':
                show_tabs = 0;
                break;
            default:
                fprintf(stderr, "Usage: cat [-n] [-s] [-e] [-t|-T] [file...]\n");
                return 1;
        }
    }

    if (optind == argc) {
        // No files specified, read from stdin
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
            printf("%s", buffer);
        }
    } else {
        // Read files
        for (int i = optind; i < argc; i++) {
            display_file(argv[i], number_lines, show_ends, squeeze_blank, show_tabs);
        }
    }

    return 0;
}
