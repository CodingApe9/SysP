#include <stdio.h>

int main(int argc, char *argv[]) {
    char *message = "y"; //�⺻ ���ڿ� 
    
    if (argc > 1){ //���ڷ� ���� ���ڿ��� �ִٸ�? 
        while (1){ //�ش� ���ڿ� ���. 
            for (int i=1; i<argc; i++){
                printf("%s ", argv[i]);
            }
            printf("\n");
        }
    }
    else { //�ƴϸ� y ��� 
        while (1) {
        printf("%s\n", message);
        }
    }

    return 0;
}
