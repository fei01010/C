#include<stdio.h>

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        int b[105]={0};
        int a[205]={0};
        scanf("%d", &n);
        for(int i=0; i<n; i++){
            scanf("%d", &b[i]);
        }
        int bool = 1;
        for(int i=0; i<n; i++){
            a[i*2] = b[i];
            //一般情况下是直接加1，但是若加1的数字已经在b序列，则再加一，直到该数字不在b数组中，若超过2n则没有
            int act = 1;
            do{
                a[i*2+1] = b[i] + 1;
                if(a[i*2+1] > n*2){
                    bool=0;
                    break;
                }
                act = 0;
                for(int j=0; j<n; j++){
                    if(a[j] == a[i*2+1]){
                        act = 1;
                        a[i*2+1]++;
                        if(a[i*2+1] > n*2){
                            bool = 0;
                            act = 0;
                        }
                        break;
                    }
                }
            }while(act);
        }
        if(bool){
            for(int i=0; i<n*2; i++){
                printf("%d ", a[i]);
            }
        }else{
            printf("-1");
        }
    }
    return 0;
}