#include <stdio.h>
#include <stdlib.h>

typedef struct s_Node {
	void* data;
	struct s_Node* next;
} Node;

typedef struct s_List {
	Node* header;
	void* (*Get) (struct s_List*, int);
	struct s_List* (*Add) (struct s_List*, void*);
} List;

List* List_New();
List* List_Add(List*, void*);
void* List_Get(List *self, int index);



