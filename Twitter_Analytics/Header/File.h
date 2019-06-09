#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./Tweet.h"

#define OP_NAME_MAX_CHAR_LENGTH 30
#define BASE 10

typedef struct s_ArgumentsForOp {
	char opChar;
	int number;
	char name[OP_NAME_MAX_CHAR_LENGTH];
} ArgumentsForOp;

ArgumentsForOp ArgumentsForOp_New();

List* readArgumentsForOp(FILE *file);

void readTweets(FILE *file);

int argumentsError(int argc);

int filesError(FILE *input1, FILE *input2);

// case sensitive
// acentos
