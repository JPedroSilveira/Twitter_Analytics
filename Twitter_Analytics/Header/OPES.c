#include "../Header/OPES.h"

ArgumentsForOp ArgumentsForOp_New() {
	ArgumentsForOp argumentsForOp;
	argumentsForOp.opChar = ' ';
	argumentsForOp.number = 0;
	argumentsForOp.name[0] = '\0'; //Inicializa a string vazia

	return argumentsForOp;
}

OPES OPES_New() {
	OPES opes;
	opes.AvlUsuarioByName = AVL_newTreeUserByName();
	opes.AvlHashtagByTweetCount = AVL_newTreeHashtagByTweetCount();
	opes.AvlTweetByRetweetCount = AVL_newTreeTweetByRetweetCount();

	return opes;
}
