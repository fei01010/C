#include <stdio.h>
#include <string.h>

#define ROWS 20        // 总排数
#define SEATS 5        // 每排座位数
#define TOTAL 100      // 总座位数（20×5）
char seatChar[] = "ABCDF";  // 座位字母映射
int seats[TOTAL] = {0};     // 座位状态：0=未售，1=已售

// 打印单个座位（索引→排号+字母，如i=0→1A）
void printSeat(int i) {
    printf("%d%c", i/SEATS + 1, seatChar[i%SEATS]);
}

// 分配连续座位（返回1=成功，0=失败）
int assignContiguous(int num) {
    for (int i = 0; i <= TOTAL - num; i++) {
        // 检查当前位置是否在排首，避免跨排连续
        if (i % SEATS > SEATS - num) continue;
        
        // 检查连续num个座位是否全空
        int ok = 1;
        for (int j = 0; j < num && ok; j++) {
            if (seats[i+j]) ok = 0;
        }
        
        // 分配并打印
        if (ok) {
            for (int j = 0; j < num; j++) {
                seats[i+j] = 1;
                if (j) printf(" ");
                printSeat(i+j);
            }
            return 1;
        }
    }
    return 0;
}

// 分配非连续最小空座
void assignNonContiguous(int num) {
    int cnt = 0;
    for (int i = 0; i < TOTAL && cnt < num; i++) {
        if (!seats[i]) {
            seats[i] = 1;
            if (cnt) printf(" ");
            printSeat(i);
            cnt++;
        }
    }
}

int main() {
    int n, times;
    // 读取输入
    scanf("%d", &times);
    for (int t = 0; t < times; t++) {
        scanf("%d", &n);
        // 优先连续，否则非连续
        if (!assignContiguous(n)) {
            assignNonContiguous(n);
        }
        printf("\n");
    }
    return 0;
}