#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

Node* getNode(int vertex) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->vertex = vertex;
    temp->next = NULL;
    return temp;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dst) {
    Node* temp = getNode(dst);
    temp->next = graph->adjLists[src];
    graph->adjLists[src] = temp;
    temp = getNode(src);
    temp->next = graph->adjLists[dst];
    graph->adjLists [dst] = temp;
}

void printList(Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        Node* temp = graph->adjLists[i];
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void printMat(Graph* graph) {
    int** adjMatrix = (int**)malloc(graph->numVertices * sizeof(int*));
    for (int i = 0; i < graph->numVertices; i++) {
        adjMatrix[i] = (int*)calloc(graph->numVertices, sizeof(int));
    }
    
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            adjMatrix[i][temp->vertex] = 1;
            temp = temp->next;
        }
    }
    
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < graph->numVertices; i++)
        free(adjMatrix[i]);
    free(adjMatrix);
}

int main() {
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    
    Graph* graph = createGraph(vertices);
    
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter the edges (source destination pairs):\n");
    for (int i = 0; i < edges; i++) {
        int src, dst;
        scanf("%d %d", &src, &dst);
        addEdge(graph, src, dst);
    }
    
    printList(graph);
    printMat(graph);
    
    for (int i = 0; i < vertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph);
    return 0;
}

/*
output:
Enter the number of vertices: 3
Enter the number of edges: 3
Enter the edges (source destination pairs):
0 1 1 2 2 0
Adjacency List:
0: 2 -> 1 -> NULL
1: 2 -> 0 -> NULL
2: 0 -> 1 -> NULL

Adjacency Matrix:
0 1 1
1 0 1
1 1 0
*/