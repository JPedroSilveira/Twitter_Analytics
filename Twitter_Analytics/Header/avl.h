// An AVL tree node 
typedef struct s_Node { 
	int key; 
	struct s_Node *left; 
	struct s_Node *right; 
	int height; 
} avlTreeNode; 

int height(avlTreeNode *N);
int max(int a, int b);
avlTreeNode* insert( avlTreeNode *node, int key);
avlTreeNode* newNode(int key);
avlTreeNode *rightRotate( avlTreeNode *y);
avlTreeNode *leftRotate( avlTreeNode *x);
int getBalance(avlTreeNode *N);
avlTreeNode* insert(avlTreeNode* node, int key);
void preOrder(avlTreeNode *root);
