// C program for generic linked list 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include "../Header/Generic.h"


/* Function to add a node at the beginning of Linked List. 
This function expects a pointer to the data to be added 
and size of the data type */
void push(genericNode** head_ref, void *new_data, size_t data_size) { 
	// Allocate memory for node 
	genericNode* new_node = (struct sGenericNode*) malloc(sizeof(struct sGenericNode)); 

	new_node->data = malloc(data_size); 
	new_node->next = (*head_ref); 

	// Copy contents of new_data to newly allocated memory. 
	// Assumption: char takes 1 byte. 
	int i; 
	for (i = 0; i < data_size; i++) {
		*((char *)new_node->data + i) = *((char *)new_data + i);
	}

	// Change head pointer as new node is added at the beginning 
	(*head_ref) = new_node; 
} 

/* Function to print nodes in a given linked list. fpitr is used 
to access the function to be used for printing current node data. 
Note that different data types need different specifier in printf() */
void printList(genericNode *node, void (*fptr)(void *)) {
	while (node != NULL) { 
		(*fptr)(node->data); 
		node = node->next; 
	} 
}

// Function to print an integer 
void printInt(void *n) { 
printf(" %d", *(int *)n); 
} 

// Function to print a float 
void printFloat(void *f) { 
printf(" %f", *(float *)f); 
} 

void printChar(void *c){
    printf(" %c",*(char *) c);
}

void printString(void *s) {
    for (int i = 0; i < 25; i++) { // Arrumar para uma variavel ao inves de 25
        printf("%c",*((char *)s + i));
//        printf("%c",*(char *)(s + 4));
    }
}

/* Driver program to test above function */
int testaFuncoesGenericas() { 
	genericNode *start = NULL; 

	// Create and print an int linked list 
	unsigned int_size = sizeof(int); 
	int arr[] = {10, 20, 30, 40, 50}, i; for (i=4; i>=0; i--) 
	push(&start, &arr[i], int_size); 
	printf("Created integer linked list is \n"); 
	printList(start, printInt); 

	// Create and print a float linked list 
	unsigned float_size = sizeof(float); 
	start = NULL; 
	float arr2[] = {10.1f, 20.2f, 30.3f, 40.4f, 50.5f}; 
	for (i=4; i>=0; i--) 
	push(&start, &arr2[i], float_size); 
	printf("\n\nCreated float linked list is \n"); 
	printList(start, printFloat); 

    // Create and print a char linked list
    unsigned char_size = sizeof(char);
    start = NULL;
    char arr3[] = {'a', 'b', 'c', 'd'};
    for (i = 4; i>=0; i--) push (&start, &arr3[i], char_size);
    printf("\n\nCreated char linked list is \n");
    printList(start, printChar);

    // Create and print a string linked list
    start = NULL;
    char *arr4[4];

    arr4[0] = "ba h";
    arr4[1] = "yadd a";
    arr4[2] = "lo l";
    arr4[3] = "string 4";
    
    // Testes para saber como definir o tamanho ideal de um array de strings
    printf("\n\nSize of arr4[0] = %lu\n",sizeof(arr4[0]));
    printf("Size of arr4[1] = %lu\n",sizeof(arr4[1]));
    printf("Size of arr4[] = %lu\n",sizeof(arr4));
    printf("Size of strlen arr4[0] = %lu\n",strlen(arr4[0]));
    printf("Size of strlen arr4[1] = %lu\n",strlen(arr4[1]));
//    printf("\n%lu sizeofchar64\n",sizeof(char*)*64); teste multiplicando por valor
    

//    int n = 1;
//    printf("\nTesta o %d  elemento do array\n%s\n", n, arr4[n]);

    printf("\n\nCreated string linked list is \n");
    for (int i = 0; i >= 0; i--) push(&start, arr4[i],sizeof(char*) * strlen(arr4[i]));
    printList(start, printString);
    printf("\n");

	return 0; 
} 

// strlen = qtd de chars na string
// usar str len para passar char por char e botar um \0 no final
 

