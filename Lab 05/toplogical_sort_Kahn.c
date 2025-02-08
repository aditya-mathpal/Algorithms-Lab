#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertices;
    Node** adjList;
} Graph;

typedef struct Queue {
    int arr[20];
    int front;
    int rear;
} Queue;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));
    
    for(int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;
    
    return graph;
}

void addEdge(Graph* graph, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;
}

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

void enqueue(Queue* q, int value) {
    q->arr[++(q->rear)] = value;
}

int dequeue(Queue* q) {
    return q->arr[(q->front)++];
}

int isEmpty(Queue* q) {
    return q->front > q->rear;
}

void topologicalSort(Graph* graph, int* opcount) {
    int* inDegree = (int*)calloc(graph->vertices, sizeof(int));
    int order[20], orderIndex = 0;
    Queue q;
    initQueue(&q);

    for(int u = 0; u < graph->vertices; u++) {
        Node* temp = graph->adjList[u];
        while(temp) {
            inDegree[temp->vertex]++;
            (*opcount)++;
            temp = temp->next;
        }
        (*opcount)++;
    }

    for(int i = 0; i < graph->vertices; i++) {
        (*opcount)++;
        if(inDegree[i] == 0) {
            enqueue(&q, i);
        }
    }

    while(!isEmpty(&q)) {
        (*opcount)++;
        int u = dequeue(&q);
        order[orderIndex++] = u;

        Node* temp = graph->adjList[u];
        while(temp) {
            int v = temp->vertex;
            inDegree[v]--;
            (*opcount)++;

            if(inDegree[v] == 0) {
                enqueue(&q, v);
            }

            temp = temp->next;
            (*opcount)++;
        }
    }

    printf("Topological Sort: ");
    for(int i = 0; i < orderIndex; i++) {
        printf("%d ", order[i]);
        (*opcount)++;
    }
    printf("\n");

    free(inDegree);
}

void freeGraph(Graph* graph) {
    for(int i = 0; i < graph->vertices; i++) {
        Node* curr = graph->adjList[i];
        while(curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    int v, t1, t2, opcount = 0;
    printf("Enter number of vertices: ");
    scanf("%d", &v);
    
    Graph* graph = createGraph(v);
    
    printf("Enter edges (source destination, -1 to stop):\n");
    while(1) {
        scanf("%d", &t1);
        if(t1 == -1) break;
        scanf("%d", &t2);
        addEdge(graph, t1, t2);
    }

    topologicalSort(graph, &opcount);
    printf("Total operations: %d\n", opcount);
    freeGraph(graph);

    return 0;
}

/*
output:
Enter number of vertices: 5
Enter edges (source destination, -1 to stop):
0 2 1 2 2 3 2 4 3 4 -1
Topological Sort: 0 1 2 3 4 
Total operations: 35
*/