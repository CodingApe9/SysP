#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 문자열을 뒤집는 함수
void reverse(char *str) {
    unsigned int length = strlen(str);
    unsigned int i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main(int argc, char *argv[]) {
    char *line = NULL;
    unsigned int line_length = 0;
    int read;

    if (argc>1){
        FILE *file;
        file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("파일 열기 실패");
            exit(EXIT_FAILURE);
        }

        while ((read = getline(&line, &line_length, file)) != -1) {
            if (line[read - 1] == '\n') {
                line[read - 1] = '\0';
            }
            if (strlen(str)==0){
                continue
            }
            reverse(line);
            printf("%s\n", line);
        }
    }
    // 표준 입력에서 각 줄을 읽어서 뒤집어 출력
    else {
        while ((read = getline(&line, &line_length, stdin)) != -1) {
            if (line[read - 1] == '\n') {
                line[read - 1] = '\0';
            }
            reverse(line);
            printf("%s\n", line);
        }
    }
    
    free(line);

    return 0;
}
