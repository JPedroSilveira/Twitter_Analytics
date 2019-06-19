#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./AVL.h"

#define OP_NAME_MAX_CHAR_LENGTH 30
#define BASE 10

typedef struct s_ArgumentsForOp {
	char opChar;
	int number;
	char name[OP_NAME_MAX_CHAR_LENGTH];
} ArgumentsForOp;

// Recebe a quantidade de parametros na chamada do programa
// Caso seja maior que 3 (a.out, arquivo1, arquivo2) nao executa o programa
int argumentsError(int argc);

//Retorna 1 caso tenha ocorrido erro ao abrir os arquivos e 0 caso contrário
int filesError(FILE *input1, FILE *input2);

//Inicializa um novo ArgumentsForOp
ArgumentsForOp ArgumentsForOp_New();

//Lê o arquivos com os dados das operações e salva em uma lista de ArgumentsForOp
List* readArgumentsForOp(FILE *file);

//Lê um valor inteiro em uma arquivos
int readInt(FILE *file);

//Lê o arquivos dos Tweets
void readTweets(FILE *file);
