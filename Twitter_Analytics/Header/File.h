#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./OPES.h"

#define BASE 10

// Recebe a quantidade de parametros na chamada do programa
// Caso seja maior que 3 (a.out, arquivo1, arquivo2) nao executa o programa
int File_argumentsError(int argc);

//Retorna 1 caso tenha ocorrido erro ao abrir os arquivos e 0 caso contr�rio
int File_filesError(FILE *input1, FILE *input2);

//Le os dados do arquivos de Tweets e do arquivos contendo as operacoes e retorna na struct OPES
OPES File_readFiles(FILE* fileTweets, FILE* fileOps);

//L� o arquivos com os dados das opera��es e salva em uma lista de ArgumentsForOp
List* File_readArgumentsForOp(FILE *file);

//L� um valor inteiro em uma arquivos
int File_readInt(FILE *file);

//L� o arquivos dos Tweets
OPES File_readTweets(FILE *file);
