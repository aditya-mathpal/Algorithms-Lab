#include<stdio.h>
#include<stdlib.h>

typedef struct list {
    int data;
    struct list* next;
} LinkedList;

typedef struct hash_table {
    LinkedList** table;
    int size;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (LinkedList**)malloc(size * sizeof(LinkedList*));
    for(int i = 0; i < size; i++) ht->table[i] = NULL;
    return ht;
}

int hash(int key, int size) {
    return key%size;
}

int search(HashTable* ht, int key, int* comp) {
    int index = hash(key, ht->size);
    LinkedList* temp = ht->table[index];
    while(temp != NULL) {
        (*comp)++;
        if(temp->data == key) return 1;
        temp = temp->next;
    }
    return 0;
}

int insert(HashTable* ht, int key) {
    int index = hash(key, ht->size);
    LinkedList* new_node = (LinkedList*)malloc(sizeof(LinkedList));
    new_node->data = key;
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
    return 1;
}

int main() {
    int n, m, successful_comp = 0, unsuccessful_comp = 0;
    printf("Enter n and m: ");
    scanf("%d%d", &n, &m);
    HashTable* ht = createHashTable(m);

    for(int i = 0; i < n; i++) insert(ht, i+1);

    search(ht, n/2, &successful_comp);
    search(ht, n + 5, &unsuccessful_comp);

    printf("Number of comparisons (successful search): %d\nNumber of comparisons (unsuccessful search): %d\n", successful_comp, unsuccessful_comp);

    return 0;
}