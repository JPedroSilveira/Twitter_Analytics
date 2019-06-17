#include<stdio.h> 
#include <string.h>
#include<stdlib.h> 

/* A linked list node */
typedef struct sGenericNode { 
	// Any data type can be stored in this node 
	void *data; 
	struct sGenericNode *next; 
} genericNode; 

void push(genericNode** head_ref, void *new_data, size_t data_size);
void printList(genericNode *node, void (*fptr)(void *));
void printInt(void *n);
void printFloat(void *f);
void printChar(void *c);
void printString(void *s);
int testaFuncoesGenericas();
