
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countCharacters(const char *filename);
int countWords(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] input_file_name\n", argv[0]);
        return 1;
    }

    char param = argv[1][1]; // ������-����ֱ�ӻ�ȡ�����ַ�
    const char *filename = argv[2];

    int result;
    if (param == 'c') {
        result = countCharacters(filename);
        printf("�ַ�����%d\n", result);
    } else if (param == 'w') {
        result = countWords(filename);
        printf("��������%d\n", result);
    } else {
        printf("����Ĳ�����������'-c'��'-w'��\n");
        return 1;
    }

    return 0;
}

// ͳ���ַ����������ո��Ʊ���ͻ��з�
int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("���ļ�ʧ��");
        return -1;
    }

    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

// ͳ�Ƶ��������Կո�򶺺���Ϊ�ָ���
int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("���ļ�ʧ��");
        return -1;
    }

    int count = 0; // ���ʼ�����
    int inWord = 0; // ����Ƿ��ڵ�����

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') { // �����ո��Ʊ�������з��򶺺ţ����ʽ���
            if (inWord) {
                count++; // ��������
                inWord = 0;
            }
        } else {
            inWord = 1; // ��ʼһ���µĵ���
        }
    }
    // �����ļ�ĩβ�����һ�����ʵ����
    if (inWord) count++;

    fclose(file);
    return count;
}

