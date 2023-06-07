#include <stdio.h>

int main(int argc, char *argv[]) {
    char *message = "y"; //기본 문자열 
    
    if (argc > 1){ //인자로 받은 문자열이 있다면? 
        while (1){ //해당 문자열 출력. 
            for (int i=1; i<argc; i++){
                printf("%s ", argv[i]);
            }
            printf("\n");
        }
    }
    else { //아니면 y 출력 
        while (1) {
        printf("%s\n", message);
        }
    }

    return 0;
}
