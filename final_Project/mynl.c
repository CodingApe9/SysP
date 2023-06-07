#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void addLineNumbers(FILE* file, int width, char* separator, int startNumber, int increment) {
    char line[BUFSIZ]; //<stdlib.h>
    int lineNumber = startNumber;

    // Read lines from the file and add line numbers
    while (fgets(line, sizeof(line), file) != NULL) {
        if (!isBlankLine(line)) { //�� ���� �ƴϸ� ��ȣ, �� ��� ��� 
            printf("%*d%s%s", width, lineNumber, separator, line);
            lineNumber += increment;
        }
        else { //ȭ��Ʈ ĳ���� ���
            printf("%s", line);
        }
    }
}

int isBlankLine(const char* line) { //ȭ��Ʈ ĳ���� �Ǻ�. 
    int i = 0;
    while (line[i] != '\0') {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') {
            return 0;
        }
        i++;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    FILE* file;
    int opt;
    int width = 6; //��ȣ �⺻ ���� 
    char* separator = "\t"; //��ȣ�� �� ���� �⺻ ����(������)
    int startNumber = 1; //��ȣ�� 1���� ���� 
    int increment = 1; //��ȣ ����ġ�� 1 
    
    while ((opt = getopt(argc, argv, "w:s:v:i:")) != -1) {
        switch (opt) {
        case 'w':
            width = atoi(optarg); //���� ����. 
            break;
        case 's':
            separator = optarg; //��ȣ�� �� ���� ������ ���� 
            break;
        case 'v':
            startNumber = atoi(optarg); //���� ��ȣ ���� 
            break;
        case 'i':
            increment = atoi(optarg); //����ġ ����. 
            break;
        default:
            fprintf(stderr, "Usage: %s [-w width] [-s separator] [-v startNumber] [-i increment] [file]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    if (optind < argc) { //���� �Է� 
        file = fopen(argv[optind], "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }
    else { //stdin
        file = stdin;
    }

    addLineNumbers(file, width, separator, startNumber, increment);
    printf("\n");
    
    if (file != stdin) {
        fclose(file);
    }

    return 0;
}
