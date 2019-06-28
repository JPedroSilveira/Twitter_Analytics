#include "./Header/TwitterAnalytics.h"

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "");

	clock_t tInicio, tFim;
	double tDecorrido;

	tInicio = clock();

	if (File_argumentsError(argc)) return 0;

	FILE *file1, *file2, *output;

	//file1 = fopen(argv[1], "r");
	//file2 = fopen(argv[2], "r");
	//output = fopen(argv[3], "r");
	file1 = fopen("file1.csv", "r");
	file2 = fopen("file2.csv", "r");
	output = fopen("output.csv", "a");

	if (File_filesError(file1, file2, output)) return 0;

	OPES opes = File_readFiles(file1, file2);

	File_executeOpes(&opes);

	File_saveOpes(&opes, output);

	tFim = clock();

	tDecorrido = ((tFim - tInicio) * 1000) / CLOCKS_PER_SEC;

	printf("Tempo decorrido em milissegundos: %lf \n", tDecorrido);

	fclose(file1);
	fclose(file2);
	fclose(output);

	system("pause");

    return 0;
}
