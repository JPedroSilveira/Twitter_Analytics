#include <string.h>
#include "./Tweet.h"

#define COMPARE_BIGGER 1
#define COMPARE_SMALLER -1
#define COMPARE_EQUAL 0

//Compara dois inteiros e retona o maior
int CompareUtils_maxInt(int a, int b);

//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_Int(void* a, void* b);

//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_Char(void* a, void* b);

//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_String(void* a, void* b);

//Compara duas structs User pelo nome
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_UserByName(User* a, User* b);

//Compara duas structs hashtag pelo nome
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_HashtagByTweetCount(Hashtag* a, Hashtag* b);

//Compara duas structs tweet pelo likeCount
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_TweetByReTweetCountAndText(Tweet* a, Tweet* b);