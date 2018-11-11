#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos
/* HEAPSORT */
void criarHeap(int *vetor, int i, int f){
	int aux = vetor[i]; //o auxiliar vira o pai
	int j = i*2+1; //atribui j ao primeiro filho de i
		while(j <= f){
			if(j < f){
				if(vetor[j] < vetor[j+1]){ //compara os dois filhos pra ver quem � maior
					j = j+1;
				}
			}
			if(aux < vetor[j]){ //checa se o auxiliar � menor que o filho
				vetor[i] = vetor[j];
				i = j; //troca o pai com o filho
				j = 2*i+1; //calcula o primeiro novo fiho
			}else{
				j = f+1; //j sai do vetor
			}
			vetor[i] = aux; //atribui ao aux o valor do ultimo filho analisado
		}//end while
}

void heapSort(int *vetor, int n){
	int i, aux;
		for(i = (n-1)/2; i>=0; i--){  //atribui i ao meio do vetor e decrementa
			criarHeap(vetor, i, n-1);
		}
		for(i = n-1; i>=1; i--){
			aux = vetor[0];
			vetor[0] = vetor[i];
			vetor[i] = aux;
			criarHeap(vetor, 0, i-1);
		}
}
/* ./HEAPSORT */

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
    heapSort(elementos,n);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
