#include<stdio.h>

int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    int cnt=n;
    int rest=cnt;
    while(rest>=k){
        rest-=k;
        cnt++;
        rest++;
    }
    printf("%d",cnt);
    return 0;
}