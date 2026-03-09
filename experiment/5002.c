#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_WORDS 50   // 最多统计50个不同单词
#define MAX_WORD_LEN 20// 单个单词最长20个字符
#define MAX_INPUT 1000 // 输入字符串最长1000字符

int main() {
    char input[MAX_INPUT] = {0};  // 存储原始输入
    char lower_input[MAX_INPUT] = {0}; // 存储转小写后的字符串
    char unique_words[MAX_WORDS][MAX_WORD_LEN] = {0}; // 存储去重后的单词
    int word_count = 0; // 不同单词的数量
    int i, j, k;        // 循环变量

    // 2. 读取输入
    fgets(input, MAX_INPUT, stdin);
    // 去除fgets读取的换行符
    input[strlen(input) - 1] = '\0';

    // 3. 第一步：将所有字母转小写，非字母替换为空格（指针遍历+基础判断）
    char *p = input;       // 原始字符串指针
    char *q = lower_input; // 小写字符串指针
    while (*p != '\0') {
        if (isalpha(*p)) { // 判断是否为字母
            *q = tolower(*p); // 转小写
            q++;
        } else {
            *q = ' '; // 非字母转空格，统一分隔符
            q++;
        }
        p++;
    }
    *q = '\0'; // 手动添加字符串结束符

    // 4. 第二步：手动分词（纯循环+数组，无复杂函数）
    char current_word[MAX_WORD_LEN] = {0}; // 
    int current_len = 0;                   // 
    p = lower_input; // 
    while (*p != '\0') {
        // 情况1：遇到空格，且当前有未保存的单词 → 保存单词
        if (*p == ' ' && current_len > 0) {
            current_word[current_len] = '\0'; // 单词结尾加结束符
            // 第三步：去重（遍历已保存的单词，比较是否重复）
            int is_duplicate = 0; // 标记是否重复（0=不重复，1=重复）
            for (i = 0; i < word_count; i++) {
                // strcmp是字符串比较函数
                if (strcmp(current_word, unique_words[i]) == 0) {
                    is_duplicate = 1;
                    break;
                }
            }
            // 不重复则存入数组，计数+1
            if (!is_duplicate && word_count < MAX_WORDS) {
                // strcpy字符串复制函数
                strcpy(unique_words[word_count], current_word);
                word_count++;
            }
            // 重置当前单词，准备提取下一个
            current_len = 0;
            memset(current_word, 0, sizeof(current_word));
        }
        // 情况2：遇到字母 → 加入当前单词
        else if (*p != ' ') {
            if (current_len < MAX_WORD_LEN - 1) { // 防止数组溢出
                current_word[current_len] = *p;
                current_len++;
            }
        }
        p++; // 指针后移，遍历下一个字符
    }

    // 处理最后一个单词（字符串末尾无空格的情况，
    if (current_len > 0) {
        current_word[current_len] = '\0';
        int is_duplicate = 0;
        for (i = 0; i < word_count; i++) {
            if (strcmp(current_word, unique_words[i]) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate && word_count < MAX_WORDS) {
            strcpy(unique_words[word_count], current_word);
            word_count++;
        }
    }

    printf("%d\n", word_count);

    
   

    return 0;
}