#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void intercala(int p, int q, int r, int v[])
{
   int i, j, k, *w;
   w = (int*) malloc ((r-p) * sizeof (int));
   i = p; j = q;
   k = 0;

	while (i < q && j < r) {
		if (v[i] <= v[j]){
	  		w[k++] = v[i++];
		}
	  	else  w[k++] = v[j++];
	}
	while (i < q){
		w[k++] = v[i++];
	}
	while (j < r){
		w[k++] = v[j++];
	}
	for (i = p; i < r; ++i){
		v[i] = w[i-p];
	}
	free (w);
}

void merge_sort(int p, int r, int v[]){
   if (p < r-1) {                 // 1
      int q = (p + r)/2;          // 2
      merge_sort(p, q, v);         // 3
      merge_sort(q, r, v);         // 4
      intercala(p, q, r, v);      // 5
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
    
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
