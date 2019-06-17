// An AVL tree node 
typedef struct s_avlNode { 
	int key; 
	struct s_avlNode *left; 
	struct s_avlNode *right; 
	int height; 
} avlTreeNode; 

int avl_height(avlTreeNode *N);
int maxInt(int a, int b);
avlTreeNode* avl_insert(avlTreeNode *node, int key);
avlTreeNode* avl_newNode(int key);
avlTreeNode *avl_rightRotate( avlTreeNode *y);
avlTreeNode *avl_leftRotate( avlTreeNode *x);
int avl_getBalance(avlTreeNode *N);
void avl_preOrder(avlTreeNode *root);
void avl_testa();
