#include<stdio.h>
#include<string.h>

int main(){
    char line[256];
    int N = 0;
    int lineCount = 0;
    int counts[40005];
    int countsLen = 0;
    char expected = '0';
    int runCount = 0;

    while (fgets(line, sizeof(line), stdin)){
        int len = (int)strlen(line);//一行数字的个数
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')){
            line[--len] = '\0';
        }
        if (len == 0){
            continue;
        }
        if (N == 0){
            N = len;
        }
        if (len < N){
            continue;
        }
        for (int i = 0; i < N; i++){
            char c = line[i];
            if (c == expected){
                runCount++;
            }else{
                counts[countsLen++] = runCount;
                expected = (expected == '0') ? '1' : '0';
                runCount = 1;
            }
        }
        lineCount++;
        if (lineCount == N){
            break;
        }
    }

    if (N == 0){
        return 0;
    }

    counts[countsLen++] = runCount;

    printf("%d", N);
    for (int i = 0; i < countsLen; i++){
        printf(" %d", counts[i]);
    }
    return 0;
}
