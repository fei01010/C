#include<stdio.h>
int Readscore(int score[]);
void Printfscore(int score[],int n);
void Selectmode(int score[],int n,int (*button)(int a,int b));
int Ascendingmode(int a,int b);
int Descendingmode(int a,int b);
void Wasp(int*a,int *b);
#define N 40
int main(){
    int score[N];
    int n;
    printf("Please input the students' scores:");
    n = Readscore(score);                                   //计算学生数量
    printf("The total number of the stu is %d\n",n);

    printf("Type 1 to printf ascending scores.\n");
    printf("Type 2 to printf descending scores.\n");
    int order;
    do{
        scanf("%d",&order);
    }while(order!=1&&order!=2);

    if(order==1){
        printf("The ascending scores are:\n");
        Selectmode(score,n,Ascendingmode);
    }
    if(order==2){
        printf("The descending scores are:\n");
        Selectmode(score,n,Descendingmode);
    }
    Printfscore(score,n);
    return 0;

}

int Readscore(int score[]){
    int i=-1;
    do{
        i++;
        scanf("%d",&score[i]);
    }while(score[i]>=0);
    return i;
}

void Printfscore(int score[],int n){
    int i;
    for(i=0;i<n;i++){
        printf ("%d ",score[i]);
    }
}

void Selectmode(int score[],int n,int (*button)(int a,int b)){
    int i,j,k;
    for(i=0;i<n-1;i++){
        k=i;
        for(j=i+1;j<n;j++){
            if(button(score[j],score[k]))k=j;
        }
        if (k!=i) Wasp(&score[i],&score[k]);
    }
}

int Ascendingmode(int a,int b){
    return a<b;
}

int Descendingmode(int a,int b){
    return a>b;
}

void Wasp(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}