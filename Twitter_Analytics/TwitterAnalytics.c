#include "./Header/TwitterAnalytics.h"

int main(int argc, char *argv[]) {
	if (File_argumentsError(argc)) return 0;

	FILE *file1, *file2, *OUTPUT;

	//file1 = fopen(argv[1], "r");
	//file2 = fopen(argv[2], "r");
	file1 = fopen("file1.txt", "r");
	file2 = fopen("file2.txt", "r");

	if (File_filesError(file1, file2)) return 0;

	OPES opes = File_readFiles(file1, file2);
	
	for (int x = 0; x < 7; x++) {
		ArgumentsForOp* teste = List_Get(opes.opsArguments, x);
		printf("%c\n", teste->opChar);
		printf("%d\n", teste->number);
		printf("%s\n", teste->name);
	}

    return 0;
}
