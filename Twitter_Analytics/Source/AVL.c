#include "../Header/AVL.h"
#include "../Header/Boolean.h"

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

AvlTree* AVL_newTreeHashtagByTweetCount() {
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_HashtagByTweetCount;

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
	root->mother = rightChild;

	if (!AVL_nodeIsEmpty(leftChildRight)) {
		leftChildRight->mother = root;
	}

    // Atualiza a altura da árvore
	rightChild->height = CompareUtils_maxInt(AVL_height(rightChild->left), AVL_height(rightChild->right))+1;
	root->height = CompareUtils_maxInt(AVL_height(root->left), AVL_height(root->right))+1;

    // Retorna a nova raiz
    return rightChild;
} 

int AVL_getBalance(AvlTreeNode* node) {
	if (node == NULL) {
		return false;
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

	return AVL_insert(tree, memoryKey);
}

AvlTreeNode* AVL_insertString(AvlTree* tree, char* key) {
	char* memoryKey = malloc(sizeof(char*));
	strcpy(memoryKey, key);

	return AVL_insert(tree, memoryKey);
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

		// 3. Pega o fator de balanceamente do nodo antecessor e verifica se a árvore está desbalanceada
		int balance = AVL_getBalance(tree->root);

		// Em caso de nodo desbalanceado verificar qual o caso e re-balanceia


		if (balance > 1 && tree->compare(key, tree->root->left->key) == COMPARE_SMALLER) { // Esquerda Esquerda
			tree->root = AVL_rightRotate(tree->root);
		} else if (balance < -1 && tree->compare(key, tree->root->right->key) == COMPARE_BIGGER) { // Direita Direita
			tree->root = AVL_leftRotate(tree->root);
		} else if (balance > 1 && tree->compare(key, tree->root->left->key) == COMPARE_BIGGER) { // Esquerda Direita 
			tree->root->left = AVL_leftRotate(tree->root->left);
			tree->root = AVL_rightRotate(tree->root);
		} else if (balance < -1 && tree->compare(key, tree->root->right->key) == COMPARE_SMALLER) { // Direita Esquerda
			tree->root->right = AVL_rightRotate(tree->root->right);
			tree->root = AVL_leftRotate(tree->root);
		}
	}

    //Retorna o novo nodo
	return newNode;
}

void AVL_remove(AvlTree* tree, AvlTreeNode* nodeToRemove, void* key) {
	if (AVL_nodeIsEmpty(nodeToRemove)) { //Verifica se o nodo existe
		
		//Caso for raiz da árvore apenas remove a raiz
		if (tree->root == nodeToRemove) { 
			tree->root = NULL;
		} else {
			//Casos com nó mãe
			if (AVL_isLeaf(nodeToRemove)) { //Caso seja folha apenas o remove
				if (AVL_isRigthChild(nodeToRemove)) { //Se for filho direito
					nodeToRemove->mother->right = NULL; //Remove o filho direita da sua mãe
				}
				else { //Se for filho esquerdo
					nodeToRemove->mother->left = NULL; //Remove o filho esquerdo da sua mãe
				}

				//Atualiza a altura do seu nodo mãe
				nodeToRemove->mother->height = 1 + CompareUtils_maxInt(AVL_height(nodeToRemove->mother->left), AVL_height(nodeToRemove->mother->right));
			} else { //Caso tenha filhos
				AvlTreeNode* onlyChild = AVL_hasJustOneSubTree(nodeToRemove); //Busca se possui apenas um filho

				if (!AVL_nodeIsEmpty(onlyChild)) { //Caso tenha apenas um filho
					if (AVL_isRigthChild(nodeToRemove)) { //Se o nó a ser removido for filho direito
						nodeToRemove->mother->right = onlyChild; //Passa o filho do nó removido como filho direito no seu lugar
					}
					else { //Se for filho esquerdo
						nodeToRemove->mother->left = onlyChild; //Passa o filho do nó removido como filho esquerdo no seu lugar
					}

					//Atualiza a altura do seu nodo mãe
					nodeToRemove->mother->height = 1 + CompareUtils_maxInt(AVL_height(nodeToRemove->mother->left), AVL_height(nodeToRemove->mother->right));
				} else { //Caso tenha dois filhos

					AvlTreeNode* smallestChild = AVL_getSmallestChild(nodeToRemove); //Busca o menor filho para substituir o nó removido
					AvlTreeNode* temp; //Nodo temporário

					//Remove a ligação da antiga mãe do menor filho do nó a ser removido (O menor filho sempre é folha)
					if (AVL_isRigthChild(smallestChild)) { //Se o nó a ser removido for filho direito
						smallestChild->mother->right = NULL; //Salva o menor filho no lugar do nó removido
					} else { //Se o nó a ser removido for filho esquerdo
						smallestChild->mother->left = NULL;
					}

					//Troca o filho da mãe do nó a ser removido
					if (AVL_isRigthChild(nodeToRemove)) { //Se o nó a ser removido for filho direito
						nodeToRemove->mother->right = smallestChild;
						smallestChild->mother = nodeToRemove->mother;
					} else { //Se o nó a ser removido for filho esquerdo
						nodeToRemove->mother->left = smallestChild;
						smallestChild->mother = nodeToRemove->mother;
					}

					if (AVL_isLeaf(smallestChild)) { //Caso o menor filho for folha apenas salva seus filhos como o filho do nó a ser removido
						smallestChild->right = nodeToRemove->right;
						nodeToRemove->right->mother = smallestChild;

						smallestChild->left = nodeToRemove->left;
						nodeToRemove->left->mother = smallestChild;

						temp = smallestChild;

						//Correção de balanceamento
						while (temp != tree->root) {
							//Atualiza a altura do nodo mais profundo movido até a raiz
							temp->height = 1 + CompareUtils_maxInt(AVL_height(temp->left), AVL_height(temp->right));
							temp = temp->mother;
						}
					} else { //Se não for folha então possui apenas filho a direita
						AvlTreeNode* biggestChild = AVL_getBiggestChild(nodeToRemove); //Busca o maior filho do menor filho do nó removido (nó folha)

						//Salva ele como mãe do filho direito do novo removido
						biggestChild->right = nodeToRemove->right;
						nodeToRemove->right->mother = biggestChild;
						
						temp = biggestChild;

						//Correção de balanceamento
						while (temp != tree->root) {
							//Atualiza a altura do nodo mais profundo movido até a raiz
							temp->height = 1 + CompareUtils_maxInt(AVL_height(temp->left), AVL_height(temp->right));
							temp = temp->mother;
						}
					}
				}
			}
		}
	} else {
		return NULL;
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
		return AVL_getSmallerChild(node->left);
	} else { //Caso não returna o nó
		return node;
	}
}

AvlTreeNode* AVL_getBiggestChild(AvlTreeNode* node) {
	if (node->left != NULL) { //Caso tenha filho a esquerda continua a recursão
		return AVL_getSmallerChild(node->left);
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
	int compareResult = tree->compare(key, root->key);

	if (compareResult == COMPARE_BIGGER) {
		tree->root = root->right; //Pega sub-arvore direita
		node = AVL_get(tree, key);
	} else if (compareResult == COMPARE_SMALLER){
		tree->root = root->left; //Pega sub-arvore esquerda
		node = AVL_get(tree, key);
	}
	else if(compareResult == COMPARE_EQUAL){
		return root; //Retorna o proprio nodo
	}

	tree->root = root; //Restaura a raiz da sub-arvore

	return node; //Retorna o nodo encontrado ou NULL
}

AvlTreeNode* AVL_getInt(AvlTree* tree, int key)
{
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

void AVL_preOrderInt(AvlTree* tree) {
	if (tree != NULL && tree->root != NULL) {
		AvlTreeNode* root = tree->root;
        printf("%d ", *((int*)(root->key)));

		tree->root = root->left;
		AVL_preOrderInt(tree);

		tree->root = root->right;
		AVL_preOrderInt(tree);
    } 
} 

void AVL_preOrderChar(AvlTree* tree) {
	if (tree != NULL && tree->root != NULL) {
		AvlTreeNode* root = tree->root;
		printf("%c ", *((char*)(root->key)));

		tree->root = root->left;
		AVL_preOrderChar(tree);

		tree->root = root->right;
		AVL_preOrderChar(tree);
	}
}

void AVL_preOrderString(AvlTree* tree) {
	if (tree != NULL && tree->root != NULL) {
		AvlTreeNode* root = tree->root;
		printf("%s ", ((char*)(root->key)));

		tree->root = root->left;
		AVL_preOrderString(tree);

		tree->root = root->right;
		AVL_preOrderString(tree);
	}
}

void AVL_testInt() {
	AvlTree* tree = AVL_newTreeInt();

    AvlTreeNode* teste = AVL_insertInt(tree, 10);
	teste = AVL_insertInt(tree, 20);
	teste = AVL_insertInt(tree, 30);
	teste = AVL_insertInt(tree, 40);
	teste = AVL_insertInt(tree, 50);
    teste = AVL_insertInt(tree, 25);

	printf("\nBuscando por 40, resultado: %d \n", *((int*)AVL_getInt(tree, 40)->key));

    AVL_preOrderInt(tree);
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

	AVL_preOrderChar(tree);

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

	AVL_preOrderString(tree);
}


