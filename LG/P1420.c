#include<stdio.h>

#define N0 10000
#define N1 1000000000

int main(){
    int n;
    if(scanf("%d", &n) != 1){
        return 0;
    }
    if(n < 1 || n > N0){
        printf("incorrect input");
        return 0;
    }

    int prev;
    if(scanf("%d", &prev) != 1){
        return 0;
    }
    if(prev < 1 || prev > N1){
        return 0;
    }

    int max_len = 1;
    int cur_len = 1;
    for(int i = 1; i < n; i++){
        int cur;
        if(scanf("%d", &cur) != 1){
            return 0;
        }
        if(cur < 1 || cur > N1){
            return 0;
        }
        if(cur == prev + 1){
            cur_len++;
            if(cur_len > max_len){
                max_len = cur_len;
            }
        }else{
            cur_len = 1;
        }
        prev = cur;
    }

    printf("%d", max_len);
    return 0;
}