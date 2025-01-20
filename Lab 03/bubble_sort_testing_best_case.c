#include<stdio.h>
#include<stdlib.h>

int* bubbleSort(int* arr, int n, int* opcount) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            (*opcount)++;
            if(arr[j] > arr[j+1]) {
                (*opcount)++;
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return arr;
}

int main() {
    printf("Enter length of array: ");
    int n, opcount = 0;
    scanf("%d",&n);
    int* arr = (int*)malloc(n*sizeof(int));
    printf("Entering elements of array");
    for(int i = 0; i < n; i++) arr[i] = i;
    printf("\nSorting array");
    bubbleSort(arr,n,&opcount);
    printf("\n%d operations\n",opcount);
    return 0;
}