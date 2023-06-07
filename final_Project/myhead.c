#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_LINES 10
#define DEFAULT_BYTES 0 

int main(int argc, char* argv[]) {
    int opt; //옵션 파싱에 사용할 변수. 
    int num_lines = DEFAULT_LINES; //기본 출력 라인 수로 초기화. 
    int num_bytes = DEFAULT_BYTES; //-c옵션시 사용. 바이트 지정 출력. 
    int use_lines = 1; //기본 출력은 줄 단위, -c 옵션땐 off 
    int quiet_mode = 0; //-q옵션시 사용. 

    while ((opt = getopt(argc, argv, "n:c:q")) != -1) { //옵션 파싱. 
        switch (opt) {
        case 'n': //즉 몇 줄을 출력할지를 설정한다. 
            num_lines = atoi(optarg); //atoi() 문자열을 정수로 변환. optarg에는 옵션의 인수가 저장됨. 
            use_lines = 1;
            break;
        case 'c':
            num_bytes = atoi(optarg); //몇 바이트 단위로 출력할지 정한다. 
            use_lines = 0;
            break;
        case 'q':
            quiet_mode = 1; //파일의 이름을 출력하지 않는 옵션. -q 
            break;
        default: //에러 알 수 없는 옵션. 
            fprintf(stderr, "Usage: %s [-n num_lines] [-c num_bytes] [-q] [file]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {//읽을 파일이 없는 경우. 
        if (use_lines) { //줄 단위로 출력.
            char buffer[BUFSIZ]; //BUFSIZ: (stdio.h) 시스템에 따라 다름 보통 1024 이상 
            int line_count = 0;
			
			//stdin에서 읽어와 설정한 줄 수 만큼 출력. 
            while (fgets(buffer, sizeof(buffer), stdin) != NULL && line_count < num_lines) {
                printf("%s", buffer);
                line_count++;
            }
        } 
        else { // -c 옵션: 바이트 단위 출력 
            char buffer[num_bytes + 1]; //null처리위해 
            fread(buffer, 1, num_bytes, stdin);
            buffer[num_bytes] = '\0';
            printf("%s", buffer);
        }
    }
    else {//파일 입력  
        for (int i = optind; i < argc; i++) { //각 파일에 대해. 
            FILE* file = fopen(argv[i], "r"); //읽기 모드로 오픈 
            if (file == NULL) { //존재하지 않는 파일. 
                perror("fopen");
                continue;
            }
            if (!(argc - optind==1) && !quiet_mode) { //파일 이름 출력. -q일땐 안함. 
                printf("==> %s <==\n", argv[i]);
            }

            if (use_lines) { //줄 단위 출력. 
                char buffer[BUFSIZ];
                int line_count = 0;

				//파일 입력인거 빼고 위와 동일. 
                while (fgets(buffer, sizeof(buffer), file) != NULL && line_count < num_lines) {
                    printf("%s", buffer);
                    line_count++;
                }
            }
            else { //바이트 단위 출력. 위와 동일. 
                char buffer[num_bytes + 1];
                fread(buffer, 1, num_bytes, file);
                buffer[num_bytes] = '\0';
                printf("%s", buffer);
            }
            if ((i != argc - 1) && !quiet_mode) printf("\n"); //파일별로 구분을 위해. -q일땐 필요 없다. 
            fclose(file);
        }
    }

    return 0;
}
