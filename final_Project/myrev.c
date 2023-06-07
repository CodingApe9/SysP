#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *str) {
    unsigned int length = strlen(str);
    unsigned int i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) { //맨 앞, 맨 뒤에서 하나씩 swap 
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main(int argc, char *argv[]) {
    char *line = NULL;
    unsigned int line_length = 0; //크기 동적 할당을 위해 0으로 지정. 
    int read;

    if (argc>1){ //파일 입력. 
        FILE *file;
        file = fopen(argv[1], "r");
        if (file == NULL) { //존재하지 않는 파일. 
            perror("파일 열기 실패");
            exit(EXIT_FAILURE);
        }

        while ((read = getline(&line, &line_length, file)) != -1) { //읽은 줄의 문자 개수를 반환. 
            if (read > 1 && line[read - 1] == '\n') { //깔끔한 출력을 위한 처리 
                line[read - 1] = '\0';
            }
            reverse(line);
            if (line[0]=='\n'){ //개행만 있는 빈 줄의 경우. 
                printf("\n");
                continue;
            }
            printf("%s\n", line); //뒤집은 스트링 출력. 
        }
    }
    else { //stdin
        while ((read = getline(&line, &line_length, stdin)) != -1) { 
            if (line[read - 1] == '\n') {
                line[read - 1] = '\0';
            }
            reverse(line); //한 줄 입력받고 뒤집어서 출력. 
            printf("%s\n", line);
        }
    }
    
    free(line);

    return 0;
}
