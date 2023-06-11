#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//유닉스 기반 os에 제공되는 기능, 상수: getopt(), fopen(), fclose(), perror() 등 

#define BUFFER_SIZE 4096

void display_file(const char* filename, int number_lines, int show_ends, int show_tabs, int show_nonprint, int squeeze_blank) {
    FILE* file = fopen(filename, "r"); //파일 읽기모드 오픈 
    if (file == NULL) { //존재하지 않는 파일 
        perror("fopen");
        return;
    }

    char buffer[BUFFER_SIZE];
    int lineNums = 1; //각 줄의 맨 앞에 번호 출력을 위한 변수-n, -b 옵션에 사용 

    char firstNL = 1; //-s 옵션에 이용되는 변수 비어 있는 줄이 여러 개 일때 한 줄로 압축 
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) { //파일에서 버퍼로 한 줄씩 읽어 옴(최대 크기는 버퍼 사이즈)
        if (squeeze_blank && buffer[0] == '\n') { //-s 옵션 flag가 on이면서 빈줄일때 
            if (!number_lines && firstNL) { //첫 줄만 개행 출력 
                firstNL = 0; //flag off해서 두번째 빈줄부터는 출력을 막음
                printf("\n");
            }
            else if (!number_lines && !firstNL) { //두번재 빈줄부터 개행출력x 
            }
            else {//-b옵션일땐 압축이 되면 안된다. 
                printf("\n");//라인넘버는 없고 개행만 출력 
            }
            continue;
        }

        firstNL = 1; //개행이 아닌 다른 줄이 나오는 순간 다시 on (-s옵션)
		
        if (number_lines) {//라인 넘버를 표시해야 하는 옵션이면 
            printf("%6d  ", lineNums++);  // 라인 번호 출력
        }
        int i = 0;
        while (buffer[i] != '\0') { //각 줄에 대해 출력
            if (show_ends && buffer[i] == '\n') { //-E 옵션은 개행앞에 $를 붙여준다. 
                printf("$\n");
            }
            else if (show_tabs && buffer[i] == '\t') { //-T 옵션은 ^I으로 대체한다. 
                printf("^I");
            } else if (show_nonprint) { //-v 옵션은 특수문자를 표시한다. 
                if (buffer[i] == '\n' || buffer[i] == '\t') { //개행이나 탭을 제외하고. 
                    printf("%c", buffer[i]);
                }
                else if (buffer[i] < 32 || buffer[i] > 126) {//나머지 특수문자들은 +64를 더해 출력. 
                    printf("^%c", buffer[i] + 64);
                }
                else { //일반 문자 출력. 
                    putchar(buffer[i]);
                }
                
            } else { //따로 처리가 필요없는 문자. 
                putchar(buffer[i]);
            }
            i++;
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    int number_lines = 0; //-n, -b 옵션에 사용 
    int show_ends = 0; //-E 옵션 
    int show_tabs = 0; //-T 옵션 
    int show_nonprint = 0; //-v 옵션 
    int squeeze_blank = 0; //-s 옵션 

    int opt;
    while ((opt = getopt(argc, argv, "nbsETv")) != -1) { //옵션 인식 패턴에 맞는 옵션 하나씩 반환. 마지막엔 -1 
        switch (opt) { //unistd.h에 선언되어 있는 getopt() 
            case 'n': //각 옵션에 맞게 flag on 
                number_lines = 1;
                break;
            case 'b':
                number_lines = 1;
                squeeze_blank = 1;
                break;
            case 'E':
                show_ends = 1;
                break;
            case 'T':
                show_tabs = 1;
                break;
            case 'v':
                show_nonprint = 1;
                break;
            case 's':
                squeeze_blank = 1;
                break;
            default: //인식할 수 없는 옵션 optopt에 저장되어 있음. 
                fprintf(stderr, "Invalid option: -%c\n", optopt);
                return 1;
        }
    }

    if (optind >= argc) { //파일 이름이 인자에 없는 경우. 
        fprintf(stderr, "Usage: %s [options] <file>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[optind]; //파일 이름 
    display_file(filename, number_lines, show_ends, show_tabs, show_nonprint, squeeze_blank); //출력 함수 call 

    return 0;
}
