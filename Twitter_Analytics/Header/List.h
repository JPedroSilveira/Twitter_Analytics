#include <stdio.h>
#include <stdlib.h>

typedef struct s_Node {
	void* data;
	struct s_Node* next;
} Node;

typedef struct s_List {
	Node* header;
	void (*Add) (struct s_List*, void*);
	void* (*Get) (struct s_List*, int);
} List;

/*Retorna o enésimo elemento de uma lista.
 Caso seja pedido um elemento de posição maior que o último elemento da lista retorna este último.
 Caso seja pedido um elemento menor que o elemento de menor posição da lista (negativo) então retorna o primeiro.*/
void* List_Get(List *self, int index);

/*Adiciona um novo item a uma lista existente
Na primeira etapa de leitura do arquivos pode deixar por ordem de insercao na lista e depois ordenada na ABP*/
void List_Add(List*, void*);

//Inicializa uma nova lista
List* List_New();


