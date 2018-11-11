#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void shell_sort(int *vetor, int tamanho){
   int i = (tamanho - 1) / 2;
   int chave, k, aux;

   while(i != 0){
      do{
         chave = 1;
         for(k = 0; k < tamanho - i; ++k){
            if(vetor[k] > vetor[k + i]){
               aux = vetor[k];
               vetor[k] = vetor[k + i];
               vetor[k + i] = aux;
               chave = 0;
            }
         }
      }while(chave == 0);
      i = i / 2;
   }
}

int main() {
    FILE* f;
    int i=0, n=1000000;
    int* elementos;
    f =  fopen("decrescente/entrada-decrescente-1000000.txt","r");
	if (f == NULL) {
  	     printf("\nErro na abertura do arquivo!");
         exit(1);
	}
    printf("\tTamanho: [%d]\n",n);

    elementos = (int *) malloc(n*sizeof(int));

    for(i=0;i<n;i++) {
        fscanf(f, "%d", &elementos[i]);
    }

    clock_t ini = clock(), fim;
    shell_sort(elementos,n);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
