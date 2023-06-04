#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

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

int main(int argc, char* argv[]) {
    int show_hidden = 0;
    int sort_by_time = 0;
    int reverse_order = 0;

    // ����� ���ڸ� �м��Ͽ� �ɼ��� ����
    int opt;
    while ((opt = getopt(argc, argv, "altr")) != -1) {
        switch (opt) {
            case 'a':
                show_hidden = 1;
                break;
            case 'l':
                // '-l' �ɼ� �߰� ����
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
        printf("%s\n", files[i].name);
    }

    // ���� �Ҵ��� �޸� ����
    free(files);

    return 0;
}