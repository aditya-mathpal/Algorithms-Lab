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
    printf("Enter elements of array: ");
    for(int i = 0; i < n; i++) scanf("%d",&arr[i]);
    printf("Entered array is: ");
    for(int i = 0; i < n; i++) printf("%d ",arr[i]);
    bubbleSort(arr,n,&opcount);
    printf("\nSorted array: ");
    for(int i = 0; i < n; i++) printf("%d ",arr[i]);
    printf("\n%d operations\n",opcount);
    return 0;
}

/*
output:
Enter length of array: 5
Enter elements of array: 3 5 1 4 2
Entered array is: 3 5 1 4 2 
Sorted array: 1 2 3 4 5
16 operations

time efficiency:
Due to the number of iterations and swaps the algorithm has to produce, it has a time complexity of omega(n), theta(n^2), and O(n^2) where n is the length of the array.
*/