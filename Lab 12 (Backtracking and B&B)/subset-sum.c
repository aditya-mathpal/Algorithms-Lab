#include<stdio.h>
#include<stdlib.h>

int count = 1;

void subset_sum(int* arr, int n, int i, int sum, int* subset, int subsetSize) {
    if(!sum) {
        printf("\nsubset %d:\n", count++);
        for(int i = 0; i < subsetSize; i++) {
            printf("%5d", subset[i]);
        }
        return;
    }

    if(sum < 0 || i >= n) return;

    subset[subsetSize] = arr[i];
    subset_sum(arr, n, i+1, sum - arr[i], subset, subsetSize+1);
    subset_sum(arr, n, i+1, sum, subset, subsetSize);
}

int main() {
    int n, sum;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int* arr = (int*)malloc(n*sizeof(n));
    int* subset = (int*)malloc(n*sizeof(n));
    printf("Enter array in ascending order: ");
    for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
    printf("Enter sum of subset: ");
    scanf("%d", &sum);
    subset_sum(arr, n, 0, sum, subset, 0);
    free(arr);
    free(subset);
    return 0;
}

/*
output:
Enter size of array: 5        
Enter array in ascending order: 1 2 5 6 8
Enter sum of subset: 9

subset 1:
    1    2    6
subset 2:
    1    8
*/