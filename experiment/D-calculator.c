#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {
    char s[100];                //将算式作为字符串输入
    char error_chars[100];      //记录错误的运算符
    int error_count = 0;        //记录错误的运算符的下标，初始化为0
    int i = 0;

    // 1. 读取输入，直到遇到'='
    while (i < 99) {
        char c = getchar();     //问了豆老师，这样写其实不好，getchar()返回int，用char接收可能无法正确识别EOF
                                // 但在此处逻辑下，若c是EOF（-1），在有符号char系统中会变成-1，
                                // 后续判断 c == EOF 成立。在无符号char系统中会变成255，判断失败。
                                // 所以这是一个可移植性问题，但对于本题目输入以'='结束的场景影响不大。
        if (c == '=' || c == EOF) break;
        s[i++] = c;
    }
    s[i] = '\0';
    
    int len = strlen(s);
    i = 0; // 重置i，用于后续解析

    int current_num = 0;//临时存储当前正在解析的数字
    int result = 0;//最后答案
    char last_op = 0; // 记录上一个等待执行的运算符
    int has_started = 0; // 标记是否已经解析了第一个数字

    while (i < len) { 
        // 2. 解析数字（从字符串里识别数字）
        if (isdigit(s[i])) {
            current_num = 0;
            while (i < len && isdigit(s[i])) {
                current_num = current_num * 10 + (s[i] - '0');
                i++;
            }

            // 如果已经开始计算（有上一个运算符），则执行上一次的运算
            if (has_started && last_op != 0) {                 //排除开头是运算符
                if (last_op == '/') {
                     // 特别处理除法，检查除零
                    if (current_num == 0) {
                        // 将'/'视为一个错误字符
                        error_chars[error_count++] = '/';
                    } else {
                        result /= current_num;
                    }
                } else {
                    // 处理其他运算符
                    switch (last_op) {
                        case '+': result += current_num; break;
                        case '-': result -= current_num; break;
                        case '*': result *= current_num; break;
                    }
                }
                last_op = 0; // 运算执行完毕，清空上一个运算符，防止重复使用
            } else if (!has_started) {
                // 这是第一个数字，作为初始结果
                result = current_num;
                has_started = 1;
            }
            // else: 如果has_started为真但last_op为0，说明是连续的数字，忽略
        } else {
            // 3. 检查是否为合法运算符
            if (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/') {
                error_chars[error_count++] = s[i];
                i++;
            } else {
                // 4. 检查运算符的位置是否合法
                // 如果运算符在开头、结尾，或者后面不是数字，则是错误的
                if (i == 0 || i == len - 1 || !isdigit(s[i+1])) {
                    // 将当前运算符记录为错误
                    error_chars[error_count++] = s[i];
                    i++; // 移动到下一个字符

                    // 如果下一个字符不是数字，也将其记录为错误
                    // 同时要防止i越界
                    if (i < len && !isdigit(s[i])) {
                        error_chars[error_count++] = s[i];
                        i++;
                    }
                } 
                // 如果运算符位置合法，则记录下来，等待下一个数字进行计算
                else if (i < len - 1 && isdigit(s[i+1])) {
                    last_op = s[i];
                    i++;
                }
            }
        }
    }

    // 5. 统一处理并输出所有错误
    if (error_count > 0) {
        printf("错误的运算符:");
        for (int j = 0; j < error_count; j++) {
            printf("%c", error_chars[j]);
        }
        printf("\n");
    }
    // 6. 如果没有任何错误，才输出计算结果
    else if (has_started) {
        printf("%d\n", result);
    }

    return 0;
}