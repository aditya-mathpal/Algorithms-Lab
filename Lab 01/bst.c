#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int search(TreeNode* root, int key) {
    if (root == NULL) return 0;
    if(key == root->data) return 1;
    if (key < root->data) return search(root->left, key);
    else return search(root->right, key);
}

TreeNode* insert(TreeNode* root, int key) {
    if (root == NULL)
        return createNode(key);
    
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    
    return root;
}

TreeNode* buildTree(TreeNode* root) {
    int n;
    printf("Enter elements (-1 to stop): ");
    while (1) {
        scanf("%d", &n);
        if (n == -1)
            break;
        root = insert(root, n);
    }
    return root;
}

void inorder(TreeNode* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode* root = NULL;
    printf("Enter nodes of the tree:\n");
    root = buildTree(root);
    printf("\nInorder traversal: ");
    inorder(root);
    printf("\nPreorder traversal: ");
    preorder(root);
    printf("\nPostorder traversal: ");
    postorder(root);
    printf("\n\n");

    printf("Enter key: ");
    int key;
    scanf("%d", &key);
    
    if(search(root,key)) printf("key found");
    else {
        root = insert(root, key);
        printf("Key %d inserted in the tree.\n", key);
    }
    
    printf("\nInorder traversal: ");
    inorder(root);
    printf("\nPreorder traversal: ");
    preorder(root);
    printf("\nPostorder traversal: ");
    postorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}

/*
output:
Enter nodes of the tree:
Enter elements (-1 to stop): 34 21 55 -1

Inorder traversal: 21 34 55
Preorder traversal: 34 21 55
Postorder traversal: 21 55 34

Enter key: 36
Key 36 inserted in the tree.

Inorder traversal: 21 34 36 55
Preorder traversal: 34 21 55 36
Postorder traversal: 21 36 55 34
*/