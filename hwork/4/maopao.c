#include <stdio.h>
int main()
{
    int arr[6] = {9, 3, 7, 1, 6, 2};
    int n = 6;
    int i,j;
    for(i=0;i<n;i++){
        for(j=n;j>i;j--){
            if(arr[j]<arr[j-1]){
                int temp=arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=temp;
            }
        }
    }
    i=0;
    for(i=0;i<6;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}