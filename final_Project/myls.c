#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void print_file_info(struct dirent *de, struct stat *file_stat, int show_details, int show_inode, int omit_group, int show_disk_usage, int show_file_type) {
    struct passwd *pwd;
    struct group *grp;
    struct tm *time_info;
    char timestamp[20];

    if (show_details) {
        pwd = getpwuid(file_stat->st_uid);
        grp = getgrgid(file_stat->st_gid);
        time_info = localtime(&(file_stat->st_mtime));
        strftime(timestamp, sizeof(timestamp), "%b %e %H:%M", time_info);
        printf("%s ", (S_ISDIR(file_stat->st_mode) ? "d" : "-"));

        if (show_inode) {
            printf("%lu ", file_stat->st_ino);
        }

        printf("%2lu ", file_stat->st_nlink);

        if (!omit_group) {
            printf("%s ", pwd->pw_name);
        }

        if (!omit_group) {
            printf("%s ", grp->gr_name);
        }

        if (show_disk_usage) {
            printf("%8lld ", (long long)file_stat->st_blocks * 512 / 1024);
        } else {
            printf("%8lld ", (long long)file_stat->st_size / 1024);
        }

        printf("%s ", timestamp);

        if (show_file_type) {
            if (S_ISDIR(file_stat->st_mode)) {
                printf("/");
            } else if (file_stat->st_mode & S_IXUSR || file_stat->st_mode & S_IXGRP || file_stat->st_mode & S_IXOTH) {
                printf("*");
            }
        }

        printf("%s\n", de->d_name);
    } else {
        printf("%s\n", de->d_name);
    }
}

void ls_recursive(const char *directory, int show_hidden, int show_details, int show_inode, int omit_group, int show_disk_usage, int show_file_type) {
    struct dirent *de;
    DIR *dir = opendir(directory);

    if (dir == NULL) {
        printf("���丮�� �� �� �����ϴ�.\n");
        return;
    }

    struct stat file_stat;
    char subdirectory[256];

    while ((de = readdir(dir)) != NULL) {
        if (!show_hidden && de->d_name[0] == '.') {
            continue;
        }

        sprintf(subdirectory, "%s/%s", directory, de->d_name);

        if (stat(subdirectory, &file_stat) == -1) {
            printf("���� ������ ������ �� �����ϴ�.\n");
            return;
        }

        print_file_info(de, &file_stat, show_details, show_inode, omit_group, show_disk_usage, show_file_type);

        if (S_ISDIR(file_stat.st_mode) && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            printf("\n%s:\n", subdirectory);
            ls_recursive(subdirectory, show_hidden, show_details, show_inode, omit_group, show_disk_usage, show_file_type);
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    int show_hidden = 0;
    int sort_by_time = 0;
    int reverse_order = 0;
    int show_details = 0;
    int recursive = 0;
    int show_inode = 0;
    int omit_group = 0;
    int show_disk_usage = 0;
    int show_file_type = 0;

    int opt;
    while ((opt = getopt(argc, argv, "altrRiGsdF")) != -1) {
        switch (opt) {
            case 'a':
                show_hidden = 1;
                break;
            case 'l':
                show_details = 1;
                break;
            case 't':
                sort_by_time = 1;
                break;
            case 'r':
                reverse_order = 1;
                break;
            case 'R':
                recursive = 1;
                break;
            case 'i':
                show_inode = 1;
                break;
            case 'G':
                omit_group = 1;
                break;
            case 's':
                show_disk_usage = 1;
                break;
            case 'd':
                show_file_type = 1;
                break;
            case 'F':
                show_file_type = 1;
                break;
            default:
                fprintf(stderr, "�߸��� �ɼ�: %c\n", opt);
                return 1;
        }
    }

    struct dirent *de;
    DIR *dir = opendir(".");

    if (dir == NULL) {
        printf("���� ���丮�� �� �� �����ϴ�.\n");
        return 1;
    }

    struct stat file_stat;

    while ((de = readdir(dir)) != NULL) {
        if (!show_hidden && de->d_name[0] == '.') {
            continue;
        }

        if (stat(de->d_name, &file_stat) == -1) {
            printf("���� ������ ������ �� �����ϴ�.\n");
            return 1;
        }

        print_file_info(de, &file_stat, show_details, show_inode, omit_group, show_disk_usage, show_file_type);

        if (recursive && S_ISDIR(file_stat.st_mode) && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            printf("\n%s:\n", de->d_name);
            ls_recursive(de->d_name, show_hidden, show_details, show_inode, omit_group, show_disk_usage, show_file_type);
        }
    }

    closedir(dir);

    return 0;
}
