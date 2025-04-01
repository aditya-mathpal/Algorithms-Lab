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
    if (q->rear == 100 - 1) {
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
        bfs(graph, 0, &opcount);
        printf("%d vertices: %d operations\n", n, opcount);

        free(graph);
    }
    return 0;
}