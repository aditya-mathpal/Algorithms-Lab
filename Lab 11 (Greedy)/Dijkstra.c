#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define inf INT_MAX

typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    int V;
    Edge** array;
} Graph;

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (Edge**)malloc(V * sizeof(Edge*));
    for (int i = 0; i < V; i++)
        graph->array[i] = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->array[src];
    graph->array[src] = newEdge;
    newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = src;
    newEdge->weight = weight;
    newEdge->next = graph->array[dest];
    graph->array[dest] = newEdge;
}

typedef struct {
    int v;
    int dist;
} MinHeapNode;

typedef struct {
    int size;
    int capacity;
    int *pos;
    MinHeapNode **array;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;
    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return NULL;
    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    minHeap->size--;
    minHeapify(minHeap, 0);
    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap *minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int *dist = (int*)malloc(V * sizeof(int));
    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = inf;
        minHeap->array[v] = (MinHeapNode*)malloc(sizeof(MinHeapNode));
        minHeap->array[v]->v = v;
        minHeap->array[v]->dist = inf;
        minHeap->pos[v] = v;
    }

    minHeap->array[src]->dist = 0;
    dist[src] = 0;
    minHeap->size = V;
    decreaseKey(minHeap, src, 0);

    while (minHeap->size > 0) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        if (!minHeapNode) break; // Prevent null pointer access
        int u = minHeapNode->v;
        free(minHeapNode);

        Edge* crawl = graph->array[u];
        while (crawl != NULL) {
            int v = crawl->dest;

            if (isInMinHeap(minHeap, v) && dist[u] != inf && crawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + crawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            crawl = crawl->next;
        }
    }

    for (int i = 0; i < V; i++)
        printf("vertex %d: distance %d\n", i, dist[i]);

    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
    free(dist);
}


int main() {
    int V, E, u, v, w, src;
    printf("Enter number of verticies and edges: ");
    scanf("%d%d", &V, &E);
    Graph* graph = createGraph(V);
    printf("Enter all edges in tuples of <u> <v> <weight>:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d%d%d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }
    printf("Enter source vertex: ");
    scanf("%d", &src);
    dijkstra(graph, src);

    for (int i = 0; i < V; i++) {
        Edge* edge = graph->array[i];
        while (edge != NULL) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
    return 0;
}

/*
output:
Enter number of verticies and edges: 5 7
Enter all edges in tuples of <u> <v> <weight>:
0 1 3
0 3 7
1 3 2
1 2 4
2 3 5
3 4 4
2 4 6
Enter source vertex: 0
vertex 0: distance 0
vertex 1: distance 3
vertex 2: distance 7
vertex 3: distance 5
vertex 4: distance 9
*/

/*
time efficiency analysis:
The most expensive operation is the decreaseKey function, which operates in O(E log V) in the worst case.
*/