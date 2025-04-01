#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int vertices;
    int adjMatrix[100][100];
} Graph;

typedef struct Queue {
    int items[100];
    int front, rear;
} Queue;

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
    graph->adjMatrix[v][u] = 1;  // Since it's an undirected graph
}

void initializeQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == 99) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front >= q->rear) q->front = q->rear = -1;
    else q->front++;
    return item;
}

void bfs(Graph* graph, int start, int* opcount) {
    int visited[100] = {0};
    Queue q;
    initializeQueue(&q);
    
    visited[start] = 1;
    enqueue(&q, start);
    
    while (!isQueueEmpty(&q)) {
        int current = dequeue(&q);
        printf("Visited: %d\n", current);
        
        for (int i = 0; i < graph->vertices; i++) {
            (*opcount)++;
            if (graph->adjMatrix[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
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

    printf("BFS starting from vertex 0:\n");
    bfs(graph, 0, &opcount);
    printf("%d operations\n", opcount);

    free(graph);
    return 0;
}

/*
output:
Enter number of vertices: 6
Enter edges of the graph (input vertex numbers, -1 to cancel): 0 1 0 2 1 3 1 4 2 5 -1
BFS starting from vertex 0:
Visited: 0
Visited: 1
Visited: 2
Visited: 3
Visited: 4
Visited: 5
36 operations
*/