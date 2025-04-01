#include <stdio.h>
#include <stdlib.h>

void warshall(int** graph, int** reach, int n, int* op) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            reach[i][j] = graph[i][j];
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
                (*op)++;
            }
}

int main() {
    int n, op = 0;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    int** graph = (int**)malloc(n * sizeof(int*));
    int** reach = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++)
        graph[i] = reach[i] = (int*)malloc(n * sizeof(int));
    printf("Enter elements of adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    warshall(graph, reach, n, &op);
    printf("Transitive closure matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", reach[i][j]);
        printf("\n");
    }
    printf("%d operations\n", op);
    return 0;
}

/*
output:
Enter number of vertices: 4
Enter elements of adjacency matrix:
0 1 0 0 0 0 0 1 0 0 0 0 1 0 1 0
Transitive closure matrix:
1 1 1 1 
1 1 1 1 
0 0 0 0 
1 1 1 1 
64 operations
*/