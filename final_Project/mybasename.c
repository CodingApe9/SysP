#include <stdio.h>
#include <string.h> //strlen() 이용. 

int main(int argc, char *argv[]) {
    char *name = argv[1]; //인자로 경로 입력받기 

    int idx = 0;

    if (name[strlen(name)-1]=='/'){ //경로의 마지막 문자가 /이면 삭제. (null로 대체) 
        name[strlen(name)-1] = '\0';
    }

    for (int i=0; i<strlen(name); i++){ //오른쪽에서 제일 까까운 /을 찾음. 
        if (name[i]=='/'){
            idx = i;
        }
    }

    if (idx==0){
        for (int i=0; i<strlen(name); i++){//만약 idx==0이면 즉 경로에 /가 포함x면 그냥 그 자체가 파일이름. 
            printf("%c", name[i]); //그냥 출력. 
        }
    }
    else {
        for (int i=idx+1; i<strlen(name); i++){ //idx+1 즉 제일 오른쪽의 / 다음 문자부터 출력. 
            printf("%c", name[i]);
        }
    }
    
    printf("\n");
    return 0;
}
