#include <stdio.h>
#include <stdlib.h> 
#include "./CompareUtils.h"

//Nodo da árvore
typedef struct s_AvlNode { 
	void* key; 
	struct s_AvlNode *left;
	struct s_AvlNode *right;
	struct s_AvlNode *mother;
	int height; 
} AvlTreeNode; 

//Struct da árvore
typedef struct s_AvlTree {
	AvlTreeNode* root;
	int (*compare) (void*, void*);
} AvlTree;

//Pega a altura da árvore
int AVL_height(AvlTreeNode* node);

//Retorna true se o nó for NULL e false caso não seja
int AVL_nodeIsEmpty(AvlTreeNode* node);

//Cria uma nova árvore com chave INT
AvlTree* AVL_newTreeInt();

//Cria uuma nova árvore com chave CHAR
AvlTree* AVL_newTreeChar();

//Cria uma nova árvore com chave STRING
AvlTree* AVL_newTreeString();

//Cria uma nova árvore com chave User.name
AvlTree* AVL_newTreeUserByName();

//Cria uma nova árvore com chave Hashtag.name
AvlTree* AVL_newTreeHashtagByTweetCount();

//Cria uma nova árvore com chave Tweet.retweetCount
AvlTree * AVL_newTreeTweetByRetweetCount();

//Inicializa os dados básicas do novo sem ser a chave
AvlTreeNode* AVL_newNode(void* data);

// Rotaciona sub-árvore para direita
AvlTreeNode* AVL_rightRotate(AvlTreeNode* y);

// Rotaciona sub-árvore para esquerda
AvlTreeNode* AVL_leftRotate(AvlTreeNode* x);

// Retorna o valor de balanceamente de um nodo
int AVL_getBalance(AvlTreeNode* node);

//Insere um novo nodo inteiro na árvore
AvlTreeNode* AVL_insertInt(AvlTree* tree, int key);

//Insere um novo nodo char na árvore
AvlTreeNode* AVL_insertChar(AvlTree* tree, char key);

//Insere um novo nodo string na árvore
AvlTreeNode* AVL_insertString(AvlTree* tree, char* key);

/*Adiciona um novo nodo a árvore
  Retorna o nodo novo*/
AvlTreeNode* AVL_insert(AvlTree* tree, AvlTreeNode* mother, void* key);

/*Remove um nodo da árvore*/
void AVL_remove(AvlTree* tree, AvlTreeNode* nodeToRemove);

/*Recebe um nó e retorna verdadeiro caso ele seja um nó folha*/
int AVL_isLeaf(AvlTreeNode* node);

/*Retorna o filho único de um nó ou NULL*/
AvlTreeNode* AVL_hasJustOneSubTree(AvlTreeNode* node);

/*Retorna o menor filho de um nó*/
AvlTreeNode* AVL_getSmallestChild(AvlTreeNode* node);

/*Retorna o maior filho de um nó*/
AvlTreeNode* AVL_getBiggestChild(AvlTreeNode* node);

/*Retorna true se o nó for filho direito, causa erro caso o nó não possui mãe*/
int AVL_isRigthChild(AvlTreeNode* node);

/*Busca um nodo na arvore por um endereco de valor, caso nao ache retorna NULL*/
AvlTreeNode* AVL_get(AvlTree* tree, void* key);

/*Busca um nodo na arvore por um valor INT, caso nao ache retorna NULL*/
AvlTreeNode* AVL_getInt(AvlTree* tree, int key);

/*Busca um nodo na arvore por um valor CHAR, caso nao ache retorna NULL*/
AvlTreeNode* AVL_getChar(AvlTree* tree, char key);

/*Busca um nodo na arvore por um valor STRING, caso nao ache retorna NULL*/
AvlTreeNode* AVL_getString(AvlTree* tree, char* key);

//Imprime a árvore pré-ordenada e a altura de cada nodo INT
void AVL_preOrderInt(AvlTreeNode* root);

//Imprime a árvore pré-ordenada e a altura de cada nodo CHAR
void AVL_preOrderChar(AvlTreeNode* root);

//Imprime a árvore pré-ordenada e a altura de cada nodo STRING
void AVL_preOrderString(AvlTreeNode* root);

//Teste básico para AVL com chaves tipo INT
void AVL_testInt();

//Teste básico para AVL com chaves tipo CHAR
void AVL_testChar();

//Teste básico para AVL com chaves tipo STRING
void AVL_testString();
