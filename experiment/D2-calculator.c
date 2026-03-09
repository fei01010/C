#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char expr[100];
    scanf("%s", expr);  // 读取算式（遇'='结束）
    
    int result = 0;
    int i = 0;
    // 读取第一个数字
    while (isdigit(expr[i])) {
        result = result * 10 + (expr[i] - '0');
        i++;
    }
    
    while (expr[i] != '=') {
        char op = expr[i];
        // 判断运算符是否合法
        if (op != '+' && op != '-' && op != '*' && op != '/') {
            printf("错误的运算符:%c\n", op);
            return 0;
        }
        i++;
        
        // 读取下一个数字
        int num = 0;
        while (isdigit(expr[i])) {
            num = num * 10 + (expr[i] - '0');
            i++;
        }
        
        // 计算
        switch (op) {
            case '+': result += num; break;
            case '-': result -= num; break;
            case '*': result *= num; break;
            case '/': result /= num; break;  // 题目保证结果是整数
        }
    }
    
    printf("%d\n", result);
    return 0;
}