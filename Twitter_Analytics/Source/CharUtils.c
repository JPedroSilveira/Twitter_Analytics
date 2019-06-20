#include "..\Header\CharUtils.h"

char CharUtils_removeCharAccent(char l) {
	switch (l) {
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
			return 'a';
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
			return 'A';
		case '�':
		case '�':
		case '�':
		case '�':
			return 'e';
		case '�':
		case '�':
		case '�':
		case '�':
			return 'E';
		case '�':
		case '�':
		case '�':
		case '�':
			return 'i';
		case '�':
		case '�':
		case '�':
		case '�':
			return 'I';
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
			return 'o';
		case '�':
		case '�':
		case '�':
		case '�':
		case '�':
			return 'O';
		case '�':
		case '�':
		case '�':
		case '�':
			return 'o';
		case '�':
		case '�':
		case '�':
		case '�':
			return 'O';
		case '�':
			return 'c';
		case '�':
			return 'C';
		default:
			return l;
	}
}

char CharUtils_toLowerCase(char l) {
	return tolower(l);
}
