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

typedef struct Stack {
    int arr[20];
    int top;
} Stack;

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

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int value) {
    s->arr[++(s->top)] = value;
}

int pop(Stack* s) {
    return s->arr[(s->top)--];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void dfs(Graph* graph, int v, int visited[], Stack* stack, int* opcount) {
    visited[v] = 1;

    Node* temp = graph->adjList[v];
    while(1) {
        (*opcount)++;
        if (!temp) break;

        (*opcount)++;
        if(!visited[temp->vertex]) {
            dfs(graph, temp->vertex, visited, stack, opcount);
        }
        
        temp = temp->next;
    }

    push(stack, v);
    (*opcount)++;
}

void topologicalSort(Graph* graph, int* opcount) {
    Stack stack;
    initStack(&stack);
    int visited[20] = {0};

    for(int i = 0; i < graph->vertices; i++) {
        (*opcount)++;
        if(!visited[i]) {
            dfs(graph, i, visited, &stack, opcount);
        }
    }

    printf("Topological Sort: ");
    while(!isEmpty(&stack)) {
        printf("%d ", pop(&stack));
        (*opcount)++;
    }
    printf("\n");
}

void freeGraph(Graph* graph) {
    for(int i = 0; i < graph->vertices; i++) {
        Node* curr = graph->adjList[i];
        while(curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        graph->adjList[i] = NULL;
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    int v, e, opcount = 0;
    printf("Enter number of vertices and edges: ");
    scanf("%d%d", &v, &e);
    
    Graph* graph = createGraph(v);

    for(int i = 0; i < e; i++)
        addEdge(graph, i, i+1);

    topologicalSort(graph, &opcount);
    printf("Total operations: %d\n", opcount);
    freeGraph(graph);
    return 0;
}