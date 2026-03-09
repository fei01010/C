#include<stdio.h>
#define N1 10000
#define N2 30000
int main(){
    int k,i,cnt=0;
    do{
        //printf("Input a integer ranging from 0 to 1000:");
        scanf("%d",&k);
    }while(k<0||k>1000);
    for(i=N1;i<=N2;i++){
        int sub1,sub2,sub3;
        sub1=i/100;
        int temp1=i/10000;
        sub2=(i-temp1*10000)/10;
        int temp2=i/1000;
        sub3=i-temp2*1000;
        if(sub1%k==0&&sub2%k==0&&sub3%k==0){
            printf("%d\n",i);
            cnt++;
        }
    }
    if(cnt==0){
        printf("No");
    }
    return 0;
}
