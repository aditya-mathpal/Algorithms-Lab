#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int weight;
    double ratio;
} Item;

typedef struct {
    int level;
    int profit;
    int weight;
    double bound;
} Node;

int partition(Item* arr, int l, int r) {
    double pivot = arr[l].ratio;
    int i = l-1, j = r+1;
    while(1) {
        do {
            i++;
        } while(arr[i].ratio > pivot);
        do {
            j--;
        } while(arr[j].ratio < pivot);
        if(i >= j) return j;
        Item temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void quicksort(Item* arr, int l, int r) {
    if(l<r) {
        int p = partition(arr, l, r);
        quicksort(arr, l, p);
        quicksort(arr, p+1, r);
    }
}

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Node *pq, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && pq[left].bound > pq[largest].bound)
        largest = left;
    if (right < n && pq[right].bound > pq[largest].bound)
        largest = right;
    if (largest != i) {
        swap(&pq[i], &pq[largest]);
        heapify(pq, n, largest);
    }
}

Node extractMax(Node *pq, int *n) {
    Node max = pq[0];
    pq[0] = pq[*n - 1];
    (*n)--;
    heapify(pq, *n, 0);
    return max;
}

void insert(Node *pq, int *n, Node item) {
    (*n)++;
    int i = *n - 1;
    pq[i] = item;
    while (i > 0 && pq[(i - 1) / 2].bound < pq[i].bound) {
        swap(&pq[i], &pq[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

double bound(Node u, int n, int W, Item items[]) {
    if (u.weight >= W) return 0;
    double bound_value = u.profit;
    int j = u.level + 1;
    int total_weight = u.weight;
    while (j < n && total_weight + items[j].weight <= W) {
        total_weight += items[j].weight;
        bound_value += items[j].value;
        j++;
    }
    if (j < n) bound_value += (W - total_weight) * items[j].ratio;
    return bound_value;
}

int knapsack(int n, Item items[], int W) {
    for (int i = 0; i < n; i++)
        items[i].ratio = (double)items[i].value / items[i].weight;
    quicksort(items, 0, n-1);
    Node *pq = (Node *)malloc(sizeof(Node) * 10000);
    int pq_size = 0;
    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = bound(u, n, W, items);
    insert(pq, &pq_size, u);
    int max_profit = 0;
    while (pq_size > 0) {
        u = extractMax(pq, &pq_size);
        if (u.bound <= max_profit) continue;
        if (u.level == n - 1) continue;
        v.level = u.level + 1;
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        if (v.weight <= W && v.profit > max_profit)
            max_profit = v.profit;
        v.bound = bound(v, n, W, items);
        if (v.bound > max_profit && v.weight <= W)
            insert(pq, &pq_size, v);
        v.level = u.level + 1;
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, items);
        if (v.bound > max_profit) insert(pq, &pq_size, v);
    }
    free(pq);
    return max_profit;
}

int main() {
    int n, W;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    Item *items = (Item *)malloc(sizeof(Item) * n);
    printf("Enter the weight and value of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &items[i].weight, &items[i].value);
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &W);
    int max_profit = knapsack(n, items, W);
    printf("Maximum profit: %d\n", max_profit);
    free(items);
    return 0;
}

/*
output:
Enter the number of items: 4
Enter the weight and value of items:
4 40 7 42 5 25 3 12
Enter the capacity of the knapsack: 10
Maximum profit: 65
*/