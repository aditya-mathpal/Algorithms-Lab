#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Graph {
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(Graph* graph, int u, int v) {
    graph->adjMatrix[u][v] = 1;
    graph->adjMatrix[v][u] = 1;
}

void dfs(Graph* graph, int start, int visited[], int* pushOrder, int* popOrder, int* pushIndex, int* popIndex) {
    visited[start] = 1;
    pushOrder[(*pushIndex)++] = start;
    printf("Pushed: %d\n", start);

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[start][i] == 1 && !visited[i]) {
            dfs(graph, i, visited, pushOrder, popOrder, pushIndex, popIndex);
        }
    }

    popOrder[(*popIndex)++] = start;
    printf("Popped: %d\n", start);
}

int main() {
    int vertices = 6;
    Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    int visited[MAX_VERTICES] = {0};
    int pushOrder[MAX_VERTICES], popOrder[MAX_VERTICES];
    int pushIndex = 0, popIndex = 0;

    printf("Starting DFS from vertex 0:\n");
    dfs(graph, 0, visited, pushOrder, popOrder, &pushIndex, &popIndex);

    printf("\nPush Order: ");
    for (int i = 0; i < pushIndex; i++) {
        printf("%d ", pushOrder[i]);
    }
    
    printf("\nPop Order: ");
    for (int i = 0; i < popIndex; i++) {
        printf("%d ", popOrder[i]);
    }
    printf("\n");

    free(graph);
    return 0;
}
/*Starting DFS from vertex 0:
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
*/