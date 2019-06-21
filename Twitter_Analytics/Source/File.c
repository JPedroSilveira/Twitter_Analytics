#include "../Header/File.h"
#include "../Header/CharUtils.h"

int File_argumentsError(int argc) {
	if (argc > 3) {
		printf("Mais de dois parametros\n");
		return 1;
	}
	else return 0;
}

int File_filesError(FILE *input1, FILE *input2) {
	if (!input1 || !input2) { // Caso ocorra erro na abertura de um dos arquivos
		printf("Parametros invalidos\n");
		return 1;
	}
	else return 0;
}

OPES File_readFiles(FILE* fileTweets, FILE* fileOps) {
	OPES opes = File_readTweets(fileTweets);
	opes.opsArguments = File_readArgumentsForOp(fileOps);

	return opes;
}

List* File_readArgumentsForOp(FILE *file) {
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
	if (character != '\n' && character != ' ' && character != ';' && character != EOF) { //Lê até achar o final
		number = File_readIntAux(file, count); //Chama recursivamente até o último caracter
		number += ((character - 48) * pow(10, *count)); //Converte char ASCII para int e eleva para sua casa decimal somando ao valor total
		*count = *count + 1; //Soma o contador para cada nova casa decimal
		return number; //Retorna o número parcial
	}
	else {
		return 0;
	}
}

OPES File_readTweets(FILE * file) {
	char readChar;
	int countChar, countHashtagChar = -1, countMentionChar = -1, number = 0;
	OPES opes = OPES_New();

	while ((readChar = getc(file)) != EOF) {
		Tweet* tweet = TweetP_New();
		User* user;
		Hashtag* hashtag;
		User* userMention;

		//Lendo nome do usuario
		countChar = 0;
		readChar = getc(file); //Pula a @ inicial do nome
		user = UserP_New(); //Inicia um novo usuário

		user->name[countChar] = CharUtils_toLowerCase(readChar);

		while ((readChar = getc(file)) != ';') { //Lê todo o nome do usuário
			countChar++;
			user->name[countChar] = CharUtils_toLowerCase(readChar);
		}

		user->name[countChar + 1] = '\0'; //Finaliza a leitura do nome do usuario

		//Adiciona o novo usuário na árvore caso ainda não exista ou retorna o existente
		user = (User*)AVL_insert(opes.AvlUsuarioByName, NULL, user)->key;
		
		//Lendo texto do tweet
		countChar = 0;
		do {
			readChar = getc(file);
			if (readChar == '#' || countHashtagChar != -1) { //Lê Hashtag
				if (readChar == '#') { //Inicia leitura do nome da hashtag
					hashtag = HashtagP_New(); //Inicializa uma nova hashtag
					countHashtagChar = 0; //Zera o contador
				} else if (readChar == ' ' || readChar == ';') { //Finaliza a leitura da hashtag
					hashtag->name[countHashtagChar] = '\0';

					//Adiciona a nova hashtag na árvore caso ainda não exista ou retorna a existente
					hashtag = (Hashtag*) AVL_insert(opes.AvlHashtagByTweetCount, NULL, hashtag)->key;

					//Incrementa o número de tweets relacionados a ela e adiciona o tweet na sua lista
					hashtag->tweetCount = hashtag->tweetCount + 1;
					List_Add(hashtag->tweetList, tweet);

					//Adiciona a Hashtag a lista de hashtags do Tweet
					List_Add(tweet->hashtagList, hashtag);
					countHashtagChar = -1; //Finaliza o contador de leitura da hashtag
				} else { //Segue lendo o nome da hashtag
					hashtag->name[countHashtagChar] = CharUtils_toLowerCase(readChar);
					countHashtagChar++;
				}
			} else if (readChar == '@' || countMentionChar != -1) { //Lê menção
				if (readChar == '@') { //Inicializa leitura do nome do usuário mencionado
					userMention = UserP_New(); //Inicializa novo usuário mencionado
					countMentionChar = 0; //Zera o contador para sua string nome
				} else if (readChar == ' ' || readChar ==  ';') { //Finaliza leitura
					userMention->name[countMentionChar] = '\0';

					//Adiciona o possível novo usuário na árvore caso ainda não exista ou retorna o existente
					userMention = (User*)AVL_insert(opes.AvlUsuarioByName, NULL, userMention)->key;

					//Adiciona a mencao na estrutura do usuário
					List_Add(userMention->mentionTweetList, tweet);
					userMention->info.mentionCount = userMention->info.mentionCount + 1; //Incrementa a contagem de menções

					//Adiciona o usuario ao que o Tweet menciona
					List_Add(tweet->mentionList, userMention);

					countMentionChar = -1; //Finaliza o contador de leitura da menção
				} else { //Segue lendo o nome do usuario mencionado
					userMention->name[countMentionChar] = CharUtils_toLowerCase(readChar);
					countMentionChar++;
				}
			}

			if (readChar != ';') {
				tweet->text[countChar] = CharUtils_removeCharAccent(readChar);
				countChar++;
			}
			else {
				tweet->text[countChar] = '\0'; //Finaliza a leitura do texto do Tweet
			}
		} while (readChar != ';');

		//Le o numero de re-tweets
		tweet->reTweetCount = File_readInt(file);

		//Le o numero de likes
		tweet->likeCount = File_readInt(file);

		//Adiciona o Tweet a lista de tweets do usuario
		User_AddTweet(user, tweet);

		//Adiciona o Tweet na sua árvore
		AVL_insert(opes.AvlTweetByRetweetCount, NULL, tweet);
	}
	
	return opes;
}

void File_exFile2(FILE *input2) {
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


