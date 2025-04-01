#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

void swap (int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int* arr, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {
    int n, ascOpcount = 0, descOpcount = 0, randOpcount = 0, ascInv = 0, descInv = 0, randInv = 0, *ascArr, *descArr, *randArr;
    printf("Enter size of array: ");
    scanf("%d", &n);

    ascArr = (int*)malloc(n*sizeof(int));
    descArr = (int*)malloc(n*sizeof(int));
    randArr = (int*)malloc(n*sizeof(int));

    for(int i = 0; i < n; i++)
        ascArr[i] = descArr[n-i-1] = randArr[i] = i;
    shuffle(randArr, n);
    //printf("randArr:\n");
    //for(int i = 0; i < n; i++) printf("%d ", randArr[i]);
    //printf("\n");

    mergesort(ascArr, n, &ascOpcount, &ascInv);
    mergesort(descArr, n, &descOpcount, &descInv);
    mergesort(randArr, n, &randOpcount, &randInv);
    //printf("Sorted array:\n");
    //for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("%d asc operations\n%d desc operations\n%d rand operations\n%d asc inversions\n%d desc inversions\n%d rand inversions", ascOpcount, descOpcount, randOpcount, ascInv, descInv, randInv);
    return 0;
}