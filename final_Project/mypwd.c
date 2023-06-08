#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char buff[1024];
    getcwd(buff, 1024); //<unistd.h> 현재 작업 중인 디렉토리를 불러옴
    printf("%s\n", buff);
    return 0;
}
