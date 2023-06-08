#include <stdio.h>

int main(int argc, char *argv[])
{
    char **ptr;
    extern char **environ; //모든 환경 변수를 가리키는 포인트 배열. extern 외부의 변수를 참조. 

    for(ptr = environ; *ptr != 0; ptr++)
        printf("%s\n", *ptr);

    return 0; 
}
