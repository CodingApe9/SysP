#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// 지정된 파일에서 마지막 n줄을 출력하는 함수
void print_last_n_lines(FILE* file, int n) {
    char buffer[BUFFER_SIZE][BUFFER_SIZE]; //최근 1024줄을 기억.
    int count = 0;

    // 파일을 끝까지 읽으면서 버퍼를 순환시키면서 최근 1024줄 유지
    while (fgets(buffer[count % n], BUFFER_SIZE, file) != NULL) {
        count++;
    }

    int start = (count > n) ? (count % n) : 0; //출력 시작 줄 계산 
    int lines_to_print = (count > n) ? n : count; //시작 줄 부터 몇 줄 출력할지 계산 

    for (int i = 0; i < lines_to_print; i++) { //출력 
        printf("%s", buffer[(start + i) % n]);
    }
}

// 지정된 파일에서 마지막 n개의 문자를 출력하는 함수
void print_last_n_chars(FILE* file, int n) {
    fseek(file, 0, SEEK_END); //포인터를 마지막으로 이동. 
    long file_size = ftell(file); //ftell() 파일 포인터가 현재 가리키고 있는 위치를 바이트 단위로 반환.

    int chars_to_read = (n < file_size) ? n : file_size; //읽을 바이트 수 계산. 
    char buffer[BUFFER_SIZE];

    fseek(file, -chars_to_read, SEEK_END); //마지막에서 읽을 바이트 수만큼 앞으로 이동. 

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {  //바이트 단위 출력. 
        printf("%s", buffer);
    }
}

int main(int argc, char* argv[]) {
    int n = 10; // 기본적으로 10줄 출력
    int c = 0;  // 문자 수 옵션 초기화
    int q = 0;  // 조용한 모드 옵션 초기화

    // 명령행 인수 처리
    int opt;
    while ((opt = getopt(argc, argv, "n:c:q")) != -1) {
        switch (opt) {
        case 'n':
            n = atoi(optarg); //-n 옵션의 인수로 지정된 숫자로 출력할 줄 수를 설정. 
            break;
        case 'c':
            c = atoi(optarg); //-c 옵션의 인수로 지정된 숫자로 출력할 바이트 수를 설정. 
            break;
        case 'q': //-q 옵션 flag on 
            q = 1;
            break;
        default:
            fprintf(stderr, "사용법: %s [-n 숫자] [-c 숫자] [-q] 파일...\n", argv[0]);
            return 1;
        }
    }
    
    for (int i = optind; i < argc; i++) { //각 파일에 대해 
        char* filename = argv[i];

        // 파일 열기
        FILE* file = fopen(filename, "r"); //파일 오픈 시도 
        if (file == NULL) { //존재하지 않는 파일 
            perror("파일 열기 실패");
            continue;
        }
        
        if (!(argc - optind == 1) && !q) { //-q 옵션이 아닐 때는 파일 이름 출력. 
            printf("==> %s <==\n", filename);
        }
        
        if (c > 0) {// c>0이면 -c 옵션이 지정된 것. 
            // -c 옵션으로 지정된 문자 수만큼 출력
            print_last_n_chars(file, c);
        }
        else { //그 외에는 줄 수 기준 출력. 
            // -n 옵션으로 지정된 줄 수만큼 출력
            print_last_n_lines(file, n);
        }

        // 파일 닫기
        fclose(file);

        // 파일 간 구분을 위한 개행 출력
        if (!(argc - i == 1) && !q) {
            printf("\n");
        }
    }

    return 0;
}

