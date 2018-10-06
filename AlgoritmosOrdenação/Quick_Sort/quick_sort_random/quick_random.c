#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

int partition_random(int a[], int p, int r){
	srand((unsigned)time(NULL));
	int pos = rand() % (r-p);
	pos = pos+p;
	int j= r+1, aux;
    int pivot = a[pos];
    int i = p-1;

	while (1){
      do {j--;} while(a[j] > pivot);

      do {i++;} while(a[i] < pivot);

	  if (i >= j){return j;}

	  aux = a[i];
	  a[i] = a[j];
	  a[j] = aux;
	}
}

void quick_random(int a[], int p, int r){
  int q;
  if (p < r){
        q = partition_random(a, p, r);
        quick_random(a, p, q-1);
        quick_random(a, q+1, r);
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
    quick_random(elementos,0,n-1);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
