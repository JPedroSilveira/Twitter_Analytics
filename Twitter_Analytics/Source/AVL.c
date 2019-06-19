#include "../Header/AVL.h"

int AVL_height(AvlTreeNode* node) {
	if (node == NULL) {
		return 0;
	}
    return node->height;
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

AvlTree * AVL_newTreeUserByName()
{
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_UserByName;

	return tree;
}

AvlTree * AVL_newTreeHashtagByName()
{
	AvlTree* tree = (AvlTree*)malloc(sizeof(AvlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_HashtagByName;

	return tree;
}

AvlTreeNode* AVL_newNode(void* key) {
	AvlTreeNode* node = (AvlTreeNode*)malloc(sizeof(AvlTreeNode));

	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; //Nodo folha
	return node;
}

AvlTreeNode* AVL_rightRotate(AvlTreeNode* y) {
	AvlTreeNode* x = y->left;
	AvlTreeNode* T2 = x->right;

    // Rotaciona 
    x->right = y; 
    y->left = T2; 

    // Atualiza a altura da árvore
    y->height = CompareUtils_maxInt(AVL_height(y->left), AVL_height(y->right))+1;
    x->height = CompareUtils_maxInt(AVL_height(x->left), AVL_height(x->right))+1;

    // Retorna a nova raiz
    return x; 
} 

AvlTreeNode* AVL_leftRotate(AvlTreeNode* x) {
	AvlTreeNode* y = x->right;
	AvlTreeNode* T2 = y->left;

    // Rotaciona 
    y->left = x; 
    x->right = T2; 

    // Atualiza a altura da árvore
    x->height = CompareUtils_maxInt(AVL_height(x->left), AVL_height(x->right))+1;
    y->height = CompareUtils_maxInt(AVL_height(y->left), AVL_height(y->right))+1;

    // Retorna a nova raiz
    return y; 
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

	return AVL_insert(tree, memoryKey);
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

AvlTreeNode* AVL_insert(AvlTree* tree, void* key) {
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
		newNode = tree->root;
	} else { //Caso haja elementos continuar a busca pelo local para inserir o novo nodo

		int compareResult = tree->compare(key, tree->root->key);

		if (compareResult == COMPARE_SMALLER) {
			root = tree->root;
			tree->root = tree->root->left;
			newNode = AVL_insert(tree, key); //Compara a sub-árvore
			subTree = tree->root;
			tree->root = root;
			tree->root->left = subTree;
		}
		else if (compareResult == COMPARE_BIGGER) {
			root = tree->root;
			tree->root = tree->root->right;
			newNode = AVL_insert(tree, key); //Compara a sub-árvore
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
		}
		else if (balance < -1 && tree->compare(key, tree->root->right->key) == COMPARE_BIGGER) { // Direita Direita
			tree->root = AVL_leftRotate(tree->root);
		}
		else if (balance > 1 && tree->compare(key, tree->root->left->key) == COMPARE_BIGGER) { // Esquerda Direita 
			tree->root->left = AVL_leftRotate(tree->root->left);
			tree->root = AVL_rightRotate(tree->root);
		}
		else if (balance < -1 && tree->compare(key, tree->root->right->key) == COMPARE_SMALLER) { // Direita Esquerda
			tree->root->right = AVL_rightRotate(tree->root->right);
			tree->root = AVL_leftRotate(tree->root);
		}
	}

    //Retorna o novo nodo
	return newNode;
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


