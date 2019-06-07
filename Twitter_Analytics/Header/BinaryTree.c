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

//Result = 1 (Inserido), Result = 2 (Já existente)
BTreeNode* BinaryTree_User_Add(BinaryTree* tree, void* data, int* result)
{
	User* newUser = data;
	BTreeNode* bTNode = tree->rootBTreeNode;
	*result = 0;

	//Caso não tenha raiz, cria uma
	if (bTNode == NULL) {
		bTNode = BTreeNode_New();
		bTNode->data = newUser;
		result = 1;
	} else { //Caso não, procura o local ideal para a inserção
		while (!result) {
			User* userNode = bTNode->data;
			int cmpResult = strcmp(userNode->name, newUser->name);

			if (cmpResult == 0) { //Nodo já existente
				result = 2;
			} else if (cmpResult == -1) { //Caso o novo nodo seja maior
				if (bTNode->right != NULL){ //Se tiver próximo continua o laço
					bTNode = bTNode->right;
				} else { //Caso não, adiciona o novo nodo e termina o laço
					BTreeNode_InsertNewRight(bTNode, data);
					result = 1;
				}
			} else { //Caso seja menor
				if (bTNode->left != NULL) { //Se tiver próximo continua o laço
					bTNode = bTNode->left;
				}
				else { //Caso não, adiciona o novo nodo e termina o laço
					BTreeNode_InsertNewLeft(bTNode, data);
					result = 1;
				}
			}
		}
	}
}

//Retorna o usuário conforme seu nome
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

//Inicializa uma nova árvore binária do tipo usuário
BinaryTree* BinaryTree_User_New()
{
	BinaryTree* tree = malloc(sizeof(BinaryTree));
	tree->rootBTreeNode = NULL;
	tree->Add = BinaryTree_User_Add;
	tree->Get = BinaryTree_User_Get;

	return tree;
}


