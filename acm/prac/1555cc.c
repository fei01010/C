#include<stdio.h>
#include<string.h>
#include<limits.h>

#define MAXN 100010

long long row0[MAXN]; //第一行
long long row1[MAXN]; //第二行
long long pre1[MAXN]; //第二行前缀和 pre1[i] = row1[0]~row1[i‑1]
long long suf0[MAXN]; //第一行后缀和 suf0[i] = row0[i]~row0[m‑1]

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int m;
        scanf("%d",&m);
        for(int i=0;i<m;i++) scanf("%lld",&row0[i]);
        for(int i=0;i<m;i++) scanf("%lld",&row1[i]);

        // 第二行前缀和 pre1[0]=0, pre1[1]=row1[0], pre1[2]=row1[0]+row1[1]
        pre1[0]=0;
        for(int i=1;i<=m;i++)
        {
            pre1[i]=pre1[i-1]+row1[i-1];
        }
        //第一行后缀和 suf0[m]=0
        suf0[m]=0;
        for(int i=m-1;i>=0;i--)
        {
            suf0[i]=suf0[i+1]+row0[i];
        }

        long long ans = LLONG_MAX;
        // e 代表爱丽丝在第 e 列(下标0‑m‑1)向下跳
        for(int e=0;e<m;e++)
        {
            long long option1 = pre1[e];       //第二行前 e 个：0~e‑1
            long long option2 = suf0[e+1];     //第一行 e+1 ~ m‑1
            long long bob = (option1>option2)?option1:option2;
            if(bob<ans) ans=bob;
        }
        printf("%lld\n",ans);
    }
    return 0;
}


//本题有一点要注意的地方，就是最终的得分是求bob的得分
//alice在第e列向下走，那么bob最大化得分就有两种可能，即第二行前e-1个，和第一行e+1个及之后的