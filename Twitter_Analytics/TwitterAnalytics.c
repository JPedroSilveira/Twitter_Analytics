#include "./Header/TwitterAnalytics.h"

int main(int argc, char *argv[]) {
	
	clock_t tInicio, tFim, tDecorrido;

	tInicio = clock();

	if (File_argumentsError(argc)) return 0;

	FILE *file1, *file2, *OUTPUT;

	//file1 = fopen(argv[1], "r");
	//file2 = fopen(argv[2], "r");
	file1 = fopen("file1.txt", "r");
	file2 = fopen("file2.txt", "r");

	if (File_filesError(file1, file2)) return 0;

	OPES opes = File_readFiles(file1, file2);

	OPES_A_HashtagMaisCitadas(&opes);
	OPES_B_UsuariosComMaisTweets(&opes);
	OPES_C_TweetsComMaiorNumeroDeRetweets(&opes);
	OPES_D_UsuariosMaisMencionados(&opes);
	OPES_E_UsuariosMaisInfluentes(&opes);
	OPES_G_TermosAssociados(&opes);

	tFim = clock();

	tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));

	printf("Tempo decorrido: %f", tDecorrido);

    return 0;
}
