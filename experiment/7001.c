#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[20];
    int ms;
    char date[11];   // 格式：YYYY-MM-DD
    char time_str[9];// 格式：HH:MM:SS
} Record;


// 从score.txt读取历史记录到数组，返回读取的条数
int load_records(Record rec[], int max_count) {
    FILE *fp = fopen("score.txt", "r");
    int count = 0;
    if (fp == NULL) {
        return 0;
    }
    // 按格式读取每条记录
    while (count < max_count && fscanf(fp, "%s %d %s %s", 
        rec[count].name, &rec[count].ms, rec[count].date, rec[count].time_str) != EOF) {
        count++;
    }
    fclose(fp);
    return count;
}

void show_records(Record rec[], int count) {
    printf("编号  姓名    反应时间(ms)  记录时间\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-4d %-8s %-12d %s %s\n", 
            i+1, rec[i].name, rec[i].ms, rec[i].date, rec[i].time_str);
    }
}

void add_record(Record rec[], int *count, int ms) {
    char name[20];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    printf("请输入姓名（不含空格）：");
    scanf("%s", name);
    strcpy(rec[*count].name, name);
    rec[*count].ms = ms;
    strftime(rec[*count].date, 11, "%Y-%m-%d", t);
    // 格式化时间（HH:MM:SS）
    strftime(rec[*count].time_str, 9, "%H:%M:%S", t);

    // 追加到文件
    FILE *fp = fopen("score.txt", "a");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return;
    }
    fprintf(fp, "%s %d %s %s\n", 
        rec[*count].name, rec[*count].ms, rec[*count].date, rec[*count].time_str);
    fclose(fp);

    // 更新记录条数
    (*count)++;
    printf("成绩已保存到score.txt。\n");
}


// 模拟游戏（随机等待后获取反应时间）
int play_game() {
    printf("(随机等待...)\n");
    // 随机等待1~3秒
    srand((unsigned int)time(NULL));
    int wait = rand() % 3 + 1;
    for (int i = 0; i < wait * 100000000; i++); // 简单延时

    printf("\033[1;33m现在按Enter!\033[0m\n");
    // 记录按下Enter的时间
    clock_t start = clock();
    getchar(); // 吸收之前的换行
    getchar(); // 等待用户按Enter
    clock_t end = clock();

    int reaction = (int)((end - start) * 1000.0 / CLOCKS_PER_SEC);
    printf("你的反应时间是：%d 毫秒。\n", reaction);
    return reaction;
}


int main() {
    const int MAX_COUNT = 100; // 最大记录条数
    Record rec[MAX_COUNT];
    int count = load_records(rec, MAX_COUNT);
    printf("已从 score.txt 读取 %d 条记录。\n", count);

    int choice;
    while (1) {
        printf("\n--------反应速度测试--------\n");
        printf("1. 开始游戏\n");
        printf("2. 查看成绩\n");
        printf("0. 退出\n");
        printf("请选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int ms = play_game();
                char save;
                printf("是否保存本次成绩？(y/n)：");
                scanf(" %c", &save);
                if (save == 'y' || save == 'Y') {
                    add_record(rec, &count, ms);
                }
                break;
            }
            case 2:
                show_records(rec, count);
                break;
            case 0:
                printf("程序已退出。\n");
                return 0;
            default:
                printf("输入无效，请重新选择！\n");
        }
    }
}