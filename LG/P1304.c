#include<stdio.h>
#include<math.h>
#include<ctype.h>
int main(){
    //输入N
    int n;
    do{
        scanf("%d",&n);
    }while(n<4||n%2!=0);
    //寻找素数
    int m=n/2;
    int pri[m];
    //memset(pri,0,sizeof(int));
    for(int i=0;i<m;i++){
        pri[i]=0; 
    }
    pri[0]=2;

    int cnt=1;
    for(int i=3;i<n;i+=2){
        int find=1;//
        for(int j=3;j<=sqrt(i);j+=2){
            if(i%j==0){
                find=0;
                break;
            }
        }
        if(find)pri[cnt++]=i;
    }

    //遍历4-N的所有偶数
    for(int i=4;i<=n;i+=2){
        //对每一个i，寻找其质数之和
        int check=0;
        for(int k=0;pri[k]<=i/2&&k<m;k++){
            for(int l=k;l<cnt;l++){
                if(pri[k]+pri[l]==i){
                    printf("%d=%d+%d\n",i,pri[k],pri[l]);
                    check=1;
                    break;
                }
            }
            if(check)break;
        }
    }
    // for(int i=0;i<m;i++){
    //     printf("%d ",pri[i]);
    // }
    return 0;
}


// 题目描述
// 输入一个偶数 N，验证 4∼N 所有偶数是否符合哥德巴赫猜想：任一大于 2 的偶数都可写成两个质数之和。如果一个数不止一种分法，则输出第一个加数相比其他分法最小的方案。例如 10，10=3+7=5+5，则 10=5+5 是错误答案。

// 输入格式
// 第一行输入一个正偶数 N

// 输出格式
// 输出  
// 2
// N−2
// ​
//   行。对于第 i 行：

// 首先先输出正偶数 2i+2，然后输出等号，再输出加和为 2i+2 且第一个加数最小的两个质数，以加号隔开。

// 输入输出样例
// 输入 #1复制

// 10
// 输出 #1复制

// 4=2+2
// 6=3+3
// 8=3+5
// 10=3+7
// 说明/提示
// 数据保证，4≤N≤10000。