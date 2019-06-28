#ifndef _OPESH_
#define _OPESH_

#include "./AVL.h"
#include "./List.h"
#include "./CharUtils.h"
#include <math.h>

#define OP_NAME_MAX_CHAR_LENGTH 50

typedef struct s_ArgumentsForOp {
	char opChar;
	int number;
	char name[OP_NAME_MAX_CHAR_LENGTH];
	List* result;
} ArgumentsForOp;

ArgumentsForOp ArgumentsForOp_New();

typedef struct s_OPES {
	List* opsArguments; //Lista de ArgumentsForOp
	AvlTree* AvlUserByName;
	AvlTree* AvlUserByTweetCount;
	AvlTree* AvlUserByMentionCount;
	AvlTree* AvlUserByRetweetCount;
	AvlTree* AvlUserByEngagementCount;
	AvlTree* AvlHashtagByTweetCount;
	AvlTree* AvlHashtagByName;
	AvlTree* AvlTweetByRetweetCount;
} OPES;

OPES OPES_New();

//Dado o nodo raiz de uma árvore binária de pesquisa converte para uma lista decrescente
void ConvertTreeToListDesc(AvlTreeNode* mother, int* count, List* result);

// Listar as hastags mais citadas em toda rede.
void OPES_A_HashtagMaisCitadas(OPES* opes, ArgumentsForOp* argument);

// Listar os usuários que mais postam tweets.
void OPES_B_UsuariosComMaisTweets(OPES* opes, ArgumentsForOp* argument);

// Listar os tweets com maior número de retweets.
void OPES_C_TweetsComMaiorNumeroDeRetweets(OPES* opes, ArgumentsForOp* argument);

// Listar os usuários mais mencionados nos tweets.
void OPES_D_UsuariosMaisMencionados(OPES* opes, ArgumentsForOp* argument);

// Listar os usuários mais influentes (aquele que possui o maior número de retweets.)
void OPES_E_UsuariosMaisInfluentes(OPES* opes, ArgumentsForOp* argument);

// Listar os usuários mais engajados da rede. Engajamento é a interação do público com as postagens do usuário e determina o alcance das postagens. O engajamento é contabilizado pela somatório da quantidade de interações dos tweets de um usuário, que inclui: gostar do tweet (like), quantidade de retweets e quantidade de menções ao usuário.
void OPES_F_UsuariosMaisEngajados(OPES* opes, ArgumentsForOp* argument);
							
//Lista os termos associados a uma hashtag dada
void OPES_G_TermosAssociados(OPES* opes, ArgumentsForOp* argument);


#endif _OPESH_