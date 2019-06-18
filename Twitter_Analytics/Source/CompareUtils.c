#include "../Header/CompareUtils.h"

int CompareUtils_maxInt(int a, int b) {
	return (a > b) ? a : b;
}

int CompareUtils_Int(void* a, void* b) {
	int A = *((int*)a);
	int B = *((int*)b);

	if (A > B) {
		return 1;
	}
	else if (A == B) {
		return 0;
	}
	else {
		return -1;
	}
}

int CompareUtils_Char(void* a, void* b) {
	char A = *((char*)a);
	char B = *((char*)b);

	if (A > B) {
		return 1;
	}
	else if (A == B) {
		return 0;
	}
	else {
		return -1;
	}
}

int CompareUtils_String(void* a, void* b) {
	char* A = (char*)a;
	char* B = (char*)b;
	int cmp = strcmp(A, B);
	if (cmp > 0) { //caso a > b
		return 1;
	}
	else if (cmp < 0) { //caso a < b
		return -1;
	}
	else { //caso a == b
		return cmp;
	}
}
