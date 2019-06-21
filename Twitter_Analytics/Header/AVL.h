#include <stdio.h>
#include <stdlib.h> 
#include "./CompareUtils.h"

//Nodo da �rvore
typedef struct s_AvlNode { 
	void* key; 
	struct s_AvlNode *left;
	struct s_AvlNode *right;
	struct s_AvlNode *mother;
	int height; 
} AvlTreeNode; 

//Struct da �rvore
typedef struct s_AvlTree {
	AvlTreeNode* root;
	int (*compare) (void*, void*);
} AvlTree;

//Pega a altura da �rvore
int AVL_height(AvlTreeNode* node);

//Retorna true se o n� for NULL e false caso n�o seja
int AVL_nodeIsEmpty(AvlTreeNode* node);

//Cria uma nova �rvore com chave INT
AvlTree* AVL_newTreeInt();

//Cria uuma nova �rvore com chave CHAR
AvlTree* AVL_newTreeChar();

//Cria uma nova �rvore com chave STRING
AvlTree* AVL_newTreeString();

//Cria uma nova �rvore com chave User.name
AvlTree* AVL_newTreeUserByName();

//Cria uma nova �rvore com chave Hashtag.name
AvlTree* AVL_newTreeHashtagByTweetCount();

//Cria uma nova �rvore com chave Tweet.retweetCount
AvlTree * AVL_newTreeTweetByRetweetCount();

//Inicializa os dados b�sicas do novo sem ser a chave
AvlTreeNode* AVL_newNode(void* data);

// Rotaciona sub-�rvore para direita
AvlTreeNode* AVL_rightRotate(AvlTreeNode* y);

// Rotaciona sub-�rvore para esquerda
AvlTreeNode* AVL_leftRotate(AvlTreeNode* x);

// Retorna o valor de balanceamente de um nodo
int AVL_getBalance(AvlTreeNode* node);

//Insere um novo nodo inteiro na �rvore
AvlTreeNode* AVL_insertInt(AvlTree* tree, int key);

//Insere um novo nodo char na �rvore
AvlTreeNode* AVL_insertChar(AvlTree* tree, char key);

//Insere um novo nodo string na �rvore
AvlTreeNode* AVL_insertString(AvlTree* tree, char* key);

/*Adiciona um novo nodo a �rvore
  Retorna o nodo novo*/
AvlTreeNode* AVL_insert(AvlTree* tree, AvlTreeNode* mother, void* key);

/*Remove um nodo da �rvore*/
void AVL_remove(AvlTree* tree, AvlTreeNode* nodeToRemove);

/*Recebe um n� e retorna verdadeiro caso ele seja um n� folha*/
int AVL_isLeaf(AvlTreeNode* node);

/*Retorna o filho �nico de um n� ou NULL*/
AvlTreeNode* AVL_hasJustOneSubTree(AvlTreeNode* node);

/*Retorna o menor filho de um n�*/
AvlTreeNode* AVL_getSmallestChild(AvlTreeNode* node);

/*Retorna o maior filho de um n�*/
AvlTreeNode* AVL_getBiggestChild(AvlTreeNode* node);

/*Retorna true se o n� for filho direito, causa erro caso o n� n�o possui m�e*/
int AVL_isRigthChild(AvlTreeNode* node);

/*Busca um nodo na arvore por um endereco de valor, caso nao ache retorna NULL*/
AvlTreeNode* AVL_get(AvlTree* tree, void* key);

/*Busca um nodo na arvore por um valor INT, caso nao ache retorna NULL*/
AvlTreeNode* AVL_getInt(AvlTree* tree, int key);

/*Busca um nodo na arvore por um valor CHAR, caso nao ache retorna NULL*/
AvlTreeNode* AVL_getChar(AvlTree* tree, char key);

/*Busca um nodo na arvore por um valor STRING, caso nao ache retorna NULL*/
AvlTreeNode* AVL_getString(AvlTree* tree, char* key);

//Imprime a �rvore pr�-ordenada e a altura de cada nodo INT
void AVL_preOrderInt(AvlTreeNode* root);

//Imprime a �rvore pr�-ordenada e a altura de cada nodo CHAR
void AVL_preOrderChar(AvlTreeNode* root);

//Imprime a �rvore pr�-ordenada e a altura de cada nodo STRING
void AVL_preOrderString(AvlTreeNode* root);

//Teste b�sico para AVL com chaves tipo INT
void AVL_testInt();

//Teste b�sico para AVL com chaves tipo CHAR
void AVL_testChar();

//Teste b�sico para AVL com chaves tipo STRING
void AVL_testString();
