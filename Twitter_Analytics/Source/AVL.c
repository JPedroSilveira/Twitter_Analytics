 #include <stdio.h>
#include <stdlib.h> 
#include "../Header/AVL.h"

// Functions
// C program to insert a node in AVL tree 

// A utility function to get the height of the tree 
int avl_height(avlTreeNode *N) { 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 

// A utility function to get maximumInt of two integers 
int maxInt(int a, int b) { 
    return (a > b)? a : b; 
} 

/* Helper function that allocates a new node with the given key and 
   NULL left and right pointers. */
avlTreeNode *avl_newNode(int key) { 
    avlTreeNode* node = (struct s_avlNode*) 
    malloc(sizeof(struct s_avlNode)); 
    node->key = key; 
    node->left = NULL; 
    node->right = NULL; 
    node->height = 1; // new node is initially added at leaf 
    return(node); 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
avlTreeNode *avl_rightRotate(avlTreeNode *y) { 
    avlTreeNode *x = y->left; 
    avlTreeNode *T2 = x->right; 

    // Perform rotation 
    x->right = y; 
    y->left = T2; 

    // Update avl_heights 
    y->height = maxInt(avl_height(y->left), avl_height(y->right))+1; 
    x->height = maxInt(avl_height(x->left), avl_height(x->right))+1; 

    // Return new root 
    return x; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
avlTreeNode *avl_leftRotate(avlTreeNode *x) { 
    avlTreeNode *y = x->right; 
    avlTreeNode *T2 = y->left; 

    // Perform rotation 
    y->left = x; 
    x->right = T2; 

    // Update heights 
    x->height = maxInt(avl_height(x->left), avl_height(x->right))+1; 
    y->height = maxInt(avl_height(y->left), avl_height(y->right))+1; 

    // Return new root 
    return y; 
} 

// Get Balance factor of node N 
int avl_getBalance(avlTreeNode *N) { 
    if (N == NULL) 
        return 0; 
    return avl_height(N->left) - avl_height(N->right); 
} 

// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
avlTreeNode *avl_insert(avlTreeNode* node, int key) { 
    /* 1. Perform the normal BST insertion */
    if (node == NULL) 
        return(avl_newNode(key)); 

    if (key < node->key) 
        node->left = avl_insert(node->left, key); 
    else if (key > node->key) 
        node->right = avl_insert(node->right, key); 
    else // Equal keys are not allowed in BST 
        return node; 

    /* 2. Update height of this ancestor node */
    node->height = 1 + maxInt(avl_height(node->left), 
            avl_height(node->right)); 

    /* 3. Get the balance factor of this ancestor 
       node to check whether this node became 
       unbalanced */
    int balance = avl_getBalance(node); 

    // If this node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && key < node->left->key) 
        return avl_rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && key > node->right->key) 
        return avl_leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && key > node->left->key) { 
        node->left = avl_leftRotate(node->left); 
        return avl_rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && key < node->right->key) { 
        node->right = avl_rightRotate(node->right); 
        return avl_leftRotate(node); 
    } 

    /* return the (unchanged) node pointer */
    return node; 
} 

// A utility function to print preorder traversal 
// of the tree. 
// The function also prints avl_height of every node 
void avl_preOrder(avlTreeNode *root) { 
    if(root != NULL) { 
        printf("%d ", root->key); 
        avl_preOrder(root->left); 
        avl_preOrder(root->right); 
    } 
} 

void avl_testa() { 
    avlTreeNode *root = NULL;

    /* Constructing tree given in the above figure */
    root = avl_insert(root, 10);
    root = avl_insert(root, 20);
    root = avl_insert(root, 30);
    root = avl_insert(root, 40);
    root = avl_insert(root, 50);
    root = avl_insert(root, 25);


    avl_preOrder(root);

} 


