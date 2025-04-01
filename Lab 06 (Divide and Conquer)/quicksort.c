#include<stdio.h>
#include<stdlib.h>

void swap (int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int l, int r, int* opcount) {
    int i = l-1, j = r+1;
    while (1) {
        do {
            i++;
            (*opcount)++;
        } while (arr[i] < arr[l]);

        do {
            j--;
            (*opcount)++;
        } while (arr[j] > arr[l]);

        if (i >= j) {
            (*opcount)++;
            return j;
        }

        (*opcount)++;
        swap(&arr[i], &arr[j]);
    }
}

void quicksort(int* arr, int l, int r, int* opcount) {
    if(l < r) {
        (*opcount)++;
        int p = partition(arr, l, r, opcount);
        quicksort(arr, l, p, opcount);
        (*opcount)++;
        quicksort(arr, p+1, r, opcount);
        (*opcount)++;
    }
}

int main() {
    printf("Enter size of array: ");
    int n, opcount = 0;
    scanf("%d", &n);
    int* arr = (int*)malloc(n*sizeof(arr));
    printf("Enter elements of array: ");
    for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
    quicksort(arr, 0, n-1, &opcount);
    printf("Sorted array:\n");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n%d operations\n", opcount);
    return 0;
}

/*
output:
Enter size of array: 5
Enter elements of array: 3 2 1 4 5
Sorted array:
1 2 3 4 5
36 operations
*/