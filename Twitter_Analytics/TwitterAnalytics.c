#include <stdio.h>
#include <stdlib.h>

#include "Header/File.h"
#include "Header/StringUtils.h"

int main(int argc, char *argv[]) {
    /* Teste Lista */
	/*
	List* list = List_New();

	int l = 1;
	int o = 2;

	list->Add(list, &l);
	list->Add(list, &o);


	int *um = list->Get(list, 0);
	int *dois = list->Get(list, 1);
	printf("\nItem 1: %d", *um);
	printf("\nItem 2: %d", *dois);
    

	/* Teste operações */
	/*
	if (argumentsError(argc)) return 0;

	FILE *file1, *file2, *OUTPUT;

	//file1 = fopen(argv[1], "r");
	//file2 = fopen(argv[2], "r");
	file1 = fopen("file1.txt", "r");
	file2 = fopen("file2.txt", "r");

	if (filesError(file1, file2)) return 0;
	
	List* argumentsForOpList = readArgumentsForOp(file2);
	for (int x = 0; x < 7; x++) {
		ArgumentsForOp* teste = argumentsForOpList->Get(argumentsForOpList, x);
		printf("%c\n", teste->opChar);
		printf("%d\n", teste->number);
		printf("%s\n", teste->name);
	}
	

	/*Teste AVL*/
	
	printf("\n\nTeste AVL INT \n");
	AVL_testInt();
	printf("\n\nTeste AVL CHAR \n");
	AVL_testChar();
	printf("\n\nTeste AVL STRING \n");
	AVL_testString();
	

	/*StringUtils Teste*/
	/*
	StringUtils_removeAccentsTest();
	StringUtils_toLowerCaseTest();
	
	/*Fim testes*/
    return 0;
}
