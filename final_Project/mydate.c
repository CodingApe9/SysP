#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time; //1970�� 1�� 1�� ���� �� ���� ����. 
    struct tm* time_info; //�� �� �� �� �� �� ���� ������ ����ü. 
    char time_buffer[80]; 
    
    current_time = time(NULL); //time�Լ��� ���� �ð��� ������ 

    time_info = localtime(&current_time); //���� �ð����� ��ȯ�ϸ鼭 tm����ü�� ��ȯ 

    // ����� ���·� �ٲ���.
    strftime(time_buffer, sizeof(time_buffer), "%a %b %e %H:%M:%S KST %Y", time_info);
    
    printf("%s\n", time_buffer);

    return 0;
}

