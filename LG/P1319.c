#include<stdio.h>

int main(){
    int n;//列数
    scanf("%d",&n);
    while(n<1){
        printf("please input a positive integer\n");
        scanf("%d",&n);
    }//边界检测

    int d;//记录临时输入
    int c;
    int sum = 0;//判断当前输入个数和
    int id = 0;//为0输出0,为1输出1
    while((c = scanf("%d", &d)) != EOF){
        if(!id){    
            for(int j=1;j<=d;j++){
                printf("0");
                if((sum + j)% n == 0){
                    printf("\n");
                }
            }
            id = 1;
        }else{
            for(int j=1;j<=d;j++){
                printf("1");
                if((sum + j) % n == 0){
                    printf("\n");
                }
            }
            id = 0;
        }    
        sum += d;
        if(sum > n*n){
            printf("错误的输入\n");
            return 0;
        }else if(sum == n*n){
            break;
        }
    }
    return 0;
}