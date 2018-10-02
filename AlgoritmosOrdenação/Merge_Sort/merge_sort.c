#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void merge(int vetor[], int tamanho) {
  int meio = tamanho / 2;
  int i = 0, j = meio, k = 0;
  int aux[tamanho];

  while( i < meio && j < tamanho ){
    if( vetor[i] <= vetor[j] )
      aux[k] = vetor[i++];
    else
      aux[k] = vetor[j++];
    k++;
  }

  if( i == meio )
    while( j < tamanho )
      aux[k++] = vetor[j++];
  else
    while( i < meio )
      aux[k++] = vetor[i++];

  for( i = 0; i < tamanho; i++ )
    vetor[i] = aux[i];
}

int mergeSort(int vetor[], int tamanho){
	int meio = tamanho / 2;

	if( tamanho > 1 ){
		mergeSort(vetor, meio);
		mergeSort(vetor + meio, tamanho - meio);
		merge(vetor, tamanho);
	}
}

int main() {
    FILE* f;
    int i=0, n=10;
    f =  fopen("decrescente/entrada-decrescente-10.txt","r");
	if (f == NULL) {
  	     printf("\nErro na abertura do arquivo!");
         exit(1);
	}
    printf("\tTamanho: [%d]\n",n);

    int *elementos = (int *) malloc(n*sizeof(int));

    for(i=0;i<n;i++) {
        fscanf(f, "%d", &elementos[i]);
    }

    clock_t ini = clock(), fim;
    mergeSort(elementos,n);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
