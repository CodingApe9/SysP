#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>

int main(int argc, char *argv[]) {
    int opt;
    mode_t mode = 0755;
    char *owner = NULL;
    char *group = NULL;
    char *timestamp = NULL;

    while ((opt = getopt(argc, argv, "pm:u:g:t:")) != -1) {
        switch (opt) {
            case 'p':
                mode |= S_IRWXU | S_IRWXG | S_IRWXO;
                break;
            case 'm':
                mode = strtol(optarg, NULL, 8);
                break;
            case 'u':
                owner = optarg;
                break;
            case 'g':
                group = optarg;
                break;
            case 't':
                timestamp = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-p] [-m mode] [-u owner] [-g group] [-t timestamp] directory\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {
        fprintf(stderr, "No directory specified.\n");
        exit(EXIT_FAILURE);
    }

    char *directory = argv[optind];

    if (mkdir(directory, mode) == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    if (owner != NULL || group != NULL) {
        if (chown(directory, -1, -1) == -1) {
            perror("chown");
            exit(EXIT_FAILURE);
        }
    }

    if (group != NULL) {
        if (chown(directory, -1, -1) == -1) {
            perror("chown");
            exit(EXIT_FAILURE);
        }
    }

    if (timestamp != NULL) {
        struct utimbuf times;
        times.actime = times.modtime = strtol(timestamp, NULL, 10);
        if (utime(directory, &times) == -1) {
            perror("utime");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
