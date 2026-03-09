#include <stdio.h>
int main() {
    int arr[10] = {23, 5, 12, 7, 31, 19, 1, 8, 15, 4};
    int n = 10;

    // TODO：直接插入排序
    for (int i = 1; i < n; i++) { 
        int temp=arr[i];
        int j=i-1;
        while(j>=0&&arr[j]>temp){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=temp;
    }

    printf("result:");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}