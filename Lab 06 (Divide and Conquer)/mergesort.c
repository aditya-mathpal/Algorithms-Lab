#include<stdio.h>
#include<stdlib.h>

void merge(int* arr, int* b, int* c, int n, int* opcount, int* inv) {
    int i = 0, j = 0, k = 0, bSize = n/2, cSize = (n+1)/2;
    while(i < bSize && j < cSize) {
        if(b[i] <= c[j]) {
            arr[k] = b[i];
            k++, i++;
        }
        else {
            (*inv) += (bSize - i);
            arr[k] = c[j];
            k++, j++;
        }
        (*opcount)++;
    }
    while(j < cSize) {
        arr[k] = c[j];
        k++, j++;
        (*opcount)++;
    }
    while(i < bSize) {
        arr[k] = b[i];
        k++, i++;
        (*opcount)++;
    }
}

void mergesort(int* arr, int n, int* opcount, int* inv) {
    (*opcount)++;
    if(n > 1){
        // printf("\narr: ");
        // for(int i = 0; i < n; i++) printf("%d ", arr[i]);
        int bSize = n/2, cSize = (n+1)/2;
        int* b = (int*)malloc((bSize)*sizeof(int));
        int* c = (int*)malloc((cSize)*sizeof(int));
        int i = 0;
        while(i < bSize) {
            b[i] = arr[i];
            i++;
        }
        (*opcount)++;
        for(int j = 0; j < cSize; j++, i++) c[j] = arr[i];
        (*opcount)++;
        // printf("\nB: ");
        // for(int i = 0; i < bSize; i++) printf("%d ", b[i]);
        // printf("\nC: ");
        // for(int i = 0; i < cSize; i++) printf("%d ", c[i]);
        mergesort(b, bSize, opcount, inv);
        mergesort(c, cSize, opcount, inv);
        merge(arr, b, c, n, opcount, inv);
        free(b);
        free(c);
    }
}

int main() {
    printf("Enter size of array: ");
    int n, opcount = 0, inv = 0;
    scanf("%d", &n);
    int* arr = (int*)malloc(n*sizeof(int));
    printf("Enter elements of array: ");
    for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
    mergesort(arr, n, &opcount, &inv);
    printf("\nSorted array:\n");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n%d operations\n%d inversions\n", opcount, inv);
    free(arr);
    return 0;
}

/*
output:
Enter size of array: 5
Enter elements of array: 3 2 1 4 5

Sorted array:
1 2 3 4 5
29 operations
3 inversions
*/