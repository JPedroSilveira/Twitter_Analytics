#ifndef _COMPAREUTILSH_
#define _COMPAREUTILSH_

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
int CompareUtils_Int(int* a, int* b);

//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_Char(char* a, char* b);

//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_String(char* a, char* b);

//Compara duas structs User pelo nome
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_UserByName(User* a, User* b);

//Compara duas structs user pela contagem de tweets e nome
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_UserByTweetCount(User* a, User* b);

//Compara duas structs user pela contagem de menções e nome
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_UserByMentionCount(User* a, User* b);

//Compara duas structs user pela contagem de retweets
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_UserByRetweetCount(User* a, User* b);

//Compara duas structs user pela contagem de engajamento
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_UserByEngagementCount(User* a, User* b);

//Compara duas structs hashtag pela contagem de tweets e nome
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_HashtagByTweetCount(Hashtag* a, Hashtag* b);

//Compara duas structs hashtag pelo nome
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_HashtagByName(Hashtag* a, Hashtag* b);

//Compara duas structs tweet pelo likeCount
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_TweetByReTweetCountAndText(Tweet* a, Tweet* b);

//Compara duas structs tweet pelo seu texto
//Retorna COMPARE_BIGGER caso o primeiro valor seja maior que o segundo
//Retorna COMPARE_SMALLER caso o primeiro valor seja menor que o segundo
//Retorna COMPARE_EQUAL caso ambos sejam iguais
int CompareUtils_TweetByText(Tweet* a, Tweet* b);

#endif _COMPAREUTILSH_