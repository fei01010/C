#include<stdio.h>
#include<stdlib.h>
int main(){
    int i,n;
    do{
        scanf("%d",&n);
    }while(n<2||n>1000);
    int a[n];
    for(i=0;i<n;i++){
        scanf(" %d",&a[i]);
    }
    int b[n-1];
    i=0;
    for(i=0;i<n-1;i++){
        b[i]=abs(a[i]-a[i+1]);
    }
    int m,k;
    i=0;
    int cnt[n];
    for(i=0;i<n;i++){
        cnt[i]=0;
    }
    for(m=0;m<n-1;m++){
        if(b[m]<1||b[m]>n-1){
            printf("Not jelly");
            return 0;
        }
        cnt[b[m]]++;
    }
    for(k=1;k<n;k++){
        if(cnt[k]!=1){
            printf("Not jelly");
            return 0;
        }
    }
    printf("Jelly");
    return 0;
}