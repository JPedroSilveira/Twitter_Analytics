#include "../Header/File.h"

int argumentsError(int argc) {
	if (argc > 3) {
		printf("Mais de dois parametros\n");
		return 1;
	}
	else return 0;
}

int filesError(FILE *input1, FILE *input2) {
	if (!input1 || !input2) { // Caso ocorra erro na abertura de um dos arquivos
		printf("Parametros invalidos\n");
		return 1;
	}
	else return 0;
}

ArgumentsForOp ArgumentsForOp_New() {
	ArgumentsForOp argumentsForOp;
	argumentsForOp.opChar = ' ';
	argumentsForOp.number = 0;
	argumentsForOp.name[0] = '\0'; //Inicializa a string vazia

	return argumentsForOp;
}

List* readArgumentsForOp(FILE *file) {
	List* argumentsList = List_New();

	char command, letter;
	int count, number;

	while ((command = getc(file)) != EOF) {
		ArgumentsForOp* arguments = (ArgumentsForOp*)malloc(sizeof(ArgumentsForOp));
		*arguments = ArgumentsForOp_New();

		arguments->opChar = command; // char comando
		getc(file); // pula o ;

		if (arguments->opChar == 'g') { // Caso especial = operação G recebe uma hashtag (string)
			arguments->number = 0;
			count = 0;
			letter = getc(file);

			while (letter == ' ') { //Elimina espaço em branco
				letter = getc(file);
			}

			while (letter != '\n' && letter != ' ') { //Lê até achar o final
				arguments->name[count] = letter;
				letter = getc(file);
				count++;
			}

			//Finaliza a string
			arguments->name[count] = '\0';
		}
		else {
			strcpy(arguments->name, "");
			arguments->number = readInt(file);
		}

		argumentsList->Add(argumentsList, arguments);
	}

	return argumentsList;
}

int readInt(FILE *file) {
	int count = 0;
	return readIntAux(file, &count);
}

int readIntAux(FILE *file, int *count) {
	char character = getc(file);
	int number;
	if (character != '\n' && character != ' ') { //Lê até achar o final
		number = readIntAux(file, count); //Chama recursivamente até o último caracter
		number += ((character - 48) * pow(10, *count)); //Converte char ASCII para int e eleva para sua casa decimal somando ao valor total
		*count = *count + 1; //Soma o contador para cada nova casa decimal
		return number; //Retorna o número parcial
	}
	else {
		return 0;
	}
}

void readTweets(FILE * file)
{
	char readChar;
	int countChar, countHashtagChar = -1, countMentionChar = -1, number = 0;
	while ((readChar = getc(file)) != EOF) {
		Tweet* tweet = TweetP_New();
		User* user;
		Hashtag* hashtag;
		User* userMention;
		char userName[USER_NAME_LENGTH];
		char hashtagName[HASHTAG_NAME_LENGTH];
		char mentionUserName[USER_NAME_LENGTH];

		//Lendo nome do usuario
		countChar = 0;
		userName[countChar] = readChar;

		while ((readChar = getc(file)) != ';') {
			countChar++;
			userName[countChar] = readChar;
		}

		userName[countChar + 1] = '\0';

		//TO-DO: Procura nome do usuario na arvore. Se nao encontrar cria novo e adiciona, caso contrario atualiza ele
		user = UserP_New();
		user->info.tweetCount = 1;
		strcpy(user->name, userName);
		user->tweetList->Add(user->tweetList, tweet);
		//TO-DO: Adicionar o novo usuario a arvore

		//Lendo texto do tweet
		countChar = 0;
		int continue_ = 1;
		do {
			readChar = getc(file);
			if (readChar == '#' || countHashtagChar != -1) { //Le Hashtag
				if (readChar == '#') { //Inicia leitura do nome da hashtag
					countHashtagChar++;
				}
				else if (readChar == ' ' || readChar != ';') { //Finaliza hashtag
					hashtagName[countHashtagChar] = '\0';
					//TO-DO: Procura hashtag na arvore. Se nao existir cria nova e adiciona na arvore, se existir apenas adiciona este Tweet a ela
					hashtag = HashtagP_New();
					strcpy(hashtag->name, hashtagName);
					hashtag->tweetCount = 1;
					hashtag->tweetList->Add(hashtag->tweetList, tweet);
					//TO-DO: Adicionar na arvore
					//Adiciona a Hashtag a lista de hashtags do Tweet
					tweet->hashtagList->Add(tweet->hashtagList, hashtag);
					countHashtagChar = -1;
				}
				else { //Segue lendo o nome da hashtag
					hashtagName[countHashtagChar] = readChar;
					countHashtagChar++;
				}
			}
			else if (readChar == '@' || countMentionChar != -1) { //Le mencao
				if (readChar == '@') { //Inicializa leitura do nome do usuario mencionado
					countMentionChar++;
				}
				else if (readChar != ' ' || readChar !=  ';') { //Finaliza leitura
					mentionUserName[countMentionChar] = '\0';
					//TO-DO: Procura usuario na arvore. Se nao existir cria novo e adiciona na arvore, se existir adiciona este tweet a lista de mencoes
					userMention = UserP_New();
					strcpy(userMention->name, mentionUserName);
					userMention->mentionTweetList->Add(userMention->mentionTweetList, tweet);
					userMention->info.mentionCount = 1;
					//TO-DO: Adicionar na arvore
					//Adiciona o usuario ao que o Tweet menciona
					tweet->mentionList->Add(tweet->mentionList, userMention);
					countMentionChar = -1;
				}
				else { //Segue lendo o nome do usuario mencionado
					mentionUserName[countMentionChar] = readChar;
					countMentionChar++;
				}
			}

			tweet->text[countChar] = readChar;
			readChar++;
		} while (readChar != ';');

		//Ler numero de re-tweets
		countChar = 0;

		while ((readChar = getc(file)) != ';') {
			number = number + (readChar * pow(BASE, countChar));
			countChar++;
		}

		tweet->reTweetCount = number;

		//Ler numero de likes
		countChar = 0;

		while ((readChar = getc(file)) != ';') {
			number = number + (readChar * pow(BASE, countChar));
			countChar++;
		}

		tweet->likeCount = number;

		//TO-DO: Adicionar Tweet na sua arvore
	}
//	return NULL; Funcao void
}

void exFile2(FILE *input2) {
	/*
	ArgumentsForOp arguments;
	char op;
	int qtt;
	char s;

	while ((s = getc(input2)) != EOF) { // Até o final do arquivo
		arguments = readLine(input2);

		switch (arguments.opChar) {
			case 'a':

				break;

			case 'b':

				break;

			case 'c':

				break;

			case 'd':

				break;

			case 'e':

				break;

			case 'f':

				break;

			case 'g':

				break;
		}
	}
	*/
}


