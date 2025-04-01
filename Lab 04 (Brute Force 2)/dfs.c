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
    printf("Pushed: %d\n", start);

    for (int i = 0; i < graph->vertices; i++) {
        (*opcount)++;
        if (graph->adjMatrix[start][i] == 1 && !visited[i])
            dfs(graph, i, visited, pushOrder, popOrder, pushIndex, popIndex, opcount);
    }

    popOrder[(*popIndex)++] = start;
    printf("Popped: %d\n", start);
}

int main() {
    printf("Enter number of vertices: ");
    int n, t1, t2, opcount = 0;
    scanf("%d", &n);
    Graph* graph = createGraph(n);
    printf("Enter edges of the graph (input vertex numbers, -1 to cancel): ");
    while(1) {
        scanf("%d", &t1);
        if(t1 == -1) break;
        scanf("%d", &t2);
        addEdge(graph, t1, t2);
    }
    int visited[100] = {0};
    int pushOrder[100], popOrder[100];
    int pushIndex = 0, popIndex = 0;

    printf("Starting DFS from vertex 0:\n");
    dfs(graph, 0, visited, pushOrder, popOrder, &pushIndex, &popIndex, &opcount);

    printf("\nPush Order: ");
    for (int i = 0; i < pushIndex; i++)
        printf("%d ", pushOrder[i]);
    
    printf("\nPop Order: ");
    for (int i = 0; i < popIndex; i++)
        printf("%d ", popOrder[i]);
    printf("\n");

    printf("%d operations\n", opcount);

    free(graph);
    return 0;
}

/*
output:
Enter number of vertices: 6
Enter edges of the graph (input vertex numbers, -1 to cancel): 0 1 0 2 1 3 1 4 2 5 -1
Starting DFS from vertex 0:
Pushed: 0
Pushed: 1
Pushed: 3
Popped: 3
Pushed: 4
Popped: 4
Popped: 1
Pushed: 2
Pushed: 5
Popped: 5
Popped: 2
Popped: 0

Push Order: 0 1 3 4 2 5
Pop Order: 3 4 1 5 2 0
36 operations
*/