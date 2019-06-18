#include "../Header/StringUtils.h"

void StringUtils_removeStringAccents(char* string) {
	int count = 0;

	while (string != NULL && string[count] != '\0') {
		switch (string[count])
		{
		case 'á':
		case 'â':
		case 'à':
		case 'å':
		case 'ã':
		case 'ä':
			string[count] = 'a';
			break;
		case 'Á':
		case 'Â':
		case 'À':
		case 'Å':
		case 'Ã':
		case 'Ä':
			string[count] = 'A';
			break;
		case 'é':
		case 'ê':
		case 'è':
		case 'ë':
			string[count] = 'e';
			break;
		case 'É':
		case 'Ê':
		case 'È':
		case 'Ë':
			string[count] = 'E';
			break;
		case 'í':
		case 'î':
		case 'ì':
		case 'ï':
			string[count] = 'i';
			break;
		case 'Í':
		case 'Î':
		case 'Ì':
		case 'Ï':
			string[count] = 'I';
			break;
		case 'ó':
		case 'ô':
		case 'ò':
		case 'õ':
		case 'ö':
			string[count] = 'o';
			break;
		case 'Ó':
		case 'Ô':
		case 'Ò':
		case 'Õ':
		case 'Ö':
			string[count] = 'O';
		case 'ú':
		case 'û':
		case 'ù':
		case 'ü':
			string[count] = 'o';
			break;
		case 'Ú':
		case 'Û':
		case 'Ù':
		case 'Ü':
			string[count] = 'O';
		case 'ç':
			string[count] = 'c';
		case 'Ç':
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
	char* string = (char*)malloc((strlen("á Á ê Ê î í õ Õ") + 1) * sizeof(char));
	strcpy(string, "á Á ê Ê î í õ Õ");
	StringUtils_removeStringAccents(string);
	printf("%s", string);
}

void StringUtils_toLowerCaseTest() {
	char* string = (char*)malloc((strlen("AaBbCcZz") + 1) * sizeof(char));
	strcpy(string, "AaBbCcZz");
	StringUtils_toLowerCase(string);
	printf("%s", string);
}
