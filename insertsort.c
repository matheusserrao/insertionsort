#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMERO_MAXIMO_RANDOM 500;

/* PROTOTIPOS DE FUNCOES */
void iniciaSRand();
int* iniciaVetor(int tamanho);
void mostrarVetor(int *vetor, int tamanho);
void ordenarVetorIterativa(int *vetor, int tamanho);
void ordenarVetorRecursivo(int *vetor, int tamanho);

int maximoRecursivo(int *vetor, int tamanho);
int maximoIterativo(int *vetor, int tamanho);

int comparacoesRecursivas = 0;
int trocasRecursivas      = 0;

int main()
{	
	iniciaSRand();
	
	int tamanho;
	
	puts("Informe o tamanho do vetor: ");
	scanf(" %d", &tamanho);
	
	printf("Alimentando o vetor com %d numeros aleatorios... (0 a 500) \n", tamanho);
	
	int *vetor  = iniciaVetor(tamanho);
	int *vetor2[tamanho];
	
	memcpy(vetor2, vetor, tamanho * sizeof(int)); // FAZ UMA COPIA DO VETOR 1 GERADO PARA VETOR 2
	mostrarVetor(vetor, tamanho);
	
	puts("\nOrdenando vetor (insert sort)...\n");
	puts("ITERATIVA\n");

	int maxIterativo = maximoIterativo(vetor, tamanho);
	ordenarVetorIterativa(vetor, tamanho);

	printf("Maximo: %d\n", maxIterativo);
	
	puts("\nRECURSIVA\n");

	int maxRecursivo = maximoRecursivo(vetor, tamanho);
	
	float tempoTotal;
	time_t tempoInicial = time(NULL), tempoFinal;
	ordenarVetorRecursivo(vetor2, tamanho); // USA A COPIA DO VETOR 1

	tempoFinal = time(NULL);
	tempoTotal = difftime(tempoFinal, tempoFinal);

	mostrarVetor(vetor2, tamanho);
	printf("Trocas: %d\n", trocasRecursivas);
	printf("comparacoes: %d\n", comparacoesRecursivas);
	printf("Tempo gasto: %f\n", tempoTotal);
	printf("Maximo: %d\n", maxRecursivo);

	free(vetor);
	//free(vetor2);

	return 0;
}

void iniciaSRand()
{
	srand(time(NULL)); // 1 de janeiro de 1970 (em segundos)
}

int* iniciaVetor(int tamanho)
{	
	int *vetor 			= malloc(sizeof(int*) * tamanho);
	int i 	   			= 0;
	int numeroAleatorio = 0;
	
	for (i = 0; i < tamanho; i++)
	{
		numeroAleatorio = rand() % NUMERO_MAXIMO_RANDOM;
		vetor[i] = numeroAleatorio;
	}
	
	return vetor;
}

void mostrarVetor(int *vetor, int tamanho)
{
	int i = 0;
	printf("---------------------\n");
	for (i = 0; i < tamanho; i++)
	{
		printf("\t\t%d\n", *vetor);
		vetor++;
	}	
	printf("---------------------\n");
}

void ordenarVetorRecursivo(int *vetor, int tamanho)
{	
	if (tamanho <= 1){
		return;
	}
	
	ordenarVetorRecursivo(vetor, tamanho - 1);

	int i, j, atual;
	
	for (i = 1; i < tamanho; i++)
	{
		atual = vetor[i];
	
		for (j = i; (j > 0) && (atual < vetor[j - 1]); j--, comparacoesRecursivas++)
		{
			vetor[j] = vetor[j - 1];
		}
				
		if (atual != vetor[j]) trocasRecursivas++;
					
		vetor[j] = atual;
	}
}

void ordenarVetorIterativa(int *vetor, int tamanho)
{
	float tempoTotal;
	time_t tempoInicial = time(NULL), tempoFinal;
	
	int i, j, atual, trocas = 0, comparacoes = 0;
	
	for (i = 1; i < tamanho; i++)
	{
		atual = vetor[i];
	
		for (j = i; (j > 0) && (atual < vetor[j - 1]); j--, comparacoes++)
			vetor[j] = vetor[j - 1];
		
		if (atual != vetor[j]) trocas++;
			
		vetor[j] = atual;
	}

	tempoFinal = time(NULL);

	tempoTotal = difftime(tempoFinal, tempoFinal);

	mostrarVetor(vetor, tamanho);

	printf("Trocas: %d\n", trocas);
	printf("comparacoes: %d\n", comparacoes);
	printf("Tempo gasto: %f\n", tempoTotal);
}

int maximoIterativo(int *vetor, int tamanho)
{	
	int i;
	int maximo = vetor[0];

	for (i = 1; i < tamanho; i++)
	{
		if (maximo < vetor[i])
			maximo = vetor[i];
	}

	return maximo;
}

int maximoRecursivo(int *vetor, int tamanho)
{
	if (tamanho == 1)
		return vetor[0];
	
	int maximo = maximoRecursivo(vetor, tamanho - 1);

	if (maximo > vetor[tamanho - 1]) return maximo;

	return vetor[tamanho - 1];
}
