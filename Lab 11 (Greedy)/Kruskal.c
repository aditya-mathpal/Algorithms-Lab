#include<stdio.h>
#include<stdlib.h>

// a struct to store edge data
typedef struct {
    int u, v, weight;
} edge;

int partition(edge* arr, int l, int r) {
    int i = l-1, j = r+1;
    while(1) {
        do {
            i++;
        } while(arr[i].weight < arr[l].weight);
        do {
            j--;
        } while(arr[j].weight > arr[l].weight);
        if(i >= j) return j;
        edge temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void quicksort(edge* arr, int l, int r) {
    if(l<r) {
        int p = partition(arr, l, r);
        quicksort(arr, l, p);
        quicksort(arr, p+1, r);
    }
}

void makeSet(int* parent, int* rank, int x) {
    parent[x] = x;
}

int find(int* parent, int x) {
    if(parent[x] != x) parent[x] = find(parent, parent[x]);
    return parent[x];
}

void setUnion(int* parent, int* rank, int x, int y) {
    int rootX = find(parent, x), rootY = find(parent, y);
    if(rootX != rootY) {
        if(rank[rootX] > rank[rootY]) parent[rootY] = rootX;
        else if(rank[rootY] > rank[rootX]) parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d%d", &V, &E);
    edge* arr = (edge*)malloc(E*sizeof(edge));
    int* parent = (int*)malloc(V*sizeof(int));
    int* rank = (int*)calloc(V, sizeof(int)); // sets all ranks to 0
    edge* mst = (edge*)malloc((V-1)*sizeof(edge));
    printf("Enter all edges in tuples of <u> <v> <weight>:\n");
    for(int i = 0; i < E; i++)
        scanf("%d%d%d", &arr[i].u, &arr[i].v, &arr[i].weight);

    quicksort(arr, 0, E-1);

    for(int i = 0; i < V; i++) makeSet(parent, rank, i);
    int j = 0;

    for(int i = 0; i < E && j < V-1; i++) {
        if(find(parent, arr[i].u) != find(parent, arr[i].v)) {
            mst[j++] = arr[i];
            setUnion(parent, rank, arr[i].u, arr[i].v);
        }
    }

    printf("The minimum cost spanning tree contains the following edges:\n");
    for(int i = 0; i < V-1; i++)
        printf("u: %d\t v: %d\t weight: %d\n", mst[i].u, mst[i].v, mst[i].weight);
    
    free(arr);
    free(parent);
    free(rank);
    free(mst);
    return 0;
}

/*
output:
Enter number of vertices and edges: 6 10
Enter all edges in tuples of <u> <v> <weight>:
0 1 3
0 4 6
0 5 5
1 5 4
5 4 2
2 5 4
1 2 1
2 3 6
5 3 5
3 4 8
The minimum cost spanning tree contains the following edges:
u: 1     v: 2    weight: 1
u: 5     v: 4    weight: 2
u: 0     v: 1    weight: 3
u: 2     v: 5    weight: 4
u: 5     v: 3    weight: 5
*/

/*
time efficiency analysis:
The most expensive operation is sorting, which has a time complexity of \Theta(E log E) if impelmented optimally (quicksort in this case).
*/