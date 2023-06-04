#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

void print_file_info(struct dirent* entry) {
    printf("%s\n", entry->d_name);
}

void ls_recursive(char* path, int show_hidden) {
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }

        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char sub_path[PATH_MAX];
            snprintf(sub_path, sizeof(sub_path), "%s/%s", path, entry->d_name);

            printf("\n%s:\n", sub_path);
            ls_recursive(sub_path, show_hidden);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    char* path = ".";
    int show_hidden = 0;
    int show_details = 0;
    int show_recursive = 0;

    int opt;
    while ((opt = getopt(argc, argv, "alR")) != -1) {
        switch (opt) {
            case 'a':
                show_hidden = 1;
                break;
            case 'l':
                show_details = 1;
                break;
            case 'R':
                show_recursive = 1;
                break;
            default:
                fprintf(stderr, "Usage: ls [-a] [-l] [-R] [directory]\n");
                return 1;
        }
    }

    if (optind < argc) {
        path = argv[optind];
    }

    if (show_recursive) {
        ls_recursive(path, show_hidden);
    } else {
        DIR* dir = opendir(path);
        if (dir == NULL) {
            perror("opendir");
            return 1;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            if (!show_hidden && entry->d_name[0] == '.') {
                continue;
            }

            if (show_details) {
                print_file_info(entry);
            } else {
                printf("%s\n", entry->d_name);
            }
        }

        closedir(dir);
    }

    return 0;
}
