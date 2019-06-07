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

List* List_New();
void List_Add(List*, void*);
void* List_Get(List *self, int index);



