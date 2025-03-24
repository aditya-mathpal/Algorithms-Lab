#include <stdio.h>
#include<stdlib.h>

#define MAX 100

void floyd(int** graph, int** dist, int n, int* op) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = graph[i][j];
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != __INT_MAX__ && dist[k][j] != __INT_MAX__)
                    dist[i][j] = dist[i][j] < dist[i][k] + dist[k][j] ? dist[i][j] : dist[i][k] + dist[k][j];
                (*op)++;
            }
}

int main() {
    int n, op = 0;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    int** graph = (int**)malloc(n * sizeof(int*));
    int** dist = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++)
        graph[i] = dist[i] = (int*)malloc(n * sizeof(int));
    printf("Enter adjacency matrix (use -1 for infinity):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == -1)
                graph[i][j] = __INT_MAX__;
        }
    floyd(graph, dist, n, &op);
    printf("Shortest path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == __INT_MAX__)
                printf("Inf");
            else
                printf("%5d ", dist[i][j]);
        }
        printf("\n");
    }
    printf("%d operations\n", op);
    return 0;
}

/*
output:
Enter number of vertices: 4
Enter adjacency matrix (use -1 for infinity):
0 -1 3 -1 2 0 -1 -1 -1 7 0 1 6 -1 -1 0
Shortest path matrix:
    0    10     3     4 
    2     0     5     6 
    7     7     0     1 
    6    16     9     0 
64 operations
*/