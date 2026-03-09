#include <stdio.h>
int Cifang(int ,int);

int main(){
    int n,k;
    do{
        printf("Please input n and k :");
        scanf ("%d %d",&n,&k);
    }while(n<=0||k<=0);
    int nk=Cifang(n,k);
    printf("The result is %d",nk);\
    return 0;
}

int Cifang(int n,int k){
    if (k==1)return n;
    else return Cifang(n,k-1)*n;
}