#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_LINES 10
#define DEFAULT_BYTES 0 

int main(int argc, char* argv[]) {
    int opt; //�ɼ� �Ľ̿� ����� ����. 
    int num_lines = DEFAULT_LINES; //�⺻ ��� ���� ���� �ʱ�ȭ. 
    int num_bytes = DEFAULT_BYTES; //-c�ɼǽ� ���. ����Ʈ ���� ���. 
    int use_lines = 1; //�⺻ ����� �� ����, -c �ɼǶ� off 
    int quiet_mode = 0; //-q�ɼǽ� ���. 

    while ((opt = getopt(argc, argv, "n:c:q")) != -1) { //�ɼ� �Ľ�. 
        switch (opt) {
        case 'n': //�� �� ���� ��������� �����Ѵ�. 
            num_lines = atoi(optarg); //atoi() ���ڿ��� ������ ��ȯ. optarg���� �ɼ��� �μ��� �����. 
            use_lines = 1;
            break;
        case 'c':
            num_bytes = atoi(optarg); //�� ����Ʈ ������ ������� ���Ѵ�. 
            use_lines = 0;
            break;
        case 'q':
            quiet_mode = 1; //������ �̸��� ������� �ʴ� �ɼ�. -q 
            break;
        default: //���� �� �� ���� �ɼ�. 
            fprintf(stderr, "Usage: %s [-n num_lines] [-c num_bytes] [-q] [file]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {//���� ������ ���� ���. 
        if (use_lines) { //�� ������ ���.
            char buffer[BUFSIZ]; //BUFSIZ: (stdio.h) �ý��ۿ� ���� �ٸ� ���� 1024 �̻� 
            int line_count = 0;
			
			//stdin���� �о�� ������ �� �� ��ŭ ���. 
            while (fgets(buffer, sizeof(buffer), stdin) != NULL && line_count < num_lines) {
                printf("%s", buffer);
                line_count++;
            }
        } 
        else { // -c �ɼ�: ����Ʈ ���� ��� 
            char buffer[num_bytes + 1]; //nulló������ 
            fread(buffer, 1, num_bytes, stdin);
            buffer[num_bytes] = '\0';
            printf("%s", buffer);
        }
    }
    else {//���� �Է�  
        for (int i = optind; i < argc; i++) { //�� ���Ͽ� ����. 
            FILE* file = fopen(argv[i], "r"); //�б� ���� ���� 
            if (file == NULL) { //�������� �ʴ� ����. 
                perror("fopen");
                continue;
            }
            if (!(argc - optind==1) && !quiet_mode) { //���� �̸� ���. -q�϶� ����. 
                printf("==> %s <==\n", argv[i]);
            }

            if (use_lines) { //�� ���� ���. 
                char buffer[BUFSIZ];
                int line_count = 0;

				//���� �Է��ΰ� ���� ���� ����. 
                while (fgets(buffer, sizeof(buffer), file) != NULL && line_count < num_lines) {
                    printf("%s", buffer);
                    line_count++;
                }
            }
            else { //����Ʈ ���� ���. ���� ����. 
                char buffer[num_bytes + 1];
                fread(buffer, 1, num_bytes, file);
                buffer[num_bytes] = '\0';
                printf("%s", buffer);
            }
            if ((i != argc - 1) && !quiet_mode) printf("\n"); //���Ϻ��� ������ ����. -q�϶� �ʿ� ����. 
            fclose(file);
        }
    }

    return 0;
}
