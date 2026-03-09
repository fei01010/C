#include<stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    int height[n];
    for(int i=0;i<n;i++){
        scanf("%d",&height[i]);
    }
    int compare[n];//={0};
    for(int i=0;i<n;i++){
        compare[i]=0;
    }
    compare[1]=1;
    compare[n]=0;//比左边的数大，对应1
    for(int i=2;i<n-1;i++){
        if(height[i]>height[i-1])compare[i]=1;
    }

    int cnt=0;
    for(int i=2;i<n-1;i++){
        if(compare[i]==0&&compare[i+1]==1)cnt++;
    }
    printf("%d",cnt);
    //want _ 0 1
    //some cases are as follows:0 0;  0 1;  1 1
    return 0;
}