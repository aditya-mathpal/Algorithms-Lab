#include<stdio.h>
#include<stdlib.h>

int* bubbleSort(int* arr, int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
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
    int n;
    scanf("%d",&n);
    int* arr = (int*)malloc(n*sizeof(int));
    printf("Enter elements of array: ");
    for(int i = 0; i < n; i++) scanf("%d",&arr[i]);
    printf("Entered array is: ");
    for(int i = 0; i < n; i++) printf("%d ",arr[i]);
    bubbleSort(arr,n);
    printf("\nSorted array: ");
    for(int i = 0; i < n; i++) printf("%d ",arr[i]);
    printf("\n");
    return 0;
}

/*
output:
Enter length of array: 5
Enter elements of array: 3 5 1 4 2
Entered array is: 3 5 1 4 2 
Sorted array: 1 2 3 4 5 

time efficiency:

*/
