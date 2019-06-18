#include <stdio.h>
#include <stdlib.h> 
#include "../Header/CompareUtils.h"

//Nodo da �rvore
typedef struct s_avlNode { 
	void* key; 
	struct s_avlNode *left; 
	struct s_avlNode *right; 
	int height; 
} avlTreeNode; 

//Struct da �rvore
typedef struct s_avlTree {
	avlTreeNode* root;
	int (*compare) (void*, void*);
} avlTree;

//Pega a altura da �rvore
int AVL_height(avlTreeNode* node);

//Cria uma nova �rvore com chave INT
avlTree* AVL_newTreeInt();

//Cria uuma nova �rvore com chave CHAR
avlTree* AVL_newTreeChar();

//Cria uma nova �rvore com chave STRING
avlTree* AVL_newTreeString();

//Inicializa os dados b�sicas do novo sem ser a chave
avlTreeNode* AVL_newNode(void* key);

// Rotaciona sub-�rvore para direita
avlTreeNode* AVL_rightRotate(avlTreeNode* y);

// Rotaciona sub-�rvore para esquerda
avlTreeNode* AVL_leftRotate(avlTreeNode* x);

// Retorna o valor de balanceamente de um nodo
int AVL_getBalance(avlTreeNode* node);

//Insere um novo nodo inteiro na �rvore
avlTreeNode* AVL_insertInt(avlTree* tree, int key);

//Insere um novo nodo char na �rvore
avlTreeNode* AVL_insertChar(avlTree* tree, char key);

//Insere um novo nodo string na �rvore
avlTreeNode* AVL_insertString(avlTree* tree, char* key);

/* Adiciona um novo nodo a �rvore
Retorna o nodo raiz*/
avlTreeNode* AVL_insert(avlTree* tree, void* key);

// Imprime a �rvore pr�-ordenada e a altura de cada nodo INT
void AVL_preOrderInt(avlTree* tree);

// Imprime a �rvore pr�-ordenada e a altura de cada nodo CHAR
void AVL_preOrderChar(avlTree* tree);

// Imprime a �rvore pr�-ordenada e a altura de cada nodo STRING
void AVL_preOrderString(avlTree* tree);

// Teste b�sico para AVL com chaves tipo INT
void AVL_testInt();

// Teste b�sico para AVL com chaves tipo CHAR
void AVL_testChar();

// Teste b�sico para AVL com chaves tipo STRING
void AVL_testString();
