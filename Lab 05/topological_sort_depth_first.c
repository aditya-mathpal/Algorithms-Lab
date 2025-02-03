#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int vertices;
    int adjMatrix[100][100];
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    
    for(int i = 0; i < vertices; i++)
        for(int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0;

    return graph;
}

void addEdge(Graph* graph, int u, int v) {
    graph->adjMatrix[u][v] = 1;
    graph->adjMatrix[v][u] = 1;
}

typedef struct Stack {
    int arr[100];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

