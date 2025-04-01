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

TreeNode *buildTree() {
    int data;
    printf("Enter -1 for NULL\n");
    printf("Enter root node value: ");
    scanf("%d", &data);

    if (data == -1) return NULL;

    TreeNode *root = createNode(data);
    TreeNode *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while(front < rear) {
        TreeNode *current = queue[front++];
        printf("Left child of %d: ", current->data);
        scanf("%d", &data);
        current->left = createNode(data);
        if (current->left) queue[rear++] = current->left;
        printf("Right child of %d: ", current->data);
        scanf("%d", &data);
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
    TreeNode* root = buildTree();
    int c = 0, opcount = 0;
    countNodes(root, &c, &opcount);
    printf("There are %d nodes in the tree\n%d operations\n", c, opcount);
    return 0;
}

/*
output:
Enter -1 for NULL
Enter root node value: 1
Left child of 1: 2
Right child of 1: 3
Left child of 2: 4
Right child of 2: 5
Left child of 3: 6
Right child of 3: 7
Left child of 4: -1
Right child of 4: -1
Left child of 5: -1
Right child of 5: -1
Left child of 6: -1
Right child of 6: -1
Left child of 7: -1
Right child of 7: -1
There are 7 nodes in the tree
15 operations
*/