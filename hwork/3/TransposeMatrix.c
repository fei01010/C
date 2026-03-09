#include<stdio.h>
#define N 10
void ReadMatrix(int a[][N],int n);
void Transpose(int a[][N], int n);
void PrintMatrix(int a[][N],int n);
void Swap(int *x, int *y);

int main(){
    int n;
    printf("Input the matrix's dimension:");
    scanf("%d",&n);
    int Matrix[N][N];
    ReadMatrix(Matrix,n);
    Transpose(Matrix,n);
    PrintMatrix(Matrix,n);
    return 0;
}
void ReadMatrix(int a[][N],int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
}
void Transpose(int a[][N],int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=i;j<n;j++){
            Swap(&a[i][j],&a[j][i]);
        }
    }
}
void PrintMatrix(int a[][N],int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d ",a[i][j]);         //最后多输了一个空格，可以先输第一个元。再“ %d"
        }
        printf("\n");
    }
}
void Swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}