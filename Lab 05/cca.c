#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode(int data) {
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

TreeNode* findNode(TreeNode* root, int val, int* opcount) {
    (*opcount)++;
    if (root == NULL) return NULL;
    if (root->data == val) return root;
    TreeNode* left = findNode(root->left, val, opcount);
    if (left != NULL) return left;
    return findNode(root->right, val, opcount);
}

TreeNode* CCA(TreeNode* root, TreeNode* p, TreeNode* q, int* opcount) {
    (*opcount)++;
    if (root == NULL || root == p || root == q)
        return root;
    TreeNode* left = CCA(root->left, p, q, opcount);
    TreeNode* right = CCA(root->right, p, q, opcount);
    if (left != NULL && right != NULL) return root;
    return left != NULL ? left : right;
}

int main() {
    TreeNode *root = buildTree();
    int a, b, opcount = 0;
    printf("Enter two node values to find cca: ");
    scanf("%d %d", &a, &b);
    TreeNode* p = findNode(root, a, &opcount);
    TreeNode* q = findNode(root, b, &opcount);
    if (p == NULL || q == NULL) {
        printf("One or both nodes not found in the tree.\n");
    } else {
        TreeNode *cca = CCA(root, p, q, &opcount);
        if (cca != NULL) {
            printf("CCA of %d and %d is: %d\n", a, b, cca->data);
        } else {
            printf("No common ancestor found.\n");
        }
    }
    printf("%d operations\n", opcount);
    return 0;
}

/*
output:
Enter -1 for NULL
Enter root node value: 20
Left child of 20: 8
Right child of 20: 22
Left child of 8: 4
Right child of 8: 12
Left child of 22: -1
Right child of 22: -1
Left child of 4: -1
Right child of 4: -1
Left child of 12: 10
Right child of 12: 14
Left child of 10: -1
Right child of 10: -1
Left child of 14: -1
Right child of 14: -1
In-Order Traversal: 4 8 10 12 14 20 22 
Enter two node values to find cca: 10 14
CCA of 10 and 14 is: 12
*/