#ifndef _FILEH_
#define _FILEH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./OPES.h"
#include "./Boolean.h"
#include "./CharUtils.h"
#include "./Tweet.h"

#define BASE 10

// Recebe a quantidade de parametros na chamada do programa
// Caso seja maior que 3 (a.out, arquivo1, arquivo2) nao executa o programa
int File_argumentsError(int argc);

//Retorna 1 caso tenha ocorrido erro ao abrir os arquivos e 0 caso contrário
int File_filesError(FILE *input1, FILE *input2, FILE *output);

//Le os dados do arquivos de Tweets e do arquivos contendo as operacoes e retorna na struct OPES
OPES File_readFiles(FILE* fileTweets, FILE* fileOps);

//Lê o arquivos com os dados das operações e salva em uma lista de ArgumentsForOp
List* File_readArgumentsForOp(FILE *file);

//Lê um valor inteiro em uma arquivos
int File_readInt(FILE *file);
 
//Função auxiliar para ler todos os caracteres pertencentes a um número
int File_readIntAux(FILE *file, int *count);

//Lê o arquivos dos Tweets
OPES File_readTweets(OPES opes, FILE* file);

//Percorre todas as operações exigidas e executa
void File_executeOpes(OPES* opes);

//Salva o resultado das operações no arquivo de saída
void File_saveOpes(OPES* opes, FILE* output);

//Imprime o nome da operação padronizado no arquivo
void File_printOpData(char opChar, FILE* output, ArgumentsForOp* op);

//Imprime no arquivo de saída os resultados de uma operação do tipo a
void File_printOpA(FILE* output, ArgumentsForOp* op);

//Imprime no arquivo de saída os resultados de uma operação do tipo b
void File_printOpB(FILE* output, ArgumentsForOp* op);

//Imprime no arquivo de saída os resultados de uma operação do tipo c
void File_printOpC(FILE* output, ArgumentsForOp* op);

//Imprime no arquivo de saída os resultados de uma operação do tipo d
void File_printOpD(FILE* output, ArgumentsForOp* op);

//Imprime no arquivo de saída os resultados de uma operação do tipo e
void File_printOpE(FILE* output, ArgumentsForOp* op);

//Imprime no arquivo de saída os resultados de uma operação do tipo f
void File_printOpF(FILE* output, ArgumentsForOp* op);

//Imprime no arquivo de saída os resultados de uma operação do tipo g
void File_printOpG(FILE* output, ArgumentsForOp* op);

#endif _FILEH_