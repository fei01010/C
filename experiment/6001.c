#include<stdio.h>
#include<string.h>
#define N 100
#define M 20
typedef struct scores{
    int score[M];
    double final;
}SCORES;

int main(){
    int m,n;
    //输入m,n
    do{
        scanf("%d %d",&n,&m);
    }while(n<1||n>N||m<3||m>M);
    SCORES stu[n];
    //初始化score
    // for(int i=0;i<M;i++){
    //     memset(stu[i].score,0,M*sizeof(stu[0].score[0]));
    // }
    
    
    
    // 输入成绩
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                do {
                    scanf("%d", &stu[i].score[j]);
                } while (stu[i].score[j] < 0 || stu[i].score[j] > 10);
            }
    }

    //给成绩最大和最小值赋值为0；
    //计算平均分
    for(int i=0;i<n;i++){
        int low_index=0,high_index=0;
        for(int j=0;j<m;j++){
            if(stu[i].score[j]<stu[i].score[low_index]){
                low_index=j;
            }
            if(stu[i].score[j]>stu[i].score[high_index]){
                high_index=j;
            }
        }
        if(low_index!=high_index){
            stu[i].score[low_index]=0;
            stu[i].score[high_index]=0;
        }else{
            stu[i].score[low_index]=0;
            stu[i].score[high_index+1]=0;
        }

        double sum=0;
        for(int j=0;j<m;j++){
            sum+=stu[i].score[j];
        }
        stu[i].final=1.0*sum/(m-2);
    }
    int idx=0;
    for(int i=0;i<n;i++){
        if(stu[i].final>stu[idx].final){
            idx=i;
        }
    }
    printf("%.2f",stu[idx].final);
    return 0;
}

// n(n≤100)名同学参加歌唱比赛，并接受 m(m≤20)名评委的评分，评分范围是 0到 10分。这名同学的得分就是这些评委给分中去掉一个最高分，去掉一个最低分，剩下 m-2 个评分的平均数。请问得分最高的同学分数是多少？评分保留 2 位小数。
// 【输入描述】

// 第一行两个整数 n, m。
// 接下来 n 行，每行各 m个整数，表示得分。

// 【输出描述】

// 输出分数最高的同学的分数，保留两位小数。

// 【输入示例】

// 7 6
// 4 7 2 6 10 7
// 0 5 0 10 3 10
// 2 6 8 4 3 6
// 6 3 6 7 5 8
// 5 9 3 3 8 1
// 5 9 9 3 2 0
// 5 8 0 4 1 10
// 【输出示例】

// 6.00