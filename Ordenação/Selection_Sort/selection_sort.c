#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void selection_sort(int* elementos, int n) {
    int i,j;
    for (i = 0; i < n-1; i++) {
        int min_index = i;
        for (j = i+1; j <= n; j++) {
            if (elementos[min_index] > elementos[j]) {
                min_index = j;
            }
        }
        int temp = elementos[i];
        elementos[i] = elementos[min_index];
        elementos[min_index] = temp;
    }
}

int main() {
    FILE* f;
    int i=0, n=1000000;
    f =  fopen("crescente/entrada-crescente-1000000.txt","r");
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
    selection_sort(elementos,n);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
