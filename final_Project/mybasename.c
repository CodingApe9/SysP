#include <stdio.h>
#include <string.h> //strlen() �̿�. 

int main(int argc, char *argv[]) {
    char *name = argv[1]; //���ڷ� ��� �Է¹ޱ� 

    int idx = 0;

    if (name[strlen(name)-1]=='/'){ //����� ������ ���ڰ� /�̸� ����. (null�� ��ü) 
        name[strlen(name)-1] = '\0';
    }

    for (int i=0; i<strlen(name); i++){ //�����ʿ��� ���� ���� /�� ã��. 
        if (name[i]=='/'){
            idx = i;
        }
    }

    if (idx==0){
        for (int i=0; i<strlen(name); i++){//���� idx==0�̸� �� ��ο� /�� ����x�� �׳� �� ��ü�� �����̸�. 
            printf("%c", name[i]); //�׳� ���. 
        }
    }
    else {
        for (int i=idx+1; i<strlen(name); i++){ //idx+1 �� ���� �������� / ���� ���ں��� ���. 
            printf("%c", name[i]);
        }
    }
    
    printf("\n");
    return 0;
}
