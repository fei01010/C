#include<stdio.h>
long long factorial(int x){
    if(x==0||x==1)return 1;
    else return x*factorial(x-1);
}
int main(){
    int n;
    scanf("%d",&n);
    if(n>50||n<1){
        scanf("%d",&n);
    }
    long long sum = 0;
    for(int i = 1;i <= n; i++){
        sum += factorial(i);
    }
    printf("%lld",sum);
    return 0;
}