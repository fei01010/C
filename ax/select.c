#include <stdio.h>
int main() {
    int arr[10] = {29, 10, 14, 37, 13, 5, 40, 8, 33, 2};
    int n = 10;

    // TODO：简单选择排序
    for (int i = 0; i < n - 1; i++) { 
        int min_index=i;
        int j;
        int temp=arr[i];
        for(j=i+1;j<n;j++){
            if(arr[j]<arr[min_index]){
                min_index=j;
            }
        }
        arr[i]=arr[min_index];
        arr[min_index]=temp;
    }

    printf("result:");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}