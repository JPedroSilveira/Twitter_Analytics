#include "../Header/List.h"

void* List_Get(List* self, int index) {
	Node* node = self->header;
	int count = 0;
	while (node->next && count < index) {
        node = node->next;
		count++;
	}
	return node->data;
}

void List_Add(List* list, void* data) {
	Node* node = (Node*)malloc(sizeof(Node));
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

List* List_New() {
	List* list = (List*)malloc(sizeof(List));
	list->header = NULL;
	list->Add = List_Add;
	list->Get = List_Get;
	return list;
}
