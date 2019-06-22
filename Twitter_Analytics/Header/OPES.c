#include "../Header/OPES.h"

ArgumentsForOp ArgumentsForOp_New() {
	ArgumentsForOp argumentsForOp;
	argumentsForOp.opChar = ' ';
	argumentsForOp.number = 0;
	argumentsForOp.name[0] = '\0'; //Inicializa a string vazia

	return argumentsForOp;
}

OPESResult OPESResult_New() {
	OPESResult opesResult;
	opesResult.associatedHashtags = List_New();
	opesResult.hashtagsMaisCitadas = List_New();
	opesResult.usuarioComMaisTweets = List_New();
	opesResult.tweetsComMaisRetweets = List_New();
	opesResult.usuariosMaisMencionados = List_New();
	opesResult.usuariosMaisInfluentes = List_New();
	opesResult.usuariosMaisEngajados = List_New();

	return opesResult;
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
	opes.opesResult = OPESResult_New();

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

void OPES_A_HashtagMaisCitadas(OPES* opes) {
	int count = ((ArgumentsForOp*)List_Get(opes->opsArguments, 0))->number;
	AvlTreeNode* root = opes->AvlHashtagByTweetCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, opes->opesResult.hashtagsMaisCitadas);
	}
}

void OPES_B_UsuariosComMaisTweets(OPES* opes) {
	int count = ((ArgumentsForOp*)List_Get(opes->opsArguments, 1))->number;
	AvlTreeNode* root = opes->AvlUserByTweetCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, opes->opesResult.usuarioComMaisTweets);
	}
}

void OPES_C_TweetsComMaiorNumeroDeRetweets(OPES * opes) {
	int count = ((ArgumentsForOp*)List_Get(opes->opsArguments, 2))->number;
	AvlTreeNode* root = opes->AvlTweetByRetweetCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, opes->opesResult.tweetsComMaisRetweets);
	}
}

void OPES_D_UsuariosMaisMencionados(OPES * opes) {
	int count = ((ArgumentsForOp*)List_Get(opes->opsArguments, 3))->number;
	AvlTreeNode* root = opes->AvlUserByMentionCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, opes->opesResult.usuariosMaisMencionados);
	}
}

void OPES_E_UsuariosMaisInfluentes(OPES * opes) {
	int count = ((ArgumentsForOp*)List_Get(opes->opsArguments, 4))->number;
	AvlTreeNode* root = opes->AvlUserByRetweetCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, opes->opesResult.usuariosMaisInfluentes);
	}
}

void OPES_F_UsuariosMaisEngajados(OPES * opes) {
	int count = ((ArgumentsForOp*)List_Get(opes->opsArguments, 5))->number;
	AvlTreeNode* root = opes->AvlUserByEngagementCount->root;
	if (root != NULL) {
		if (count == 0) {
			count = pow(2, root->height); //Count como árvore completa
		}
		ConvertTreeToListDesc(root, &count, opes->opesResult.usuariosMaisEngajados);
	}
}

void OPES_G_TermosAssociados(OPES* opes) {
	//Verifica as Hashtags associadas
	ArgumentsForOp* argumentG = ((ArgumentsForOp*)List_Get(opes->opsArguments, 6));

	int countArgG = 0;
	//Retira o # da hashtag 
	do {
		argumentG->name[countArgG] = CharUtils_toLowerCase(argumentG->name[countArgG + 1]);
		countArgG++;
	} while (argumentG->name[countArgG + 1] != '\0');

	argumentG->name[countArgG] = '\0';

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
					for (int z = 0; z < opes->opesResult.associatedHashtags->length; z++) {
						AssociatedHashTag* listedAHashtag = List_Get(opes->opesResult.associatedHashtags, z);
						if (CompareUtils_String(listedAHashtag->name, aHashtag) == COMPARE_EQUAL) {
							//Se ela já estiver na lista incrementa o número de vezes que apareceu e interrompe o laço
							isListed = true;
							List_RemoveByIndex(opes->opesResult.associatedHashtags, z);
							listedAHashtag->count = listedAHashtag->count + 1;
							ListAssociatedHashtag_Add(opes->opesResult.associatedHashtags, listedAHashtag);
							break;
						}
					}

					//Caso não esteja na lista cria um novo e adiciona
					if (!isListed) {
						AssociatedHashTag* newAHashtag = AssociatedHashTag_New();
						strcpy(newAHashtag->name, aHashtag->name);
						newAHashtag->count = 1;
						ListAssociatedHashtag_Add(opes->opesResult.associatedHashtags, newAHashtag);
					}
				}
			}
		}
	}
}
