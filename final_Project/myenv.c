#include <stdio.h>

int main(int argc, char *argv[])
{
    char **ptr;
    extern char **environ; //��� ȯ�� ������ ����Ű�� ����Ʈ �迭. extern �ܺ��� ������ ����. 

    for(ptr = environ; *ptr != 0; ptr++)
        printf("%s\n", *ptr);

    return 0; 
}
