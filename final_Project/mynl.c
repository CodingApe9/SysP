#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void addLineNumbers(FILE* file, int width, char* separator, int startNumber, int increment) {
    char line[BUFSIZ]; //<stdlib.h>
    int lineNumber = startNumber;

    // Read lines from the file and add line numbers
    while (fgets(line, sizeof(line), file) != NULL) {
        if (!isBlankLine(line)) { //빈 줄이 아니면 번호, 줄 출력 출력 
            printf("%*d%s%s", width, lineNumber, separator, line);
            lineNumber += increment;
        }
        else { //화이트 캐릭터 출력
            printf("%s", line);
        }
    }
}

int isBlankLine(const char* line) { //화이트 캐릭터 판별. 
    int i = 0;
    while (line[i] != '\0') {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') {
            return 0;
        }
        i++;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    FILE* file;
    int opt;
    int width = 6; //번호 기본 간격 
    char* separator = "\t"; //번호와 줄 사이 기본 간격(구분자)
    int startNumber = 1; //번호는 1부터 시작 
    int increment = 1; //번호 증가치도 1 
    
    while ((opt = getopt(argc, argv, "w:s:v:i:")) != -1) {
        switch (opt) {
        case 'w':
            width = atoi(optarg); //간격 설정. 
            break;
        case 's':
            separator = optarg; //번호와 줄 사이 구분자 설정 
            break;
        case 'v':
            startNumber = atoi(optarg); //시작 번호 설정 
            break;
        case 'i':
            increment = atoi(optarg); //증가치 설정. 
            break;
        default:
            fprintf(stderr, "Usage: %s [-w width] [-s separator] [-v startNumber] [-i increment] [file]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    if (optind < argc) { //파일 입력 
        file = fopen(argv[optind], "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }
    else { //stdin
        file = stdin;
    }

    addLineNumbers(file, width, separator, startNumber, increment);
    printf("\n");
    
    if (file != stdin) {
        fclose(file);
    }

    return 0;
}
