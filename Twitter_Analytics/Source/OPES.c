#include "../Header/OPES.h"

ArgumentsForOp ArgumentsForOp_New() {
	ArgumentsForOp argumentsForOp;
	argumentsForOp.opChar = ' ';
	argumentsForOp.number = 0;
	argumentsForOp.name[0] = '\0'; //Inicializa a string vazia
	argumentsForOp.result = List_New();

	return argumentsForOp;
}

OPES OPES_New() {
	OPES opes;
	opes.AvlUserByName = AVL_newTreeUserByName();
	opes.AvlUserByTweetCount = AVL_newTreeUserByTweetCount();
	opes.AvlUserByMentionCount = AVL_newTreeUserByMentionCount();
	opes.AvlUserByRetweetCount = AVL_newTreeUserByRetweetCount();
	opes.AvlUserByEngagementCount = Avl_newTreeUserByEngagementCount();
	opes.AvlHashtagByTweetCount = AVL_newTreeHashtagByTweetCount();
	opes.AvlHashtagByName = AVL_newTreeHashtagByName();
	opes.AvlTweetByRetweetCount = AVL_newTreeTweetByRetweetCount();

	return opes;
}

void ConvertTreeToListDesc(AvlTreeNode* mother, int* count, List* result) {
	if (*count > 0 && !AVL_nodeIsEmpty(mother)) {
		ConvertTreeToListDesc(mother->right, count, result);
		if (*count > 0) {
			List_Add(result, mother->key);
			*count = *count - 1;
			ConvertTreeToListDesc(mother->left, count, result);
		}
	}
}

void OPES_A_HashtagMaisCitadas(OPES* opes, ArgumentsForOp* argument) {
	int count = argument->number;
	AvlTreeNode* root = opes->AvlHashtagByTweetCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, argument->result);
	}
}

void OPES_B_UsuariosComMaisTweets(OPES* opes, ArgumentsForOp* argument) {
	int count = argument->number;
	AvlTreeNode* root = opes->AvlUserByTweetCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, argument->result);
	}
}

void OPES_C_TweetsComMaiorNumeroDeRetweets(OPES * opes, ArgumentsForOp* argument) {
	int count = argument->number;
	AvlTreeNode* root = opes->AvlTweetByRetweetCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, argument->result);
	}
}

void OPES_D_UsuariosMaisMencionados(OPES * opes, ArgumentsForOp* argument) {
	int count = argument->number;
	AvlTreeNode* root = opes->AvlUserByMentionCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, argument->result);
	}
}

void OPES_E_UsuariosMaisInfluentes(OPES * opes, ArgumentsForOp* argument) {
	int count = argument->number;
	AvlTreeNode* root = opes->AvlUserByRetweetCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, argument->result);
	}
}

void OPES_F_UsuariosMaisEngajados(OPES * opes, ArgumentsForOp* argument) {
	int count = argument->number;
	AvlTreeNode* root = opes->AvlUserByEngagementCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, argument->result);
	}
}

void OPES_G_TermosAssociados(OPES* opes, ArgumentsForOp* argumentG) {
	AvlTreeNode* gHashtagNode = AVL_get(opes->AvlHashtagByName, argumentG->name);

	if (!AVL_nodeIsEmpty(gHashtagNode)) {
		Hashtag* gHashtag = gHashtagNode->key;

		//Busca as hashtags em cada tweet que menciou a hashtag desejada
		for (int x = 0; x < gHashtag->tweetList->length; x++) {
			Tweet* aTweet = List_Get(gHashtag->tweetList, x);
			//Para cada Tweet com a hashtag verifica suas outras hashtags
			for (int y = 0; y < aTweet->hashtagList->length; y++) {
				Hashtag* aHashtag = List_Get(aTweet->hashtagList, y);
				//Se a hashtag do Tweet não for a buscada
				if (CompareUtils_String(aHashtag->name, gHashtag->name) != COMPARE_EQUAL) {
					int isListed = false;
					//Verificase ela já não está na lista
					for (int z = 0; z < argumentG->result->length; z++) {
						AssociatedHashtag* listedAHashtag = List_Get(argumentG->result, z);
						if (CompareUtils_String(listedAHashtag->name, aHashtag->name) == COMPARE_EQUAL) {
							//Se ela já estiver na lista incrementa o número de vezes que apareceu e interrompe o laço
							isListed = true;
							List_RemoveByIndex(argumentG->result, z);
							listedAHashtag->count = listedAHashtag->count + 1;
							ListAssociatedHashtag_Add(argumentG->result, listedAHashtag);
							break;
						}
					}

					//Caso não esteja na lista cria um novo e adiciona
					if (!isListed) {
						AssociatedHashtag* newAHashtag = AssociatedHashtag_New();
						strcpy(newAHashtag->name, aHashtag->name);
						newAHashtag->count = 1;
						ListAssociatedHashtag_Add(argumentG->result, newAHashtag);
					}
				}
			}
		}
	}
}
