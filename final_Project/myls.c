#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// 파일 및 디렉토리 정보를 저장하기 위한 구조체
typedef struct {
    char* name;
    struct stat attributes;
} File;

// 파일 비교를 위한 비교 함수
int compare_files(const void* a, const void* b) {
    return strcmp(((File*)a)->name, ((File*)b)->name);
}

// 시간 비교를 위한 비교 함수
int compare_time(const void* a, const void* b) {
    time_t time_a = ((File*)a)->attributes.st_mtime;
    time_t time_b = ((File*)b)->attributes.st_mtime;
    return difftime(time_a, time_b);
}

int main(int argc, char* argv[]) {
    int show_hidden = 0;
    int sort_by_time = 0;
    int reverse_order = 0;

    // 명령행 인자를 분석하여 옵션을 설정
    int opt;
    while ((opt = getopt(argc, argv, "altr")) != -1) {
        switch (opt) {
            case 'a':
                show_hidden = 1;
                break;
            case 'l':
                // '-l' 옵션 추가 설정
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

    // 현재 디렉토리의 파일과 폴더를 읽어옴
    File* files = NULL;
    int num_files = 0;
    while ((de = readdir(dir)) != NULL) {
        // -a 옵션을 사용하지 않을 경우 숨김 파일은 무시
        if (!show_hidden && de->d_name[0] == '.') {
            continue;
        }

        // 파일 정보를 읽어옴
        File file;
        file.name = de->d_name;
        stat(file.name, &file.attributes);

        // 배열에 파일 정보 추가
        files = realloc(files, (num_files + 1) * sizeof(File));
        files[num_files] = file;
        num_files++;
    }

    closedir(dir);

    // 파일 목록 정렬
    qsort(files, num_files, sizeof(File), compare_files);

    // -t 옵션 사용 시 파일 목록을 수정된 시간으로 정렬
    if (sort_by_time) {
        qsort(files, num_files, sizeof(File), compare_time);
    }

    // -r 옵션 사용 시 파일 목록을 역순으로 정렬
    if (reverse_order) {
        File* temp = malloc(num_files * sizeof(File));
        for (int i = 0; i < num_files; i++) {
            temp[i] = files[num_files - i - 1];
        }
        free(files);
        files = temp;
    }

    // 파일 목록 출력
    for (int i = 0; i < num_files; i++) {
        printf("%s\n", files[i].name);
    }

    // 동적 할당한 메모리 해제
    free(files);

    return 0;
}