#include<stdio.h>
int Commonmultiple(int ,int );

int main(){
    int a,b;
    do{
        printf("Please input two positive integers:");
        scanf("%d %d",&a,&b);
    }while(a<=0||b<=0);
    int lcm=Commonmultiple(a,b);
    printf("The LCM is %d",lcm);
    return 0;

}

int Commonmultiple(int a,int b){
    int basenumber;
    basenumber = a >= b ? a : b;
    while (!(basenumber%a==0&&basenumber%b==0)){
        basenumber++;
    }
    return basenumber;
}