#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// ������ ���Ͽ��� ������ n���� ����ϴ� �Լ�
void print_last_n_lines(FILE* file, int n) {
    char buffer[BUFFER_SIZE][BUFFER_SIZE]; //�ֱ� 1024���� ���.
    int count = 0;

    // ������ ������ �����鼭 ���۸� ��ȯ��Ű�鼭 �ֱ� 1024�� ����
    while (fgets(buffer[count % n], BUFFER_SIZE, file) != NULL) {
        count++;
    }

    int start = (count > n) ? (count % n) : 0; //��� ���� �� ��� 
    int lines_to_print = (count > n) ? n : count; //���� �� ���� �� �� ������� ��� 

    for (int i = 0; i < lines_to_print; i++) { //��� 
        printf("%s", buffer[(start + i) % n]);
    }
}

// ������ ���Ͽ��� ������ n���� ���ڸ� ����ϴ� �Լ�
void print_last_n_chars(FILE* file, int n) {
    fseek(file, 0, SEEK_END); //�����͸� ���������� �̵�. 
    long file_size = ftell(file); //ftell() ���� �����Ͱ� ���� ����Ű�� �ִ� ��ġ�� ����Ʈ ������ ��ȯ.

    int chars_to_read = (n < file_size) ? n : file_size; //���� ����Ʈ �� ���. 
    char buffer[BUFFER_SIZE];

    fseek(file, -chars_to_read, SEEK_END); //���������� ���� ����Ʈ ����ŭ ������ �̵�. 

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {  //����Ʈ ���� ���. 
        printf("%s", buffer);
    }
}

int main(int argc, char* argv[]) {
    int n = 10; // �⺻������ 10�� ���
    int c = 0;  // ���� �� �ɼ� �ʱ�ȭ
    int q = 0;  // ������ ��� �ɼ� �ʱ�ȭ

    // ����� �μ� ó��
    int opt;
    while ((opt = getopt(argc, argv, "n:c:q")) != -1) {
        switch (opt) {
        case 'n':
            n = atoi(optarg); //-n �ɼ��� �μ��� ������ ���ڷ� ����� �� ���� ����. 
            break;
        case 'c':
            c = atoi(optarg); //-c �ɼ��� �μ��� ������ ���ڷ� ����� ����Ʈ ���� ����. 
            break;
        case 'q': //-q �ɼ� flag on 
            q = 1;
            break;
        default:
            fprintf(stderr, "����: %s [-n ����] [-c ����] [-q] ����...\n", argv[0]);
            return 1;
        }
    }
    
    for (int i = optind; i < argc; i++) { //�� ���Ͽ� ���� 
        char* filename = argv[i];

        // ���� ����
        FILE* file = fopen(filename, "r"); //���� ���� �õ� 
        if (file == NULL) { //�������� �ʴ� ���� 
            perror("���� ���� ����");
            continue;
        }
        
        if (!(argc - optind == 1) && !q) { //-q �ɼ��� �ƴ� ���� ���� �̸� ���. 
            printf("==> %s <==\n", filename);
        }
        
        if (c > 0) {// c>0�̸� -c �ɼ��� ������ ��. 
            // -c �ɼ����� ������ ���� ����ŭ ���
            print_last_n_chars(file, c);
        }
        else { //�� �ܿ��� �� �� ���� ���. 
            // -n �ɼ����� ������ �� ����ŭ ���
            print_last_n_lines(file, n);
        }

        // ���� �ݱ�
        fclose(file);

        // ���� �� ������ ���� ���� ���
        if (!(argc - i == 1) && !q) {
            printf("\n");
        }
    }

    return 0;
}

