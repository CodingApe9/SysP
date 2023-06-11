#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//���н� ��� os�� �����Ǵ� ���, ���: getopt(), fopen(), fclose(), perror() �� 

#define BUFFER_SIZE 4096

void display_file(const char* filename, int number_lines, int show_ends, int show_tabs, int show_nonprint, int squeeze_blank) {
    FILE* file = fopen(filename, "r"); //���� �б��� ���� 
    if (file == NULL) { //�������� �ʴ� ���� 
        perror("fopen");
        return;
    }

    char buffer[BUFFER_SIZE];
    int lineNums = 1; //�� ���� �� �տ� ��ȣ ����� ���� ����-n, -b �ɼǿ� ��� 

    char firstNL = 1; //-s �ɼǿ� �̿�Ǵ� ���� ��� �ִ� ���� ���� �� �϶� �� �ٷ� ���� 
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) { //���Ͽ��� ���۷� �� �پ� �о� ��(�ִ� ũ��� ���� ������)
        if (squeeze_blank && buffer[0] == '\n') { //-s �ɼ� flag�� on�̸鼭 �����϶� 
            if (!number_lines && firstNL) { //ù �ٸ� ���� ��� 
                firstNL = 0; //flag off�ؼ� �ι�° ���ٺ��ʹ� ����� ����
                printf("\n");
            }
            else if (!number_lines && !firstNL) { //�ι��� ���ٺ��� �������x 
            }
            else {//-b�ɼ��϶� ������ �Ǹ� �ȵȴ�. 
                printf("\n");//���γѹ��� ���� ���ุ ��� 
            }
            continue;
        }

        firstNL = 1; //������ �ƴ� �ٸ� ���� ������ ���� �ٽ� on (-s�ɼ�)
		
        if (number_lines) {//���� �ѹ��� ǥ���ؾ� �ϴ� �ɼ��̸� 
            printf("%6d  ", lineNums++);  // ���� ��ȣ ���
        }
        int i = 0;
        while (buffer[i] != '\0') { //�� �ٿ� ���� ���
            if (show_ends && buffer[i] == '\n') { //-E �ɼ��� ����տ� $�� �ٿ��ش�. 
                printf("$\n");
            }
            else if (show_tabs && buffer[i] == '\t') { //-T �ɼ��� ^I���� ��ü�Ѵ�. 
                printf("^I");
            } else if (show_nonprint) { //-v �ɼ��� Ư�����ڸ� ǥ���Ѵ�. 
                if (buffer[i] == '\n' || buffer[i] == '\t') { //�����̳� ���� �����ϰ�. 
                    printf("%c", buffer[i]);
                }
                else if (buffer[i] < 32 || buffer[i] > 126) {//������ Ư�����ڵ��� +64�� ���� ���. 
                    printf("^%c", buffer[i] + 64);
                }
                else { //�Ϲ� ���� ���. 
                    putchar(buffer[i]);
                }
                
            } else { //���� ó���� �ʿ���� ����. 
                putchar(buffer[i]);
            }
            i++;
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    int number_lines = 0; //-n, -b �ɼǿ� ��� 
    int show_ends = 0; //-E �ɼ� 
    int show_tabs = 0; //-T �ɼ� 
    int show_nonprint = 0; //-v �ɼ� 
    int squeeze_blank = 0; //-s �ɼ� 

    int opt;
    while ((opt = getopt(argc, argv, "nbsETv")) != -1) { //�ɼ� �ν� ���Ͽ� �´� �ɼ� �ϳ��� ��ȯ. �������� -1 
        switch (opt) { //unistd.h�� ����Ǿ� �ִ� getopt() 
            case 'n': //�� �ɼǿ� �°� flag on 
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
            default: //�ν��� �� ���� �ɼ� optopt�� ����Ǿ� ����. 
                fprintf(stderr, "Invalid option: -%c\n", optopt);
                return 1;
        }
    }

    if (optind >= argc) { //���� �̸��� ���ڿ� ���� ���. 
        fprintf(stderr, "Usage: %s [options] <file>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[optind]; //���� �̸� 
    display_file(filename, number_lines, show_ends, show_tabs, show_nonprint, squeeze_blank); //��� �Լ� call 

    return 0;
}
