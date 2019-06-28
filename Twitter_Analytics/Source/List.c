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
	} else {
		//Caso a lista nao estiver vazia, procura até achar um nodo sem filho
		Node* listNode = list->header;
		while (listNode->next != NULL) {
			listNode = listNode->next;
		}
		listNode->next = node;
	}

	//Incrementa a contagem de tamanho da lista
	list->length = list->length + 1;
}

void ListAssociatedHashtag_Add(List* list, AssociatedHashtag* data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;

	//Se a lista estiver vazia adiciona no cabecalho
	if (list->header == NULL) {
		list->header = node;
	} else {
		Node* mother = list->header;
		AssociatedHashtag* aMother = mother->data;

		Node* temp = mother;
		AssociatedHashtag* aTemp = temp->data;

		//Procura o nodo para encaixar
		while (temp != NULL && (aTemp->count > data->count || (aTemp->count == data->count && CompareUtils_String(data->name, aTemp->name) == ASSOCIATED_COMPARE_BIGGER))) {
			mother = temp;
			aMother = aTemp;
			temp = temp->next;
			if (temp != NULL) {
				aTemp = temp->data;
			}
		}

		//Caso o novo nó venha a ser a nova raiz
		if (list->header == temp) {
			list->header = node;
		} else {
			mother->next = node;
		}

		node->next = temp;
	}

	//Incrementa a contagem de tamanho da lista
	list->length = list->length + 1;
}

void List_Remove(List* list, Node* mother, Node* nodeToRemove) {
	if (nodeToRemove != NULL) {
		if (list->header == nodeToRemove) {
			list->header = nodeToRemove->next;
		} else {
			mother->next = nodeToRemove->next;
		}
		list->length = list->length - 1;
	}
}

void List_RemoveByIndex(List* list, int index) {
	//Busca o nodo
	Node* node = list->header;
	Node* mother = NULL;
	int count = 0;
	while (node->next && count < index) {
		mother = node;
        node = node->next;
		count++;
	}
	
	List_Remove(list, mother, node);
}

List* List_New() {
	List* list = (List*)malloc(sizeof(List));
	list->header = NULL;
	list->length = 0;
	return list;
}
