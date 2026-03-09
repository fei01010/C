#include<stdio.h>
#include<ctype.h>
#define N 100

int main(){
    char c;
    char str[N];
    int i=0;
    while(c=getchar()!='='&&c!=EOF){
        str[i++]=c;
    }
    str[i]='\0';

    i=0;
    int tempNum=0;
    if(isdigit(i)){
        tempNum=tempNum*10+(str[i]-'0');
        i++;
    }
    
    
}