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

TreeNode *buildTree(int* i, int n) {
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

void inOrder(TreeNode *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    int i = 1, n, opcount = 0;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    TreeNode *root = buildTree(&i, n);
    inOrder(root);
    printf("\n");
    TreeNode* p = findNode(root, n-1, &opcount);
    TreeNode* q = findNode(root, n, &opcount);
    if (p == NULL || q == NULL) {
        printf("One or both nodes not found in the tree.\n");
    } else {
        TreeNode *cca = CCA(root, p, q, &opcount);
        if (cca != NULL) {
            printf("");
        } else {
            printf("No common ancestor found.\n");
        }
    }
    printf("%d operations\n", opcount);
    return 0;
}