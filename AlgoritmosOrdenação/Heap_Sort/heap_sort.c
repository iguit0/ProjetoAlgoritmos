#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] < arr[largest])
        largest = l;

    if (r < n && arr[r] < arr[largest])
        largest = r;

    if (largest != i){
        int aux = arr[i];
        arr[i] = arr[largest];
        arr[largest] = aux;
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n){

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i=n-1; i>=0; i--){
        int aux = arr[0];
        arr[0] = arr[i];
        arr[i] = aux;
        heapify(arr, i, 0);
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
    heap_sort(elementos,n);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
