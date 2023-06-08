#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	//\33[H\33[J는 이스케이프 시퀀스.
	//이스케이프 시퀀스는 터미널에 특정한 명령을 전달하기 위해 사용되는 제어 문자열.
	//여기서 \33은 이스케이프 문자를 나타내는 ASCII 코드.
	//[H는 커서를 화면의 상단 왼쪽으로 이동시키는 명령. 
	//\33[J는 화면을 지우는 명령.
    write(1, "\33[H\33[J", 6); //<unistd.h>
}
