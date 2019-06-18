#include "../Header/AVL.h"

int AVL_height(avlTreeNode *node) {
	if (node == NULL) {
		return 0;
	}
    return node->height;
} 

avlTree* AVL_newTreeInt() {
	avlTree* tree = (avlTree*)malloc(sizeof(avlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_Int;

	return tree;
}

avlTree* AVL_newTreeChar() {
	avlTree* tree = (avlTree*)malloc(sizeof(avlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_Char;

	return tree;
}

avlTree* AVL_newTreeString() {
	avlTree* tree = (avlTree*)malloc(sizeof(avlTree));
	tree->root = NULL;
	tree->compare = CompareUtils_String;

	return tree;
}

avlTreeNode* AVL_newNode(void* key) {
	avlTreeNode* node = (avlTreeNode*)malloc(sizeof(avlTreeNode));

	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; //Nodo folha
	return node;
}

avlTreeNode* AVL_rightRotate(avlTreeNode *y) {
    avlTreeNode *x = y->left; 
    avlTreeNode *T2 = x->right; 

    // Rotaciona 
    x->right = y; 
    y->left = T2; 

    // Atualiza a altura da árvore
    y->height = CompareUtils_maxInt(AVL_height(y->left), AVL_height(y->right))+1;
    x->height = CompareUtils_maxInt(AVL_height(x->left), AVL_height(x->right))+1;

    // Retorna a nova raiz
    return x; 
} 

avlTreeNode* AVL_leftRotate(avlTreeNode *x) {
    avlTreeNode *y = x->right; 
    avlTreeNode *T2 = y->left; 

    // Rotaciona 
    y->left = x; 
    x->right = T2; 

    // Atualiza a altura da árvore
    x->height = CompareUtils_maxInt(AVL_height(x->left), AVL_height(x->right))+1;
    y->height = CompareUtils_maxInt(AVL_height(y->left), AVL_height(y->right))+1;

    // Retorna a nova raiz
    return y; 
} 

int AVL_getBalance(avlTreeNode *node) {
	if (node == NULL) {
		return 0;
	}
    return AVL_height(node->left) - AVL_height(node->right);
} 

avlTreeNode* AVL_insertInt(avlTree* tree, int key) {
	int* memoryKey = (int*)malloc(sizeof(int));
	*memoryKey = key;

	return AVL_insert(tree, memoryKey);
}

avlTreeNode* AVL_insertChar(avlTree* tree, char key) {
	char* memoryKey = (char*)malloc(sizeof(char));
	*memoryKey = key;

	return AVL_insert(tree, memoryKey);
}

avlTreeNode* AVL_insertString(avlTree* tree, char* key) {
	char* memoryKey = malloc(sizeof(char*));
	strcpy(memoryKey, key);

	return AVL_insert(tree, memoryKey);
}

avlTreeNode* AVL_insert(avlTree* tree, void* key) {
    // 1. Verifica se a árvore existe e tem comparador
	if (tree == NULL || tree->compare == NULL) {
		return NULL;
	}

	// 1.1 Busca o local da inserção

	if (tree->root == NULL) { //Caso base, sub-árvore vazia
		tree->root = AVL_newNode(key);

		return tree->root;
	}

	avlTreeNode* node = tree->root;
	avlTreeNode* newNode = NULL;

	int compareResult = tree->compare(key, node->key);

	if (compareResult == -1) {
		tree->root = node->left;
		newNode = AVL_insert(tree, key); //Compara a sub-árvore
		tree->root = node; //Retorna a raiz inicial
		tree->root->left = newNode; //Adiciona a nova sub-árvore
	}
	else if (compareResult == 1) {
		tree->root = node->right;
		newNode = AVL_insert(tree, key);
		tree->root = node; //Retorna a raiz inicial
		tree->root->right = newNode; //Adiciona a nova sub-árvore
	}
	else { // Se for igual a um existente retorna NULL
		return NULL;
	}

    // 2. Atualiza a altura do seu nodo antecessor
    node->height = 1 + CompareUtils_maxInt(AVL_height(node->left), AVL_height(node->right)); 

    // 3. Pega o fator de balanceamente do nodo antecessor e verifica se a árvore está desbalanceada
    int balance = AVL_getBalance(node); 

    // Em caso de nodo desbalanceado verificar qual o caso e re-balanceia

    
	if (balance > 1 && tree->compare(key, node->left->key) == -1) { // Esquerda Esquerda
		tree->root = AVL_rightRotate(node);
	} else if (balance < -1 && tree->compare(key, node->right->key) == 1) { // Direita Direita
		tree->root = AVL_leftRotate(node);
	} else if (balance > 1 && tree->compare(key, node->left->key) == 1) { // Esquerda Direita 
		node->left = AVL_leftRotate(node->left);
		tree->root = AVL_rightRotate(node);
	} else if (balance < -1 && tree->compare(key, node->right->key) == -1) { // Direita Esquerda
		node->right = AVL_rightRotate(node->right);
		tree->root = AVL_leftRotate(node);
	}

    //Retorna o nodo raiz
	return tree->root;
} 

void AVL_preOrderInt(avlTree* tree) {
	if (tree != NULL && tree->root != NULL) {
		avlTreeNode* root = tree->root;
        printf("%d ", *((int*)(root->key)));

		tree->root = root->left;
		AVL_preOrderInt(tree);

		tree->root = root->right;
		AVL_preOrderInt(tree);
    } 
} 

void AVL_preOrderChar(avlTree* tree) {
	if (tree != NULL && tree->root != NULL) {
		avlTreeNode* root = tree->root;
		printf("%c ", *((char*)(root->key)));

		tree->root = root->left;
		AVL_preOrderChar(tree);

		tree->root = root->right;
		AVL_preOrderChar(tree);
	}
}

void AVL_preOrderString(avlTree* tree) {
	if (tree != NULL && tree->root != NULL) {
		avlTreeNode* root = tree->root;
		printf("%s ", ((char*)(root->key)));

		tree->root = root->left;
		AVL_preOrderString(tree);

		tree->root = root->right;
		AVL_preOrderString(tree);
	}
}

void AVL_testInt() {
	avlTree* tree = AVL_newTreeInt();

    AVL_insertInt(tree, 10);
    AVL_insertInt(tree, 20);
    AVL_insertInt(tree, 30);
    AVL_insertInt(tree, 40);
    AVL_insertInt(tree, 50);
    AVL_insertInt(tree, 25);


    AVL_preOrderInt(tree);
} 

void AVL_testChar() {
	avlTree* tree = AVL_newTreeChar();

	AVL_insertChar(tree, 'a');
	AVL_insertChar(tree, 'b');
	AVL_insertChar(tree, 'd');
	AVL_insertChar(tree, 'e');
	AVL_insertChar(tree, 'f');
	AVL_insertChar(tree, 'c');


	AVL_preOrderChar(tree);

}

void AVL_testString() {
	avlTree* tree = AVL_newTreeString();

	AVL_insertString(tree, "abacaxi");
	AVL_insertString(tree, "arvore");
	AVL_insertString(tree, "casa");
	AVL_insertString(tree, "dado");
	AVL_insertString(tree, "egua");
	AVL_insertString(tree, "bola");


	AVL_preOrderString(tree);
}


