#include <stdio.h>

int main(int argc, char *argv[]) {
    char *name = argv[1];

    int idx = 0;
    for (int i=0; i<strlen(name); i++){
        if (name[i]=='/'){
            idx = i;
        }
    }
    
    for (int i=idx+1; i<str(name); i++){
        printf("%c", name[i]);
    }

    return 0;
}