#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void bubble_sort(int vetor[], int tam) {

    for (int fim = tam-1; fim > 0; --fim) {
        for (int i = 0; i < fim; ++i) {
            if (vetor[i] > vetor[i+1]) {
                int aux = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = aux;
            }
        }
    }
}

int main() {
    FILE* f;
    int i=0, n=1000000;
    f =  fopen("aleatorio/entrada-aleatorio-10.txt","r");
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
    bubble_sort(elementos,n);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
