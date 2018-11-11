#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

void particao(int* elements,int esq,int dir,int* i,int* j){
    int x,w;
    *i = esq;
    *j = dir;
    x = elements[(*i + *j) / 2]; // pivo
    do {
        while(x > elements[*i]) (*i)++;
        while (x < elements[*j]) (*j)--;
        if(*i <= *j) {
            w = elements[*i];
            elements[*i] = elements[*j];
            elements[*j] = w;
            (*i)++;
            (*j)--;
        }
    }while(*i <= *j);
}

void ordena(int* elements,int esq,int dir) {
    int i,j;
    particao(elements, esq, dir, &i, &j);
    if(esq < j) {
        ordena(elements,esq,j);
    }
    if(i < dir) {
        ordena(elements,i,dir);
    }
}

void quickSort1(int* elements, int n) {
    ordena(elements,0,n-1);
}

int main() {
    FILE* f;
    int i=0, n=100000;
    f =  fopen("decrescente/entrada-decrescente-100000.txt","r");
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
    quickSort1(elementos,n);
    fim = clock();
    double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo consumido: %lf sec.\n", tempo);

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
