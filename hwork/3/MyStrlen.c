#include<stdio.h>
#define N 100
unsigned int MyStrlen(char p[ ])
{
    unsigned int len;
    len=0;
    for ( ; p[len]!='\0'; ){
        len ++;
	}
    return len;
}

int main(){
    int len;
    char str[N];
    printf("Input a string:");
    gets(str);
    len=MyStrlen(str);
    printf("The length of the string is:%d",len);
    return 0;
}
