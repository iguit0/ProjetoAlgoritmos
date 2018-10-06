#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

int main() {
    FILE* f;
    int algoritmo,tamanho;
    int *elements,i=0,esq,dir;

    clock_t t1,t2,t3;

    algoritmo = menu();
    tamanho = 1000000;

    f =  fopen("entradas/aleatorio/entrada-aleatorio-1000000.txt","r");
	  if (f == NULL) {
  		printf("\nErro na abertura do arquivo!");
  		exit(1);
	  }

    elements = (int*) malloc(tamanho*sizeof(int)); // alocando vetor dinamicamente

    for(i=0;i<tamanho;i++) {
        fscanf(f, "%d", &elements[i]);
    }

    fclose(f);
    free(elementos);
    elementos = NULL;
    return 0;
}
