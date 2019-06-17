#include "../Header/List.h"

//Retorna o enésimo elemento de uma lista
//Caso seja pedido um elemento de posição maior que o último elemento da lista retorna este último
//Caso seja pedido um elemento menor que o elemento de menor posição da lista (negativo) então retorna o primeiro
void* List_Get(List* self, int index) {
	Node* node = self->header;
	int count = 0;
	while (node->next && count < index) {
        node = node->next;
	}
	return node->data;
}

//Adiciona um novo item a uma lista existente // Na primeira etapa de leitura do arquivos pode deixar por ordem de insercao na lista e depois ordenada na ABP
void List_Add(List* list, void* data) {
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;

	//Se a lista estiver vazia adiciona no cabecalho
	if (list->header == NULL) {
		list->header = node;
	}
	else {
		//Caso a lista nao estiver vazia, procura o proximo item vazio e adicionar o novo Node
		Node* listNode = list->header;
		while (listNode->next) {
			listNode = listNode->next;
		}
		listNode->next = node;
	}
}

//Inicializa uma nova lista
List* List_New() {
	List* list = malloc(sizeof(List));
	list->header = NULL;
	list->Add = List_Add;
	list->Get = List_Get;
	return list;
}
