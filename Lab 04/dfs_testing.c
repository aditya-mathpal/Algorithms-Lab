#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int vertices;
    int adjMatrix[100][100];
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0;

    return graph;
}

void addEdge(Graph* graph, int u, int v) {
    graph->adjMatrix[u][v] = 1;
    graph->adjMatrix[v][u] = 1;
}

void dfs(Graph* graph, int start, int visited[], int* pushOrder, int* popOrder, int* pushIndex, int* popIndex, int* opcount) {
    visited[start] = 1;
    pushOrder[(*pushIndex)++] = start;

    for (int i = 0; i < graph->vertices; i++) {
        (*opcount)++;
        if (graph->adjMatrix[start][i] == 1 && !visited[i])
            dfs(graph, i, visited, pushOrder, popOrder, pushIndex, popIndex, opcount);
    }

    popOrder[(*popIndex)++] = start;
}

int main() {
    printf("Enter number of tests: ");
    int t;
    scanf("%d", &t);
    printf("Enter number of vertices for each test: ");
    while(t--) {
        int n, opcount = 0;
        scanf("%d", &n);
        Graph* graph = createGraph(n);
        for(int i = 0; i < n; i++) {
            addEdge(graph, i, i+1);
        }
        int visited[100] = {0};
        int pushOrder[100], popOrder[100];
        int pushIndex = 0, popIndex = 0;
        
        dfs(graph, 0, visited, pushOrder, popOrder, &pushIndex, &popIndex, &opcount);

        printf("%d vertices: %d operations\n", n, opcount);

        free(graph);
    }
    return 0;
}