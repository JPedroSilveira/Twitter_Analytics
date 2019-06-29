#include "../Header/File.h"

int File_argumentsError(int argc) {
	if (argc != 3) {
		printf("Diferente de três parametros\n");
		return 1;
	}
	else return 0;
}

int File_filesError(FILE *input1, FILE *input2, FILE *output) {
	if (!input1 || !input2 || !output) { // Caso ocorra erro na abertura de um dos arquivos
		printf("Parametros invalidos\n");
		return 1;
	}
	else return 0;
}

OPES File_readFiles(FILE* fileTweets, FILE* fileOps) {
	OPES opes = OPES_New();
	opes.opsArguments = File_readArgumentsForOp(fileOps);
	opes = File_readTweets(opes, fileTweets);

	return opes;
}

List* File_readArgumentsForOp(FILE *file) {
	List* argumentsList = List_New();

	char command, char_;
	int count;

	while ((command = getc(file)) != EOF) {
		ArgumentsForOp* arguments = (ArgumentsForOp*)malloc(sizeof(ArgumentsForOp));
		*arguments = ArgumentsForOp_New();

		arguments->opChar = CharUtils_removeCharAccentToLowerCase(command); // char comando
		getc(file); // pula o ;

		if (arguments->opChar == 'g') { // Caso especial = operação G recebe uma hashtag (string)
			arguments->number = 0;
			count = 0;
			char_ = getc(file);

			while (char_ == ' ' || char_ == '#') { //Elimina espaço em branco e a hashtag
				char_ = getc(file);
			}

			while (!isSeparator(char_) && char_ != EOF) { //Lê até achar o final
				arguments->name[count] = CharUtils_removeCharAccentToLowerCase(char_);
				char_ = getc(file);
				count++;
			}

			//Finaliza a string
			arguments->name[count] = '\0';
		}
		else {
			strcpy(arguments->name, "");
			arguments->number = File_readInt(file);
		}

		List_Add(argumentsList, arguments);
	}

	return argumentsList;
}

int File_readInt(FILE *file) {
	int count = 0;
	return File_readIntAux(file, &count);
}

int File_readIntAux(FILE *file, int *count) {
	char character = getc(file);
	int number;
	if (!isSeparator(character) && character != EOF) { //Lê até achar o final
		number = File_readIntAux(file, count); //Chama recursivamente até o último caracter
		number += ((character - 48) * pow(10, *count)); //Converte char ASCII para int e eleva para sua casa decimal somando ao valor total
		*count = *count + 1; //Soma o contador para cada nova casa decimal
		return number; //Retorna o número parcial
	}
	else {
		return 0;
	}
}

OPES File_readTweets(OPES opes, FILE * file) {
	char readChar;
	int countChar, countHashtagChar = -1, countMentionChar = -1, number = 0, isAssociated = 0;

	while ((readChar = getc(file)) != EOF) {
		Tweet* tweet = TweetP_New();
		User* user;
		Hashtag* hashtag;
		User* userMention;

		//Lendo nome do usuario
		countChar = 0;
		readChar = getc(file); //Pula a @ inicial do nome
		user = UserP_New(); //Inicia um novo usuário

		user->name[countChar] = CharUtils_removeCharAccentToLowerCase(readChar);

		while ((readChar = getc(file)) != ';') { //Lê todo o nome do usuário
			countChar++;
			user->name[countChar] = CharUtils_removeCharAccentToLowerCase(readChar);
		}

		user->name[countChar + 1] = '\0'; //Finaliza a leitura do nome do usuario

		//Adiciona o novo usuário na árvore caso ainda não exista ou retorna o existente
		AvlTreeNode* userNode = AVL_insert(opes.AvlUserByName, NULL, user);
		
		if (!AVL_nodeIsEmpty(userNode)) {
			user = userNode->key;

			//Remove o user da árvore por contagem de tweets
			AVL_remove(opes.AvlUserByTweetCount, userNode);

			//Remove o user da árvore por contagem de retweets
			AVL_remove(opes.AvlUserByRetweetCount, userNode);

			//Remove o user da árvore para contagem de engajamento
			AVL_remove(opes.AvlUserByEngagementCount, userNode);
		}

		//Lendo texto do tweet
		countChar = 0;
		do {
			readChar = getc(file);
			if (readChar == '#' || countHashtagChar != -1) { //Lê Hashtag
				if (readChar == '#') { //Inicia leitura do nome da hashtag
					hashtag = HashtagP_New(); //Inicializa uma nova hashtag
					countHashtagChar = 0; //Zera o contador
				} else if (isSeparator(readChar)) { //Finaliza a leitura da hashtag
					hashtag->name[countHashtagChar] = '\0';

					//Busca a hashtag pelo nome
					AvlTreeNode* hashtagNode = AVL_get(opes.AvlHashtagByName, hashtag);

					if (!AVL_nodeIsEmpty(hashtagNode)) {
						hashtag = hashtagNode->key;

						//Remove a hashtag
						AVL_remove(opes.AvlHashtagByTweetCount, hashtagNode);
					} else {
						//Se não estiver na árvore ordenada por nome então é nova
						//Adiciona na árvore
						AVL_insert(opes.AvlHashtagByName, NULL, hashtag);
					}

					//Adiciona o tweet na sua lista
					List_Add(hashtag->tweetList, tweet);

					//Adiciona a Hashtag a lista de hashtags do Tweet
					List_Add(tweet->hashtagList, hashtag);

					//Adiciona a nova hashtag na árvore
					AVL_insert(opes.AvlHashtagByTweetCount, NULL, hashtag);
					
					countHashtagChar = -1; //Finaliza o contador de leitura da hashtag
				} else { //Segue lendo o nome da hashtag
					hashtag->name[countHashtagChar] = CharUtils_removeCharAccentToLowerCase(readChar);
					countHashtagChar++;
				}
			} else if (readChar == '@' || countMentionChar != -1) { //Lê menção
				if (readChar == '@') { //Inicializa leitura do nome do usuário mencionado
					userMention = UserP_New(); //Inicializa novo usuário mencionado
					countMentionChar = 0; //Zera o contador para sua string nome
				} else if (isSeparator(readChar)) { //Finaliza leitura
					userMention->name[countMentionChar] = '\0';

					//Busca o usuário pelo nome
					AvlTreeNode* userMentionNode = AVL_get(opes.AvlUserByName, userMention);

					if (!AVL_nodeIsEmpty(userMentionNode)) { //Já está inserido em ambas as árvores de usuário
						userMention = userMentionNode->key;

						//Remove o usuário para re-inserir ordenado
						AVL_remove(opes.AvlUserByMentionCount, userMentionNode);
						AVL_remove(opes.AvlUserByEngagementCount, userMentionNode);
					} else {
						//Se não estiver na árvore ordenada por nome então é nova
						//Adiciona na árvore
						AVL_insert(opes.AvlUserByName, NULL, userMention);
					}

					//Adiciona a mencao na estrutura do usuário
					List_Add(userMention->mentionTweetList, tweet);

					//Adiciona o usuario ao que o Tweet menciona
					List_Add(tweet->mentionList, userMention);

					//Incrementa o engamento do usuário ao ser mencionado
					userMention->info.engagementCount = userMention->info.engagementCount + 1;

					//Adiciona o possível novo usuário na árvore caso ainda não exista ou retorna o existente
					AVL_insert(opes.AvlUserByMentionCount, NULL, userMention);
					AVL_insert(opes.AvlUserByEngagementCount, NULL, userMention);

					countMentionChar = -1; //Finaliza o contador de leitura da menção
				} else { //Segue lendo o nome do usuario mencionado
					userMention->name[countMentionChar] = CharUtils_removeCharAccentToLowerCase(readChar);
					countMentionChar++;
				}
			}

			if (readChar != ';') {
				tweet->text[countChar] = CharUtils_removeCharAccentToLowerCase(readChar);
				countChar++;
			} else {
				tweet->text[countChar] = '\0'; //Finaliza a leitura do texto do Tweet
			}
		} while (readChar != ';');

		//Le o numero de re-tweets
		tweet->reTweetCount = File_readInt(file);

		//Le o numero de likes
		tweet->likeCount = File_readInt(file);

		//Adiciona o usuário ao Tweet
		tweet->creator = user;

		//Adiciona o Tweet a lista de tweets do usuario
		User_AddTweet(user, tweet);

		//Adiciona o usuário na árvore por contagem de Tweets
		AVL_insert(opes.AvlUserByTweetCount, NULL, user);

		//Adiciona o usuário na árvore por contagem de Retweets
		AVL_insert(opes.AvlUserByRetweetCount, NULL, user);

		//Adiciona o usuário na árvore por contagem de engajamento
		AVL_insert(opes.AvlUserByEngagementCount, NULL, user);

		//Adiciona o Tweet na sua árvore
		AVL_insert(opes.AvlTweetByRetweetCount, NULL, tweet);
	}
	
	return opes;
}

void File_executeOpes(OPES* opes) {
	for (int x = 0; x < opes->opsArguments->length; x++) {
		ArgumentsForOp* op = List_Get(opes->opsArguments, x);
		switch (op->opChar) {
		case 'a':
			OPES_A_HashtagMaisCitadas(opes, op);
			break;
		case 'b':
			OPES_B_UsuariosComMaisTweets(opes, op);
			break;
		case 'c':
			OPES_C_TweetsComMaiorNumeroDeRetweets(opes, op);
			break;
		case 'd':
			OPES_D_UsuariosMaisMencionados(opes, op);
			break;
		case 'e':
			OPES_E_UsuariosMaisInfluentes(opes, op);
			break;
		case 'f':
			OPES_F_UsuariosMaisEngajados(opes, op);
			break;
		case 'g':
			OPES_G_TermosAssociados(opes, op);
			break;
		default:
			break;
		}
	}
}

void File_saveOpes(OPES* opes, FILE* output) {
	for (int x = 0; x < opes->opsArguments->length; x++) {
		ArgumentsForOp* op = List_Get(opes->opsArguments, x);
		File_printOpData(op->opChar, output, op);
	}
}

void File_saveClocks(ClockControl cc, FILE* output) {
	fprintf(output, "Tempo para a abertura e leitura dos arquivos de entrada em milissegundos: %lfms\n", ClockUtils_readDiff(cc));
	fprintf(output, "Tempo para a execução das operaçõe em milissegundos: %lfms\n", ClockUtils_executeOPDiff(cc));
	fprintf(output, "Tempo total para a execução da aplicação: %lfms\n", ClockUtils_mainDiff(cc));
}

void File_printOpData(char opChar, FILE* output, ArgumentsForOp* op) {
	switch (opChar) {
		case 'a':
			fprintf(output, " --- OP A \n");
			File_printOpA(output, op);
			break;
		case 'b':
			fprintf(output, " --- OP B \n");
			File_printOpB(output, op);
			break;
		case 'c':
			fprintf(output, " --- OP C \n");
			File_printOpC(output, op);
			break;
		case 'd':
			fprintf(output, " --- OP D \n");
			File_printOpD(output, op);
			break;
		case 'e':
			fprintf(output, " --- OP E \n");
			File_printOpE(output, op);
			break;
		case 'f':
			fprintf(output, " --- OP F \n");
			File_printOpF(output, op);
			break;
		case 'g':
			fprintf(output, " --- OP G \n");
			File_printOpG(output, op);
			break;
		default:
			break;
	}
}

void File_printOpA(FILE* output, ArgumentsForOp* op) {
	for (int x = 0; x < op->result->length; x++) {
		Hashtag* hashtag = List_Get(op->result, x);
		fprintf(output, "#%s, %d\n", hashtag->name, hashtag->tweetList->length);
	}
}

void File_printOpB(FILE* output, ArgumentsForOp* op) {
	for (int x = 0; x < op->result->length; x++) {
		User* user = List_Get(op->result, x);
		fprintf(output, "@%s, %d\n", user->name, user->tweetList->length);
	}
}

void File_printOpC(FILE* output, ArgumentsForOp* op) {
	for (int x = 0; x < op->result->length; x++) {
		Tweet* tweet = List_Get(op->result, x);
		fprintf(output, "%s, %d\n", tweet->text, tweet->reTweetCount);
	}
}

void File_printOpD(FILE* output, ArgumentsForOp* op) {
	for (int x = 0; x < op->result->length; x++) {
		User* user = List_Get(op->result, x);
		fprintf(output, "@%s, %d\n", user->name, user->mentionTweetList->length);
	}
}

void File_printOpE(FILE* output, ArgumentsForOp* op) {
	for (int x = 0; x < op->result->length; x++) {
		User* user = List_Get(op->result, x);
		fprintf(output, "@%s, %d\n", user->name, user->info.retweetCount);
	}
}

void File_printOpF(FILE* output, ArgumentsForOp* op) {
	for (int x = 0; x < op->result->length; x++) {
		User* user = List_Get(op->result, x);
		fprintf(output, "@%s, %d\n", user->name, user->info.engagementCount);
	}
}

void File_printOpG(FILE* output, ArgumentsForOp* op) {
	for (int x = 0; x < op->result->length; x++) {
		AssociatedHashtag* aHashtag = List_Get(op->result, x);
		fprintf(output, "#%s, %d\n", aHashtag->name, aHashtag->count);
	}
}


