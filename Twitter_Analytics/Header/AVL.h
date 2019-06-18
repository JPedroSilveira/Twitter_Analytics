#include <stdio.h>
#include <stdlib.h> 
#include "../Header/CompareUtils.h"

//Nodo da árvore
typedef struct s_avlNode { 
	void* key; 
	struct s_avlNode *left; 
	struct s_avlNode *right; 
	int height; 
} avlTreeNode; 

//Struct da árvore
typedef struct s_avlTree {
	avlTreeNode* root;
	int (*compare) (void*, void*);
} avlTree;

//Pega a altura da árvore
int AVL_height(avlTreeNode* node);

//Cria uma nova árvore com chave INT
avlTree* AVL_newTreeInt();

//Cria uuma nova árvore com chave CHAR
avlTree* AVL_newTreeChar();

//Cria uma nova árvore com chave STRING
avlTree* AVL_newTreeString();

//Inicializa os dados básicas do novo sem ser a chave
avlTreeNode* AVL_newNode(void* key);

// Rotaciona sub-árvore para direita
avlTreeNode* AVL_rightRotate(avlTreeNode* y);

// Rotaciona sub-árvore para esquerda
avlTreeNode* AVL_leftRotate(avlTreeNode* x);

// Retorna o valor de balanceamente de um nodo
int AVL_getBalance(avlTreeNode* node);

//Insere um novo nodo inteiro na árvore
avlTreeNode* AVL_insertInt(avlTree* tree, int key);

//Insere um novo nodo char na árvore
avlTreeNode* AVL_insertChar(avlTree* tree, char key);

//Insere um novo nodo string na árvore
avlTreeNode* AVL_insertString(avlTree* tree, char* key);

/* Adiciona um novo nodo a árvore
Retorna o nodo raiz*/
avlTreeNode* AVL_insert(avlTree* tree, void* key);

// Imprime a árvore pré-ordenada e a altura de cada nodo INT
void AVL_preOrderInt(avlTree* tree);

// Imprime a árvore pré-ordenada e a altura de cada nodo CHAR
void AVL_preOrderChar(avlTree* tree);

// Imprime a árvore pré-ordenada e a altura de cada nodo STRING
void AVL_preOrderString(avlTree* tree);

// Teste básico para AVL com chaves tipo INT
void AVL_testInt();

// Teste básico para AVL com chaves tipo CHAR
void AVL_testChar();

// Teste básico para AVL com chaves tipo STRING
void AVL_testString();
