#include "../Header/AVL.h"

int AVL_height(AvlTreeNode* node) {
	if (node == NULL) {
		return 0;
	}
    return node->height;
} 

int AVL_nodeIsEmpty(AvlTreeNode* node) {
	if (node == NULL) {
		return true;
	} else {
		return false;
	}
}

AvlTree* AVL_newTreeInt() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_Int;

	return tree;
}

AvlTree* AVL_newTreeChar() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_Char;

	return tree;
}

AvlTree* AVL_newTreeString() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_String;

	return tree;
}

AvlTree* AVL_newTreeUserByName() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_UserByName;

	return tree;
}

AvlTree* AVL_newTreeUserByTweetCount() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_UserByTweetCount;

	return tree;
}

AvlTree* AVL_newTreeUserByMentionCount() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_UserByMentionCount;

	return tree;
}

AvlTree* AVL_newTreeUserByRetweetCount() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_UserByRetweetCount;

	return tree;
}

AvlTree* Avl_newTreeUserByEngagementCount() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_UserByEngagementCount;

	return tree;
}

AvlTree* AVL_newTreeHashtagByTweetCount() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_HashtagByTweetCount;

	return tree;
}

AvlTree* AVL_newTreeHashtagByName() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_HashtagByName;

	return tree;
}

AvlTree* AVL_newTreeTweetByRetweetCount() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_TweetByReTweetCountAndText;

	return tree;
}

AvlTreeNode* AVL_newNode(void* key) {
	AvlTreeNode* node = (AvlTreeNode*)malloc(sizeof(AvlTreeNode));

	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->mother = NULL;
	node->height = 1; //Nodo folha
	return node;
}

AvlTreeNode* AVL_rightRotate(AvlTreeNode* root) {
	AvlTreeNode* leftChild = root->left; //Salva o filho esquerdo
	AvlTreeNode* rightChildLeft = leftChild->right; //Salva o filho direito do filho esquerdo

    // Rotaciona 
	leftChild->right = root;
	root->left = rightChildLeft;

	//Troca os filhos
	leftChild->mother = root->mother;
	if (!AVL_nodeIsEmpty(root->mother)) {
		if (AVL_isRigthChild(root)) {
			root->mother->right = leftChild;
		} else {
			root->mother->left = leftChild;
		}
	}
	root->mother = leftChild;

	if (!AVL_nodeIsEmpty(rightChildLeft)) {
		rightChildLeft->mother = root;
	}

    // Atualiza a altura da árvore
	root->height = CompareUtils_maxInt(AVL_height(root->left), AVL_height(root->right))+1;
	leftChild->height = CompareUtils_maxInt(AVL_height(leftChild->left), AVL_height(leftChild->right))+1;

    // Retorna a nova raiz
    return leftChild;
} 

AvlTreeNode* AVL_leftRotate(AvlTreeNode* root) {
	AvlTreeNode* rightChild = root->right; //Salva o filho direito
	AvlTreeNode* leftChildRight = rightChild->left; //Salva o filho esquerdo do filho direito

    // Rotaciona 
	rightChild->left = root;
	root->right = leftChildRight;

	//Troca os filhos
	rightChild->mother = root->mother;
	if (!AVL_nodeIsEmpty(root->mother)) {
		if (AVL_isRigthChild(root)) {
			root->mother->right = rightChild;
		} else {
			root->mother->left = rightChild;
		}
	}

	root->mother = rightChild;

	if (!AVL_nodeIsEmpty(leftChildRight)) {
		leftChildRight->mother = root;
	}

    // Atualiza a altura da árvore
	root->height = CompareUtils_maxInt(AVL_height(root->left), AVL_height(root->right)) + 1;
	rightChild->height = CompareUtils_maxInt(AVL_height(rightChild->left), AVL_height(rightChild->right))+1;

    // Retorna a nova raiz
    return rightChild;
} 

int AVL_getBalance(AvlTreeNode* node) {
	if (node == NULL) {
		return 0;
	}
    return AVL_height(node->left) - AVL_height(node->right);
} 

AvlTreeNode* AVL_insertInt(AvlTree* tree, int key) {
	int* memoryKey = (int*)malloc(sizeof(int));
	*memoryKey = key;

	return AVL_insert(tree, NULL, memoryKey);
}

AvlTreeNode* AVL_insertChar(AvlTree* tree, char key) {
	char* memoryKey = (char*)malloc(sizeof(char));
	*memoryKey = key;

	return AVL_insert(tree, NULL, memoryKey);
}

AvlTreeNode* AVL_insertString(AvlTree* tree, char* key) {
	char* memoryKey = malloc(sizeof(char*));
	strcpy(memoryKey, key);

	return AVL_insert(tree, NULL, memoryKey);
}

AvlTreeNode* AVL_balanceNode(AvlTreeNode* node) {
	AvlTreeNode* _return = node;

	//Verifica se o nó existe
	if (!AVL_nodeIsEmpty(node)) {
		//Busca o fator de balanceamento do nó
		int balance = AVL_getBalance(node);
		int time = 0;

		//Realiza o procedimento até o nó estar balanceado
		while (balance > 1 || balance < -1) {
			if (balance > 1) { //Positivo - Rotação direita
				balance = AVL_getBalance(node->left);
				if (balance >= 0) {
					//Rotação simples direita
					if (time == 0) {
						_return = AVL_rightRotate(node);
					} else {
						AVL_rightRotate(node);
					}
				} else if (balance < 0) {
					//Rotação dupla direita
					node->left = AVL_leftRotate(node->left);
					if (time == 0) {
						_return = AVL_rightRotate(node);
					} else {
						AVL_rightRotate(node);
					}
				}
			} else if (balance < -1) { //Negativo - Rotação esquerda
				balance = AVL_getBalance(node->right);
				if (balance > 0) {
					//Rotação dupla esquerda
					node->right = AVL_rightRotate(node->right);
					if (time == 0) {
						_return = AVL_leftRotate(node);
					} else {
						AVL_leftRotate(node);
					}
				} else if (balance <= 0) {
					//Rotação simples esquerda
					if (time == 0) {
						_return = AVL_leftRotate(node);
					} else {
						AVL_leftRotate(node);
					}
				}
			}
			time++;
			balance = AVL_getBalance(node);
		}
	}

	return _return;
}

AvlTreeNode* AVL_insert(AvlTree* tree, AvlTreeNode* mother, void* key) {
	AvlTreeNode* newNode = NULL;
	AvlTreeNode* root = NULL;
	AvlTreeNode* subTree = NULL;

    // 1. Verifica se a árvore existe e tem comparador
	if (tree == NULL || tree->compare == NULL) {
		return NULL;
	}

	// 1.1 Busca o local da inserção
	if (tree->root == NULL) { //Caso base, sub-árvore vazia
		tree->root = AVL_newNode(key);
		tree->root->mother = mother;

		newNode = tree->root;
	} else { //Caso haja elementos continuar a busca pelo local para inserir o novo nodo
		int compareResult = tree->compare(key, tree->root->key);

		if (compareResult == COMPARE_SMALLER) {
			root = tree->root;
			tree->root = tree->root->left;
			newNode = AVL_insert(tree, root, key); //Compara a sub-árvore
			subTree = tree->root;
			tree->root = root;
			tree->root->left = subTree;
		} else if (compareResult == COMPARE_BIGGER) {
			root = tree->root;
			tree->root = tree->root->right;
			newNode = AVL_insert(tree, root, key); //Compara a sub-árvore
			subTree = tree->root;
			tree->root = root;
			tree->root->right = subTree;
		}
		else { // Se for igual a um existente retorna o mesmo
			return tree->root;
		}

		// 2. Atualiza a altura do seu nodo antecessor
		tree->root->height = 1 + CompareUtils_maxInt(AVL_height(tree->root->left), AVL_height(tree->root->right));

		// 3. Balanceia o nodo antecessor
		tree->root = AVL_balanceNode(tree->root);
	}

    //Retorna o novo nodo
	return newNode;
}

void AVL_remove(AvlTree* tree, AvlTreeNode* nodeToRemove) {
	//Valida se a chave existe na árvore
	nodeToRemove = AVL_get(tree, nodeToRemove->key);

	if (!AVL_nodeIsEmpty(nodeToRemove)) { //Verifica se o nodo existe
		//Caso tenha dois filhos
		AvlTreeNode* deepestNodeToMove = NULL;

		if (AVL_isLeaf(nodeToRemove)) { 
			//Caso seja folha apenas o remove
			if (!AVL_nodeIsEmpty(nodeToRemove->mother)) {
				if (AVL_isRigthChild(nodeToRemove)) {
					nodeToRemove->mother->right = NULL;
				}
				else { //Se for filho esquerdo
					nodeToRemove->mother->left = NULL;
				}
				deepestNodeToMove = nodeToRemove->mother;
			} else {
				tree->root = NULL;
			}
		} else {
			//Caso tenha filhos

			//Busca se possui apenas um filho
			AvlTreeNode* onlyChild = AVL_hasJustOneSubTree(nodeToRemove); 

			if (!AVL_nodeIsEmpty(onlyChild)) { 
				//Caso tenha apenas um filho basta apontar sua mãe para o seu filho
				if (!AVL_nodeIsEmpty(nodeToRemove->mother)) {
					if (AVL_isRigthChild(nodeToRemove)) {
						nodeToRemove->mother->right = onlyChild;
					}
					else {
						nodeToRemove->mother->left = onlyChild;
					}
				} else {
					tree->root = onlyChild;
				}
				
				onlyChild->mother = deepestNodeToMove = nodeToRemove->mother;
			} else { 
				//Busca o menor filho para substituir o nó removido
				AvlTreeNode* smallestChild = AVL_getSmallestChild(nodeToRemove); 

				//Remove a ligação da antiga mãe do menor filho do nó a ser removido
				smallestChild->mother->left = NULL;

				//Troca a referência da mãe do nó a ser removido para o substituto
				if (!AVL_nodeIsEmpty(nodeToRemove->mother)) {
					if (AVL_isRigthChild(nodeToRemove)) {
						//Se o nó a ser removido for filho direito
						nodeToRemove->mother->right = smallestChild;
					} else {
						//Se o nó a ser removido for filho esquerdo
						nodeToRemove->mother->left = smallestChild;
					}
				} else {
					tree->root = smallestChild;
				}

				smallestChild->mother = nodeToRemove->mother;

				if (!AVL_isLeaf(smallestChild)) { 
					//Caso o nó mais profundo das sub-árvores esquerdas não for nó folha
					//Pega seu nó mais profundo direito para salvar como pai da sub-árvore esquerda e direita do nó removido 
					deepestNodeToMove = AVL_getBiggestChild(smallestChild);
				} else {
					//Caso não, segue com o menor nó para salva-lo como pai da sub-árvore esquerda e direita do nó removido 
					deepestNodeToMove = smallestChild;
				}

				//Verifica se o nó removido possui sub-árvore esquerda para fazer a mudança
				if (!AVL_nodeIsEmpty(nodeToRemove->left)) {
					deepestNodeToMove->right = nodeToRemove->left;
					nodeToRemove->left->mother = deepestNodeToMove;
							
					//Atualiza o maior nó para a nova sub-árvore direita
					deepestNodeToMove = AVL_getBiggestChild(deepestNodeToMove);
				}

				//Salva a sub-árvore direita do nó removido
				deepestNodeToMove->right = nodeToRemove->right;
				if (!AVL_nodeIsEmpty(nodeToRemove->right)) {
					nodeToRemove->right->mother = deepestNodeToMove;
				}
			}
		} 

		//Correção de altura e balanceamento
		while (!AVL_nodeIsEmpty(deepestNodeToMove)) {
			//Atualiza a altura do nodo mais profundo movido até a raiz
			deepestNodeToMove->height = 1 + CompareUtils_maxInt(AVL_height(deepestNodeToMove->left), AVL_height(deepestNodeToMove->right));
			AVL_balanceNode(deepestNodeToMove);
			deepestNodeToMove = deepestNodeToMove->mother;
		}

		//Corrigir root da árvore
		while (!AVL_nodeIsEmpty(tree->root) && !AVL_nodeIsEmpty(tree->root->mother)) {
			tree->root = tree->root->mother;
		}
	}
}

int AVL_isLeaf(AvlTreeNode* node) {
	if (node->left == NULL && node->right == NULL) {
		return true;
	} else {
		return false;
	}
}

AvlTreeNode* AVL_hasJustOneSubTree(AvlTreeNode* node) {
	if (node->left != NULL && node->right == NULL) { //Caso tenha apenas filho da esquerda
		return node->left;
	} else if(node->left == NULL && node->right != NULL) { //Caso tenha apenas filho da direita
		return node->right;
	} else { //Caso seja folha ou tenha dois filhos
		return NULL;
	}
}

AvlTreeNode* AVL_getSmallestChild(AvlTreeNode* node) {
	if (node->left != NULL) { //Caso tenha filho a esquerda continua a recursão
		return AVL_getSmallestChild(node->left);
	} else { //Caso não returna o nó
		return node;
	}
}

AvlTreeNode* AVL_getBiggestChild(AvlTreeNode* node) {
	if (node->right != NULL) { //Caso tenha filho a esquerda continua a recursão
		return AVL_getBiggestChild(node->right);
	}
	else { //Caso não returna o nó
		return node;
	}
}

int AVL_isRigthChild(AvlTreeNode* node) {
	return node->mother->right == node;
}

AvlTreeNode* AVL_get(AvlTree* tree, void* key) {
	AvlTreeNode* root = tree->root;
	AvlTreeNode* node = NULL;

	if (!AVL_nodeIsEmpty(root)) {
		int compareResult = tree->compare(key, root->key);

		if (compareResult == COMPARE_BIGGER) {
			tree->root = root->right; //Pega sub-arvore direita
			node = AVL_get(tree, key);
		}
		else if (compareResult == COMPARE_SMALLER) {
			tree->root = root->left; //Pega sub-arvore esquerda
			node = AVL_get(tree, key);
		}
		else if (compareResult == COMPARE_EQUAL) {
			return root; //Retorna o proprio nodo
		}

		tree->root = root; //Restaura a raiz da sub-arvore
	}
	
	return node; //Retorna o nodo encontrado ou NULL
}

AvlTreeNode* AVL_getInt(AvlTree* tree, int key) {
	return AVL_get(tree, &key);
}

AvlTreeNode* AVL_getChar(AvlTree* tree, char key)
{
	return AVL_get(tree, &key);
}

AvlTreeNode* AVL_getString(AvlTree* tree, char* key)
{
	return AVL_get(tree, key);
}

void AVL_preOrderInt(AvlTreeNode* root) {
	if (!AVL_nodeIsEmpty(root)) {
		AvlTreeNode* temp = root;

        printf("%d ", *((int*)(root->key)));

		temp = root->left;
		AVL_preOrderInt(temp);

		temp = root->right;
		AVL_preOrderInt(temp);
    } 
} 

void AVL_preOrderChar(AvlTreeNode* root) {
	if (!AVL_nodeIsEmpty(root)) {
		printf("%c ", *((char*)(root->key)));

		root = root->left;
		AVL_preOrderChar(root);

		root = root->right;
		AVL_preOrderChar(root);
	}
}

void AVL_preOrderString(AvlTreeNode* root) {
	if (!AVL_nodeIsEmpty(root)) {
		printf("%s ", ((char*)(root->key)));

		root = root->left;
		AVL_preOrderString(root);

		root = root->right;
		AVL_preOrderString(root);
	}
}

void AVL_testInt() {
	AvlTree* tree = AVL_newTreeInt();

	AvlTreeNode* testeXVIII = AVL_insertInt(tree, 10);
	AvlTreeNode* teste = AVL_insertInt(tree, 20);
	AvlTreeNode* testeXI = AVL_insertInt(tree, 30);
	AvlTreeNode* teste3 = AVL_insertInt(tree, 40);
	AvlTreeNode* testeXVII = AVL_insertInt(tree, 50);
	AvlTreeNode* testeXVI = AVL_insertInt(tree, 25);
	AvlTreeNode* testeX = AVL_insertInt(tree, 38);
	AvlTreeNode* teste2 = AVL_insertInt(tree, 5);
	AvlTreeNode* testeXII = AVL_insertInt(tree, 22);
	AvlTreeNode* teste4 = AVL_insertInt(tree, 15);
	AvlTreeNode* testeXV = AVL_insertInt(tree, 27);
	AvlTreeNode* teste6 = AVL_insertInt(tree, 37);
	AvlTreeNode* teste5 = AVL_insertInt(tree, 100);
	AvlTreeNode* testeXIII = AVL_insertInt(tree, 23);
	AvlTreeNode* testeXIV = AVL_insertInt(tree, 7);
	AVL_preOrderInt(tree->root);

	printf("\nBuscando por 40, resultado: %d \n", *((int*)AVL_getInt(tree, 40)->key));

	AVL_remove(tree, teste);
    AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, teste);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, teste2);
	AVL_preOrderInt(tree->root); 
	printf("\n\n");

	AVL_remove(tree, teste3);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, teste4);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, teste4);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, teste5);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, teste6);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeX);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeX);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXI);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXII);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXII);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXIII);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXIV);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXV);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXVI);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXVII);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, testeXVIII);
	AVL_preOrderInt(tree->root);
	printf("\n\n");

	AVL_remove(tree, teste);
	AVL_preOrderInt(tree->root);
	printf("\n\n");
	
} 

void AVL_testChar() {
	AvlTree* tree = AVL_newTreeChar();

	AVL_insertChar(tree, 'a');
	AVL_insertChar(tree, 'b');
	AVL_insertChar(tree, 'd');
	AVL_insertChar(tree, 'e');
	AVL_insertChar(tree, 'f');
	AVL_insertChar(tree, 'c');

	printf("\nBuscando por d, resultado: %c \n", *((char*)AVL_getChar(tree, 'd')->key));

	AVL_preOrderChar(tree->root);

}

void AVL_testString() {
	AvlTree* tree = AVL_newTreeString();

	AVL_insertString(tree, "abacaxi");
	AVL_insertString(tree, "arvore");
	AVL_insertString(tree, "casa");
	AVL_insertString(tree, "dado");
	AVL_insertString(tree, "egua");
	AVL_insertString(tree, "bola");

	printf("\nBuscando por abacaxi, resultado: %s \n", (char*)(AVL_getString(tree, "abacaxi")->key));

	AVL_preOrderString(tree->root);
}


