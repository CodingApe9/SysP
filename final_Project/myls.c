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


// ���� �� ���丮 ������ �����ϱ� ���� ����ü
typedef struct {
    char* name;
    struct stat attributes;
} File;

// ���� �񱳸� ���� �� �Լ�
int compare_files(const void* a, const void* b) {
    return strcmp(((File*)a)->name, ((File*)b)->name);
}

// �ð� �񱳸� ���� �� �Լ�
int compare_time(const void* a, const void* b) {
    time_t time_a = ((File*)a)->attributes.st_mtime;
    time_t time_b = ((File*)b)->attributes.st_mtime;
    return difftime(time_a, time_b);
}

// ���� ��带 ���ڿ��� ��ȯ�Ͽ� ��ȯ
const char* get_permissions(mode_t mode) {
    static char permissions[10];

    permissions[0] = (S_ISDIR(mode)) ? 'd' : '-';
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';

    return permissions;
}

int main(int argc, char* argv[]) {
    int show_hidden = 0;
    int sort_by_time = 0;
    int reverse_order = 0;
    int show_details = 0;

    // ����� ���ڸ� �м��Ͽ� �ɼ��� ����
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

    // ���� ���丮�� ���ϰ� ������ �о��
    File* files = NULL;
    int num_files = 0;
    while ((de = readdir(dir)) != NULL) {
        // -a �ɼ��� ������� ���� ��� ���� ������ ����
        if (!show_hidden && de->d_name[0] == '.') {
            continue;
        }

        // ���� ������ �о��
        File file;
        file.name = de->d_name;
        stat(file.name, &file.attributes);

        // �迭�� ���� ���� �߰�
        files = realloc(files, (num_files + 1) * sizeof(File));
        files[num_files] = file;
        num_files++;
    }

    closedir(dir);

    // ���� ��� ����
    qsort(files, num_files, sizeof(File), compare_files);

    // -t �ɼ� ��� �� ���� ����� ������ �ð����� ����
    if (sort_by_time) {
        qsort(files, num_files, sizeof(File), compare_time);
    }

    // -r �ɼ� ��� �� ���� ����� �������� ����
    if (reverse_order) {
        File* temp = malloc(num_files * sizeof(File));
        for (int i = 0; i < num_files; i++) {
            temp[i] = files[num_files - i - 1];
        }
        free(files);
        files = temp;
    }

    // ���� ��� ���
    for (int i = 0; i < num_files; i++) {
        if (show_details) {
            struct passwd *pwd = getpwuid(files[i].attributes.st_uid);
            struct group *grp = getgrgid(files[i].attributes.st_gid);
            char timestamp[20];
            strftime(timestamp, sizeof(timestamp), "%b %e %H:%M", localtime(&(files[i].attributes.st_mtime)));
            printf("%s %2lu %s %s %8lld %s %s\n", get_permissions(files[i].attributes.st_mode),
                   files[i].attributes.st_nlink, pwd->pw_name, grp->gr_name,
                   (long long)files[i].attributes.st_size, timestamp, files[i].name);
        } else {
            printf("%s\n", files[i].name);
        }
    }

    // ���� �Ҵ��� �޸� ����
    free(files);

    return 0;
}