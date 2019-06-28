#ifndef _LISTH_
#define _LISTH_

#include <stdio.h>
#include <stdlib.h>
#include "./AssociatedHashtag.h"
#include "./Boolean.h"

typedef struct s_Node {
	void* data;
	struct s_Node* next;
} Node;

typedef struct s_List {
	Node* header;
	int length;
} List;

/*Retorna o enésimo elemento de uma lista.
 Caso seja pedido um elemento de posição maior que o último elemento da lista retorna este último.
 Caso seja pedido um elemento menor que o elemento de menor posição da lista (negativo) então retorna o primeiro.*/
void* List_Get(List* self, int index);

/*Adiciona um novo item a uma lista existente*/
void List_Add(List*, void*);

/*Adiciona um novo item a uma lista do tipo AssociatedHashtag em ordem decrescente*/
void ListAssociatedHashtag_Add(List* list, AssociatedHashtag* data);

/*Remove um item da lista, a mãe inicial deve ser a raiz da árvore*/
void List_Remove(List* list, Node* mother, Node* nodeToRemove);

/*Remove um item da lista pelo seu indice, a mãe inicial deve ser a raiz da árvore*/
void List_RemoveByIndex(List* list, int index);


//Inicializa uma nova lista
List* List_New();

#endif