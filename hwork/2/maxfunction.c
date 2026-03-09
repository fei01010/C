#include<stdio.h>
int Max(int a,int b){
    if (a >= b) return a;
    else return b;
}

int main(){
    int a,b;
    int max;
    scanf("%d %d",&a,&b);
    max=Max(a,b);
    printf("%d",max);
    return 0;

}