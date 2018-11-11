#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void insertion_sort(int* elementos, int n) {
    int i,j;
    for(i=1;i<n;i++){
        j = i-1;
        int x = elementos[i];
        while(x < elementos[j] && j >= 0){
            elementos[j+1] = elementos[j];
            elementos[j] = x;
            j--;
        }
    }
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
    insertion_sort(elementos, n);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
