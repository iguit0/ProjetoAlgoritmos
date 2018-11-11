#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

int mediana(int *vetor, int ini, int fim) {
	srand((unsigned)time(NULL));
	int a[3]; //vetor para guardar as 3 posicoes geradas aleatoriamente
	int b;
	for (b=0;b<3; b++){//
	  a[b]= rand() % (fim-ini);// essa funcao incrementa B afim de guardar em A 3 posicoes de elementos aleatorios
	  a[b]=a[b]+ini;
	}

    int tmp;
    int i, j;

	for (i=0;i<3;i++){
	  for (j=0;j<3;j++){
	    if (a[i] <= a[j]){
  	      tmp = a[i];
  	      a[i] = a[j];
  	      a[j] = tmp;
	    }
	  }
	}

	return a[1]; //retorna a posicao
}

int particaoMediana(int *vetor, int p, int r) {
	int j = r+1, aux;
	int pos = mediana(vetor, p, r);
    int pivot = vetor[pos];             // Pivo o return da funcao MEDIANA
    int i = p-1;                    // i = menor elemento

	while (1){
      // Compara o pivo
      do {
	    j--;
	  }while (vetor[j] > pivot);

      do {
        i++;
	  }while (vetor[i] < pivot );

      // Parada
	  if (i >= j){
	    return j;
	  }

	  // Troca vetor[i] com vetor[j]
	  aux = vetor[i];
	  vetor[i] = vetor[j];
	  vetor[j] = aux;
	  // Troca vetor[i] com vetor[j]
	}
}

int* quickSort2(int *vetor, int p, int r) {
  int q;
  if (p < r){
        q = particaoMediana(vetor, p, r);
        quickSort2(vetor, p, q-1); //chamada recursiva da particao a esquerda do pivo
        quickSort2(vetor, q+1, r); //chamada recursiva da particao a direita do pivo
  }
  return vetor;
}

int main() {
    FILE* f;
    int i=0, n=1000000;
    f =  fopen("decrescente/entrada-decrescente-1000000.txt","r");
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
    quickSort2(elementos,0,n-1);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
