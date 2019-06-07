#include "../Header/BinaryTree.h"

//Inicializa um novo nodo
BTreeNode* BTreeNode_New()
{
	BTreeNode* bTNode = malloc(sizeof(BTreeNode));
	bTNode->left = NULL;
	bTNode->right = NULL;
	bTNode->data = NULL;

	return bTNode;
}

//Insere um novo nodo a esquerda de um existente
void BTreeNode_InsertNewLeft(BTreeNode* bTNode, void* data)
{
	bTNode->right = BTreeNode_New();
	bTNode->right->data = data;

	return bTNode;
}

//Insere um novo nodo a direita de um existente
void BTreeNode_InsertNewRight(BTreeNode* bTNode, void* data)
{
	bTNode->right = BTreeNode_New();
	bTNode->right->data = data;

	return bTNode;
}

//Result = 1 (Inserido), Result = 2 (J� existente)
BTreeNode* BinaryTree_User_Add(BinaryTree* tree, void* data, int* result)
{
	User* newUser = data;
	BTreeNode* bTNode = tree->rootBTreeNode;
	*result = 0;

	//Caso n�o tenha raiz, cria uma
	if (bTNode == NULL) {
		bTNode = BTreeNode_New();
		bTNode->data = newUser;
		result = 1;
	} else { //Caso n�o, procura o local ideal para a inser��o
		while (!result) {
			User* userNode = bTNode->data;
			int cmpResult = strcmp(userNode->name, newUser->name);

			if (cmpResult == 0) { //Nodo j� existente
				result = 2;
			} else if (cmpResult == -1) { //Caso o novo nodo seja maior
				if (bTNode->right != NULL){ //Se tiver pr�ximo continua o la�o
					bTNode = bTNode->right;
				} else { //Caso n�o, adiciona o novo nodo e termina o la�o
					BTreeNode_InsertNewRight(bTNode, data);
					result = 1;
				}
			} else { //Caso seja menor
				if (bTNode->left != NULL) { //Se tiver pr�ximo continua o la�o
					bTNode = bTNode->left;
				}
				else { //Caso n�o, adiciona o novo nodo e termina o la�o
					BTreeNode_InsertNewLeft(bTNode, data);
					result = 1;
				}
			}
		}
	}
}

//Retorna o usu�rio conforme seu nome
BTreeNode* BinaryTree_User_Get(BinaryTree* tree, void* data)
{
	User* newUser = data;
	BTreeNode* bTNode = tree->rootBTreeNode;

	int found = 0;
	while (!found && bTNode != NULL) {
		User* nodeUser = bTNode->data;
		int cmpResult = strcmp(nodeUser->name, newUser->name);
		if (cmpResult == 0) { //Caso sejam iguais
			found = 1;
		}
		else if(cmpResult == -1){ //Caso seja maior
			bTNode = bTNode->right;
		}
		else { //Caso seja menor
			bTNode = bTNode->left;
		}
	}
		
	return bTNode;
}

//Inicializa uma nova �rvore bin�ria do tipo usu�rio
BinaryTree* BinaryTree_User_New()
{
	BinaryTree* tree = malloc(sizeof(BinaryTree));
	tree->rootBTreeNode = NULL;
	tree->Add = BinaryTree_User_Add;
	tree->Get = BinaryTree_User_Get;

	return tree;
}


