#include "..\Header\CharUtils.h"

const char separator[] = { " ,.&*%\?!;/-'@\"$#=><()][}{:\n\t" };

char CharUtils_removeCharAccent(char l) {
	switch (l) {
		case 'á':
		case 'â':
		case 'à':
		case 'å':
		case 'ã':
		case 'ä':
			return 'a';
		case 'Á':
		case 'Â':
		case 'À':
		case 'Å':
		case 'Ã':
		case 'Ä':
			return 'A';
		case 'é':
		case 'ê':
		case 'è':
		case 'ë':
			return 'e';
		case 'É':
		case 'Ê':
		case 'È':
		case 'Ë':
			return 'E';
		case 'í':
		case 'î':
		case 'ì':
		case 'ï':
			return 'i';
		case 'Í':
		case 'Î':
		case 'Ì':
		case 'Ï':
			return 'I';
		case 'ó':
		case 'ô':
		case 'ò':
		case 'õ':
		case 'ö':
			return 'o';
		case 'Ó':
		case 'Ô':
		case 'Ò':
		case 'Õ':
		case 'Ö':
			return 'O';
		case 'ú':
		case 'û':
		case 'ù':
		case 'ü':
			return 'o';
		case 'Ú':
		case 'Û':
		case 'Ù':
		case 'Ü':
			return 'O';
		case 'ç':
			return 'c';
		case 'Ç':
			return 'C';
		default:
			return l;
	}
}

char CharUtils_toLowerCase(char l) {
	return tolower(l);
}

char CharUtils_removeCharAccentToLowerCase(char l) {
	return CharUtils_toLowerCase(CharUtils_removeCharAccent(l));
}

int isSeparator(char l) {
	int count = 0;
	while (separator[count] != '\0') {
		if (separator[count] == l) {
			return true;
		}
		count++;
	}

	return false;
}
