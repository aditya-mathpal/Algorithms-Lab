#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int* arr;
    int size, cap;
} MaxHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MaxHeap* heap, int i, int* opcount) {
    int parent = (i-1)/2;
    while(i > 0 && heap->arr[i] > heap->arr[parent]) {
        (*opcount)++;
        swap(&heap->arr[i], &heap->arr[parent]);
        i = parent;
        parent = (i-1)/2;
    }
}

void insert(MaxHeap* heap, int key, int* opcount) {
    if(heap->size == heap->cap) {
        printf("Heap is full\n");
        return;
    }
    (*opcount)++;
    heap->arr[heap->size] = key;
    heapify(heap, heap->size, opcount);
    heap->size++;
}

int main() {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    printf("Enter size of heap: ");
    int n, opcount = 0;
    scanf("%d", &n);
    heap->cap = n;
    heap->arr = (int*)calloc(n, sizeof(int));
    heap->size = 0;
    printf("Enter elements to build heap (-1 to exit):\n");
    while(1) {
        scanf("%d", &n);
        if(n == -1) break;
        insert(heap, n, &opcount);
    }
    printf("Final heap:\n");
    for(int i = 0; i < heap->size; i++)
        printf("%5d", heap->arr[i]);
    printf("\n%d operations\n", opcount);
    free(heap->arr);
    free(heap);
    return 0;
}

/*
output:
Enter size of heap: 10
Enter elements to build heap (-1 to exit):
2 9 7 6 5 8 -1
Final heap:
    9    6    8    2    5    7
9 operations
*/