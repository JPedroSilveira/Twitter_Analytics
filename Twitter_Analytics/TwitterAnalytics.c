#include <stdio.h>
#include <stdlib.h>

#include "Header/File.h"
#include "Header/Generic.h"
#include "Header/AVL.h"

int main(int argc, char *argv[]) {
    /*Teste Lista
	List* list = List_New();

	int l = 1;
	int o = 2;

	list->Add(list, &l);
	list->Add(list, &o);


	int *um = list->Get(list, 0);
	int *dois = list->Get(list, 1);
	printf("\nItem 1: %d", *um);
	printf("\nItem 2: %d", *dois);
    */

	if (argumentsError(argc)) return 0;

	FILE *file1, *file2, *OUTPUT;

	//file1 = fopen(argv[1], "r");
	//file2 = fopen(argv[2], "r");
	file1 = fopen("file1.txt", "r");
	file2 = fopen("file2.txt", "r");

	if (filesError(file1, file2)) return 0;
	
	List* argumentsForOpList = readArgumentsForOp(file2);
	ArgumentsForOp* teste = argumentsForOpList->Get(argumentsForOpList, 0);
	printf("%c\n", teste->opChar);
	printf("%d\n", teste->number);
	printf("%s\n", teste->name);


    testaFuncoesGenericas();
    avl_testa();
    return 0;
}
