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
    int m, comp = 0;
    printf("Enter size of hash table: ");
    scanf("%d", &m);
    HashTable* ht = createHashTable(m);

    int n, key;
    printf("Enter number of keys to insert: ");
    scanf("%d", &n);
    printf("Enter keys to insert:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(ht, key);
    }
    printf("Keys inserted\n");

    printf("Enter key to search for: ");
    scanf("%d", &key);
    if(search(ht, key, &comp)) printf("Key found\n");
    else printf("Key not found\n");

    printf("Number of comparisons: %d\n", comp);

    return 0;
}

/*
output:
Enter size of hash table: 50
Enter number of keys to insert: 10
Enter keys to insert:
1 2 3 4 5 6 7 8 9 10
Keys inserted
Enter key to search for: 7
Key found
Number of comparisons: 1
*/