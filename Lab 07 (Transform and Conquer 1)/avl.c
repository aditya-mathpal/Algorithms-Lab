#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
    int data, height;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int getHeight(TreeNode* node) {
    if(node == NULL) return 0;
    return node->height;
}

int updateHeight(TreeNode* node) {
     return (1 + (getHeight(node->left) > getHeight(node->right) ? node->left->height : node->right->height));
}

int getBal(TreeNode* node) {
    if(node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

TreeNode* rightRot(TreeNode* root) {
    TreeNode* l = root->left;
    l->right = root;
    updateHeight(root);
    updateHeight(l);
    return l;
}

TreeNode* leftRot(TreeNode* root) {
    TreeNode* r = root->right;
    r->left = root;
    updateHeight(root);
    updateHeight(r);
    return r;
}

TreeNode* insert(TreeNode* root, int data) {
    TreeNode* newNode = createNode(data);
    if(root == NULL) return newNode;
    TreeNode *parent = NULL, *curr = root;
    while(curr != NULL) {
        parent = curr;
        if(data < curr->data) curr = curr->left;
        else if(data > curr->data) curr = curr->right;
        else {
            free(newNode);
            return root;
        }
    }
    if(data < parent->data) parent->left = newNode;
    else parent->right = newNode;
    curr = parent;
    while(curr != NULL) {
        updateHeight(curr);
        int bal = getBal(curr);
        if(bal > 1 && data < curr->left->data) curr = rightRot(curr);
        else if(bal < -1 && data > curr->right->data) curr = leftRot(curr);
        else if(bal > 1 && data > curr->left->data) {
            curr->left = leftRot(curr->left);
            curr = rightRot(curr);
        }
        else if(bal < -1 && data < curr->right->data) {
            curr->right = rightRot(curr->right);
            curr = leftRot(curr);
        }
        curr = curr == parent ? NULL : parent;
    }
    return root;
}

void inorder(TreeNode* root) {
    if(root) {
        inorder(root->left);
        printf("%5d", root->data);
        inorder(root->right);
    }
}

// ex2
void PredAndSucc(TreeNode* root, int key, int* pred, int* succFlag) {
    if(root) {
        PredAndSucc(root->left, key, pred, succFlag);
        if(root->data < key) *pred = root->data;
        if(root->data == key)
            printf("Predecessor: %d\n", *pred);
        if(root->data > key && !(*succFlag)) {
            printf("Successor: %d\n", root->data);
            *succFlag = 1;
        }
        PredAndSucc(root->right, key, pred, succFlag);
    }
}

int main() {
    TreeNode* tree = NULL;
    int n, pred, succFlag = 0;
    printf("Enter node values (-1 to stop): ");
    do {
        scanf("%d", &n);
        if(n != -1) tree = insert(tree, n);
    } while(n != -1);
    printf("In-order traversal:\n");
    inorder(tree);
    printf("\n");
    //ex2
    printf("Enter the key to print successor and predecessor of: ");
    scanf("%d", &n);
    PredAndSucc(tree, n, &pred, &succFlag);
    //ex2 end
    return 0;
}

/*
ex1 output:
Enter node values (-1 to stop): 50 20 70 30 60 -1
In-order traversal:
   20   30   50   60   70
*/

/*
ex2 output:
Enter node values (-1 to stop): 50 20 70 30 60 -1
In-order traversal:
   20   30   50   60   70
Enter the key to print successor and predecessor of: 50
Predecessor: 30
Successor: 60
*/