#include<stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    long long a[100001];
    for(int i = 0;i <= n;i ++){
        scanf("%lld",&a[i]);
    }
    int cnt = 0;
    for(int i = 0;i <= n - 1;i ++){
        if(a[i] * a[i+1] < 0){
            cnt ++;
        }
    }
    printf("%d",cnt);
    return 0;
}