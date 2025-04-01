#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int* arr;
    int size;
} MaxHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MaxHeap* heap, int i, int* opcount) {
    int largest = i, left = 2*i, right = 2*i + 1;
    if(left <= heap->size && heap->arr[left] > heap->arr[largest])
        largest = left;
    if(right <= heap->size && heap->arr[right] > heap->arr[largest])
        largest = right;
    if(largest != i) {
        (*opcount)++;
        swap(&heap->arr[i], &heap->arr[largest]);
        heapify(heap, largest, opcount);
    }
}

void buildHeap(MaxHeap* heap, int* opcount) {
    for(int i = heap->size/2; i >= 1; i--)
        heapify(heap, i, opcount);
}

void heapSort(MaxHeap* heap, int* opcount) {
    int originalSize = heap->size;
    for(int i = heap->size; i > 1; i--) {
        (*opcount)++;
        swap(&heap->arr[1], &heap->arr[i]);
        heap->size--;
        heapify(heap, 1, opcount);
    }
    heap->size = originalSize;
}

int main() {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    printf("Enter size of heap: ");
    int n, opcount = 0;
    scanf("%d", &n);
    heap->arr = (int*)calloc(n+1, sizeof(int));
    heap->size = n;
    printf("Enter elements of the array:\n");
    for(int i = 1; i <= n; i++) scanf("%d", &heap->arr[i]);
    buildHeap(heap, &opcount);
    printf("Final heap:\n");
    for(int i = 1; i <= heap->size; i++)
        printf("%5d", heap->arr[i]);
    heapSort(heap, &opcount);
    printf("\nSorted array:\n");
    for(int i = 1; i <= heap->size; i++)
        printf("%5d", heap->arr[i]);
    printf("\n%d operations\n", opcount);
    free(heap->arr);
    free(heap);
    return 0;
}

/*
output:
Enter size of heap: 6
Enter elements of the array:
9 6 8 2 5 7
Final heap:
    9    6    8    2    5    7
Sorted array:
    2    5    6    7    8    9
8 operations
*/