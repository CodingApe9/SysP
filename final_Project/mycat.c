#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void cat_file(FILE* file, int show_line_numbers, int show_nonblank_numbers, int squeeze_blank_lines, int show_ends, int show_tabs) {
    int line_number = 1;
    int prev_blank_line = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file)) {
        if (squeeze_blank_lines && prev_blank_line && buffer[0] == '\n') {
            continue;
        }

        if (show_line_numbers) {
            printf("%6d  ", line_number++);
        } else if (show_nonblank_numbers && buffer[0] != '\n') {
            printf("%6d  ", line_number++);
            prev_blank_line = 0;
        } else {
            prev_blank_line = (buffer[0] == '\n');
        }

        printf("%s", buffer);

        if (show_ends && buffer[strlen(buffer) - 1] != '\n') {
            printf("$");
        }

        if (show_tabs) {
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == '\t') {
                    printf("^I");
                } else {
                    putchar(buffer[i]);
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int show_line_numbers = 0;
    int show_nonblank_numbers = 0;
    int squeeze_blank_lines = 0;
    int show_ends = 0;
    int show_tabs = 0;

    int opt;
    while ((opt = getopt(argc, argv, "nbset")) != -1) {
        switch (opt) {
            case 'n':
                show_line_numbers = 1;
                break;
            case 'b':
                show_nonblank_numbers = 1;
                break;
            case 's':
                squeeze_blank_lines = 1;
                break;
            case 'E':
                show_ends = 1;
                break;
            case 'T':
                show_tabs = 1;
                break;
            default:
                fprintf(stderr, "Usage: cat [-n] [-b] [-s] [-e] [-t] [file ...]\n");
                return 1;
        }
    }

    if (optind >= argc) {
        // 파일이 지정되지 않은 경우 표준 입력을 읽어옴
        cat_file(stdin, show_line_numbers, show_nonblank_numbers, squeeze_blank_lines, show_ends, show_tabs);
    } else {
        // 지정된 파일들을 차례대로 읽어옴
        for (int i = optind; i < argc; i++) {
            FILE* file = fopen(argv[i], "r");
            if (file == NULL) {
                perror("fopen");
                continue;
            }

            cat_file(file, show_line_numbers, show_nonblank_numbers, squeeze_blank_lines, show_ends, show_tabs);

            fclose(file);
        }
    }

    return 0;
}
