#include <stdlib.h>
#include <string.h>
#include "../Header/Tweet.h"

typedef struct s_BTreeNode {
	void* data;
	struct s_Node* right;
	struct s_Node* left;
} BTreeNode;

typedef struct s_BinaryTree {
	BTreeNode* rootBTreeNode;
	BTreeNode* (*Add) (struct s_BinaryTree*, void*);
	BTreeNode* (*Get) (struct s_BinaryTree*, void*);
} BinaryTree;

//Funções para o nodo
BTreeNode* BTreeNode_New();
void BTreeNode_InsertNewLeft(BTreeNode*, void*);
void BTreeNode_InsertNewRight(BTreeNode*, void*);

//Funções para a árvore particulares User
BinaryTree* BinaryTree_User_New();
BTreeNode* BinaryTree_User_Add(BinaryTree*, void*, int*);
BTreeNode* BinaryTree_User_Get(BinaryTree*, void*);




