#include <stdio.h>
#include <ctype.h>

int main(void){
	char a;
	while (1){
		printf("문자 입력: ");
		scanf(" %c", &a);
			
		if (islower(a)!=0){
			printf("%c의 대문자는 %c입니다.\n", a, toupper(a));
		} 
		else if (isupper(a)!=0){
			printf("%c의 소문자는 %c입니다.\n", a, tolower(a));
		}
		else {
			break;
		}
		//scanf("%c", &a); //개행 받고 버리기 
	}
	return 0;
}
