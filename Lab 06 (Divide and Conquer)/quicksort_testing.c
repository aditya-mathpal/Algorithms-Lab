#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

void shuffle(int* arr, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {
    int n, ascOpcount = 0, descOpcount = 0, randOpcount = 0, *ascArr, *descArr, *randArr;
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

    quicksort(ascArr, 0, n-1, &ascOpcount);
    quicksort(descArr, 0, n-1, &descOpcount);
    quicksort(randArr, 0, n-1, &randOpcount);
    //printf("Sorted array:\n");
    //for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("%d asc operations\n%d desc operations\n%d rand operations\n", ascOpcount, descOpcount, randOpcount);
    return 0;
}