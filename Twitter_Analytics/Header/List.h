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

/*Retorna o en�simo elemento de uma lista.
 Caso seja pedido um elemento de posi��o maior que o �ltimo elemento da lista retorna este �ltimo.
 Caso seja pedido um elemento menor que o elemento de menor posi��o da lista (negativo) ent�o retorna o primeiro.*/
void* List_Get(List* self, int index);

/*Adiciona um novo item a uma lista existente*/
void List_Add(List*, void*);

/*Adiciona um novo item a uma lista do tipo AssociatedHashtag em ordem decrescente*/
void ListAssociatedHashtag_Add(List* list, AssociatedHashtag* data);

/*Remove um item da lista, a m�e inicial deve ser a raiz da �rvore*/
void List_Remove(List* list, Node* mother, Node* nodeToRemove);

/*Remove um item da lista pelo seu indice, a m�e inicial deve ser a raiz da �rvore*/
void List_RemoveByIndex(List* list, int index);


//Inicializa uma nova lista
List* List_New();

#endif