#include<stdio.h>
int Readscore(int score[]);
double Average(int score[],int n);
int Judge(int score[],int n,double average);
#define N 40
int main(){
    int score[N];
    int n;
    n=Readscore(score);
    double average=Average(score,n);
    int cnt=Judge(score,n,average);
    printf("%d",cnt);
    return 0;
}


int Readscore(int score[]){
    int i=-1;
    do{
        i++;
        scanf("%d",&score[i]);
    }while(score[i]>=0);
    return i;
}

double Average(int score[],int n){
    int sum=0,i;
    for (i=0;i<n;i++){
        sum+=score[i];
    }
    return sum/(n*1.0);
}

int Judge(int score[],int n,double average){
    int cnt=0,i;
    for(i=0;i<n;i++){
        if(score[i]>average)cnt++;
    }
    return cnt;
}