#include<stdio.h>
#include<stdlib.h>

typedef struct Tree {
    int data;
    struct Tree* left;
    struct Tree* right;
} TreeNode;

TreeNode* createNode(int data) {
    if (data == -1) return NULL;
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* buildTree(int* i, int n) {
    int data;
    data = (*i)++;

    if (data == -1) return NULL;

    TreeNode *root = createNode(data);
    TreeNode *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while(front < rear) {
        TreeNode *current = queue[front++];
        data = (*i)<=n?(*i)++:-1;
        current->left = createNode(data);
        if (current->left) queue[rear++] = current->left;
        data = (*i)<=n?(*i)++:-1;
        current->right = createNode(data);
        if (current->right) queue[rear++] = current->right;
    }
    return root;
}

void countNodes(TreeNode* root, int* n, int* opcount) {
    (*opcount)++;
    if(root != NULL) (*n)++;
    else return;
    countNodes(root->left, n, opcount);
    countNodes(root->right, n, opcount);
}

int main() {
    int n, i = 1;
    printf("Enter the number of vertices: ");
    scanf("%d",&n);
    TreeNode* root = buildTree(&i,n);
    int c = 0, opcount = 0;
    countNodes(root, &c, &opcount);
    printf("There are %d nodes in the tree\n%d operations\n", c, opcount);
    return 0;
}