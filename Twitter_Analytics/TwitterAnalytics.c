#include "./Header/TwitterAnalytics.h"

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "");

	//Cria o contador de tempos
	ClockControl clockControl;

	//Inicia a contagem principal
	ClockUtils_mainStart(&clockControl);

	//Avalia se os argumentos de execução então corretos
	//if (File_argumentsError(argc)) return 0;

	FILE *file1, *file2, *output;

	//Lê os arquivos
	file1 = fopen(argv[1], "r");
	file2 = fopen(argv[2], "r");
	output = fopen(argv[3], "a");

	//Verifica se houve erro nas leituras
	if (File_filesError(file1, file2, output)) return 0;

	//Faz a leitura e avaliação dos dados
	ClockUtils_readStart(&clockControl);
	OPES opes = File_readFiles(file1, file2);
	ClockUtils_readEnd(&clockControl);

	//Executa as operações com base nos dados já ordenados
	ClockUtils_executeOPStart(&clockControl);
	File_executeOpes(&opes);

	File_saveOpes(&opes, output);
	ClockUtils_executeOPEnd(&clockControl);

	ClockUtils_mainEnd(&clockControl);

	printf("Tempo decorrido em milissegundos: %lf \n", ClockUtils_mainDiff(clockControl));

	File_saveClocks(clockControl, output);

	fclose(file1);
	fclose(file2);
	fclose(output);

    return 0;
}
