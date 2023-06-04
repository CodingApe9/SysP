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


int main(int argc, char* argv[]) {
    int show_hidden = 0;
    int sort_by_time = 0;
    int reverse_order = 0;
    int show_details = 0;

    int opt;
    while ((opt = getopt(argc, argv, "altr")) != -1) {
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
            default:
                fprintf(stderr, "잘못된 옵션: %c\n", opt);
                return 1;
        }
    }

    struct dirent *de;
    DIR *dir = opendir(".");

    if (dir == NULL) {
        printf("현재 디렉토리를 열 수 없습니다.\n");
        return 1;
    }

    struct stat file_stat;
    struct passwd *pwd;
    struct group *grp;
    struct tm *time_info;
    char timestamp[20];

    while ((de = readdir(dir)) != NULL) {
        if (!show_hidden && de->d_name[0] == '.') {
            continue;
        }

        if (stat(de->d_name, &file_stat) == -1) {
            printf("파일 정보를 가져올 수 없습니다.\n");
            return 1;
        }

        if (show_details) {
            pwd = getpwuid(file_stat.st_uid);
            grp = getgrgid(file_stat.st_gid);
            time_info = localtime(&(file_stat.st_mtime));
            strftime(timestamp, sizeof(timestamp), "%b %e %H:%M", time_info);
            printf("%s %2lu %s %s %8lld %s %s\n",
                   (S_ISDIR(file_stat.st_mode) ? "d" : "-"),
                   file_stat.st_nlink, pwd->pw_name, grp->gr_name,
                   (long long)file_stat.st_size, timestamp, de->d_name);
        } else {
            printf("%s\n", de->d_name);
        }
    }

    closedir(dir);

    return 0;
}
