#include<stdio.h>

int main(){
    //t 是测试用例的数量
    int t;
    scanf("%d", &t);
    
    //m 是列数
    int m;
    scanf("%d", &m);
    //2 行 m 列的二维数组
    int a[2][m];
    for(int i=0; i<2; i++){
        for(int j=0; j<m; j++){
            scanf("%d", &a[i][j]);
        }
    }
    // 之后解决路线问题
    //ailce走的是最小化得分，需要解决的问题是什么时候要向下走
    //假定在第e列向下走，问题转化为第一行前e个和第二行e以后总和的比较
    int sum = -1, al = 0;
    for(int e=0; e<m; e++){
        for(int j=0; j<m; j++){
            if(j < e){
                sum += a[0][j];
            }else{
                sum += a[1][j];
            }
        }
        if(e>0){
            sum += a[1][e-1];
        }
        if(sum < al){
            al = sum;
        }
    }
}