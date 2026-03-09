#include<stdio.h>
#define year0 1990
#define N 3000 
void LeapJudge(int year,int Idxyear[]);
int main(){
    int date[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},
                    {31,29,31,30,31,30,31,31,30,31,30,31}};
    int Idxyear[N]={0};
    int year,month,day;
    scanf("%4d-%2d-%2d",&year,&month,&day);
    int j;
    for(j=year0;j<=year;j++){
        LeapJudge(j,Idxyear);
    }
    
    if(year>=year0){
        if(month>=1&&month<=12){
            if(day>=1&&day<=date[Idxyear[year]][month-1]);
            else {
                printf("Invalid input");
                return 0;
            }
        }else {
            printf("Invalid input");
            return 0;
        }
    }
    int n=year-year0;  
    int uptoday=0;
    if(n==0){
        int i;
        for(i=0;i<month-1;i++){
            uptoday+=date[0][i];
        }
        uptoday+=day;
    }else if(n>0){
        int i=year0;
        for(i=year0;i<year;i++){
            if(Idxyear[i])uptoday+=366;
            else uptoday+=365;
        }
        int k;
        for(k=0;k<month-1;k++){
            uptoday+=date[Idxyear[year]][k];
        }
        uptoday+=day;
    }else {
        printf("Invalid input");
        return 0;
    };
    switch(uptoday%5){
        case 1:
        case 2:
        case 3:printf("working");
                break;
        case 4:
        case 0:printf("rest");
        break;
    }
    return 0;

}
void LeapJudge(int year,int Idxyear[]){
    if (year%4==0&&year%100!=0||(year%400)==0){
        Idxyear[year]=1;
    }
}

