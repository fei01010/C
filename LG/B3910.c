#include<stdio.h>
#include<stdlib.h>

int main(){
    int m;
    scanf("%d",&m);
    if(m < 1 || m > 100000){
        printf("error!");
        return 0;
    }
    int n = m + 1;
    int a[n];
    for(int i = 0;i < n;i ++){
        scanf("%d",&a[i]);
        if(a[i] == 0 || abs(a[i]) > 1000000000){
            printf("error!");
            return 0;
        }
    }
    int cnt = 0;
    for(int i = 0;i < n - 1;i ++){
        if(a[i] * a[i+1] < 0){
            cnt ++;
        }
    }
    printf("%d",cnt);
    return 0;
}