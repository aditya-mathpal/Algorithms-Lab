#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int hash(int key, int tableSize) {
    return key%tableSize;
}

void insert(int* arr, int key, int tableSize) {
    int index = hash(key, tableSize);
    if(arr[index] == -1) arr[index] = key;
    else {
        for(int i = index + 1; i!= index; i++) {
            if(i == tableSize) i = 0;
            if(arr[i] == -1) {
                arr[i] = key;
                break;
            }
        }
    }
}

int search(int* arr, int key, int tableSize, int* comp) {
    (*comp)++;
    int index = hash(key, tableSize);
    if(arr[index] == key) return 1;
    for(int i = (index+1)%tableSize; i!= index; i = (i+1)%tableSize) {
        (*comp)++;
        if(arr[i] == key) return 1;
    }
    return 0;
}

void test(int n, int m) {
    printf("n = %d, m = %d\n", n, m);
    int succ_comp = 0, unsucc_comp = 0;
    // printf("Enter n and m: ");
    // scanf("%d%d", &n, &m);
    int* arr = (int*)malloc(m * sizeof(int));
    for(int i = 0; i<m; i++) arr[i] = -1;

    for(int i = 0; i < n; i++)
        insert(arr, 1+(i+1)*m, m);

    search(arr, 1+(n/2)*m, m, &succ_comp);
    search(arr, 0, m, &unsucc_comp);
    printf("%d comparisons (successful search)\n%d comparisons (unsuccessful search)\n\n", succ_comp, unsucc_comp);
}

int main() {
    int n[] = {50, 100, 200};
    int m[] = {200, 300, 400};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            test(n[j], m[i]);
    return 0;
}

/*
n = 50, m = 200
25 comparisons (successful search)
200 comparisons (unsuccessful search)

n = 100, m = 200
50 comparisons (successful search)
200 comparisons (unsuccessful search)

n = 200, m = 200
100 comparisons (successful search)
200 comparisons (unsuccessful search)

n = 50, m = 300
25 comparisons (successful search)
300 comparisons (unsuccessful search)

n = 100, m = 300
50 comparisons (successful search)
300 comparisons (unsuccessful search)

n = 200, m = 300
100 comparisons (successful search)
300 comparisons (unsuccessful search)

n = 50, m = 400
25 comparisons (successful search)
400 comparisons (unsuccessful search)

n = 100, m = 400
50 comparisons (successful search)
400 comparisons (unsuccessful search)

n = 200, m = 400
100 comparisons (successful search)
400 comparisons (unsuccessful search)
*/