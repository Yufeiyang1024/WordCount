
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

    char param = argv[1][1]; // 跳过‘-’，直接获取参数字符
    const char *filename = argv[2];

    int result;
    if (param == 'c') {
        result = countCharacters(filename);
        printf("字符数：%d\n", result);
    } else if (param == 'w') {
        result = countWords(filename);
        printf("单词数：%d\n", result);
    } else {
        printf("错误的参数！请输入'-c'或'-w'。\n");
        return 1;
    }

    return 0;
}

// 统计字符数，包括空格、制表符和换行符
int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
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

// 统计单词数，以空格或逗号作为分隔符
int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
        return -1;
    }

    int count = 0; // 单词计数器
    int inWord = 0; // 标记是否在单词内

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') { // 遇到空格、制表符、换行符或逗号，单词结束
            if (inWord) {
                count++; // 计数增加
                inWord = 0;
            }
        } else {
            inWord = 1; // 开始一个新的单词
        }
    }
    // 处理文件末尾如果是一个单词的情况
    if (inWord) count++;

    fclose(file);
    return count;
}

