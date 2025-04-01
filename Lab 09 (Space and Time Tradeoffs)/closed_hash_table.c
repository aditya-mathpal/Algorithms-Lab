#include<stdio.h>
#include<stdlib.h>

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

int main() {
    int m, n, key, comp = 0;
    printf("Enter size of table: ");
    scanf("%d", &m);
    int* arr = (int*)malloc(m * sizeof(int));
    for(int i = 0; i<m; i++) arr[i] = -1;

    printf("Enter number of keys to add: ");
    scanf("%d", &n);
    printf("Enter keys: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(arr, key, m);
    }

    printf("Enter key to search: ");
    scanf("%d", &key);
    if(search(arr, key, m, &comp)) printf("Key found\n");
    else printf("Key not found\n");
    printf("%d comparisons\n", comp);
    return 0;
}

/*
output:
Enter size of table: 10
Enter number of keys to add: 10
Enter keys: 1 3 5 7 9 11 13 15 17 19
Enter key to search: 13
Key found
2 comparisons
*/