#include "../Header/StringUtils.h"

void StringUtils_removeStringAccents(char* string) {
	int count = 0;

	while (string != NULL && string[count] != '\0') {
		switch (string[count])
		{
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'a';
			break;
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'A';
			break;
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'e';
			break;
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'E';
			break;
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'i';
			break;
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'I';
			break;
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'o';
			break;
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'O';
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'o';
			break;
		case '�':
		case '�':
		case '�':
		case '�':
			string[count] = 'O';
		case '�':
			string[count] = 'c';
		case '�':
			string[count] = 'C';
		default:
			break;
		}
		count = count + 1;
	}
}

void StringUtils_toLowerCase(char* string) {
	int count = 0;

	while(string != NULL && string[count] != '\0') {
		string[count] = tolower(string[count]);
		count++;
	}
}

void StringUtils_removeAccentsTest() {
	char* string = (char*)malloc((strlen("� � � � � � � �") + 1) * sizeof(char));
	strcpy(string, "� � � � � � � �");
	StringUtils_removeStringAccents(string);
	printf("%s", string);
}

void StringUtils_toLowerCaseTest() {
	char* string = (char*)malloc((strlen("AaBbCcZz") + 1) * sizeof(char));
	strcpy(string, "AaBbCcZz");
	StringUtils_toLowerCase(string);
	printf("%s", string);
}
