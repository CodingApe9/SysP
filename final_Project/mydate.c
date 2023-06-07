#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time; //1970년 1월 1일 기준 초 단위 숫자. 
    struct tm* time_info; //초 분 시 일 월 년 등을 가지는 구조체. 
    char time_buffer[80]; 
    
    current_time = time(NULL); //time함수로 현재 시간을 가져옴 

    time_info = localtime(&current_time); //지역 시간으로 변환하면서 tm구조체로 변환 

    // 출력할 형태로 바꿔줌.
    strftime(time_buffer, sizeof(time_buffer), "%a %b %e %H:%M:%S KST %Y", time_info);
    
    printf("%s\n", time_buffer);

    return 0;
}

