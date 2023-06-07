#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utime.h>

int main(int argc, char *argv[]) {
    int opt;
    int use_access_time = 0;
    int use_change_time = 0;
    int use_modification_time = 0;

    while ((opt = getopt(argc, argv, "acm")) != -1) {
        switch (opt) {
            case 'a':
                use_access_time = 1;
                break;
            case 'c':
                use_change_time = 1;
                break;
            case 'm':
                use_modification_time = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-c] [-m] file\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {
        fprintf(stderr, "No file specified.\n");
        exit(EXIT_FAILURE);
    }

    char *file = argv[optind];

    struct utimbuf times;
    if (use_access_time || use_change_time || use_modification_time) {
        if (utime(file, &times) == -1) {
            perror("utime");
            exit(EXIT_FAILURE);
        }
    }

    if (use_access_time) {
        times.actime = time(NULL);
    }
    if (use_change_time) {
        times.modtime = time(NULL);
    }
    if (use_modification_time) {
        times.modtime = time(NULL);
    }

    if (utime(file, &times) == -1) {
        perror("utime");
        exit(EXIT_FAILURE);
    }

    return 0;
}
