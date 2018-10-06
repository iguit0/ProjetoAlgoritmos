#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

/* QUICKSORT1 (PIVO NO MEIO) */
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
/* ./QUICKSORT1 */


/* QUICKSORT2 (Mediana de 3 elementos aleatorios) */
int mediana(int *vetor, int ini, int fim) {
	srand((unsigned)time(NULL));
	int a[3]; //vetor para guardar as 3 posicoes geradas aleatoriamente
	int b;
	for (b=0;b<3; b++){//
	  a[b]= rand() % (fim-ini);// essa funcao incrementa B afim de guardar em A 3 posicoes de elementos aleatorios
	  a[b]=a[b]+ini;
	}

    int tmp;
    int i, j;

	for (i=0;i<3;i++){
	  for (j=0;j<3;j++){
	    if (a[i] <= a[j]){
  	      tmp = a[i];
  	      a[i] = a[j];
  	      a[j] = tmp;
	    }
	  }
	}

	return a[1]; //retorna a posicao
}

int particaoMediana(int *vetor, int p, int r) {
	int j = r+1, aux;
	int pos = mediana(vetor, p, r);
    int pivot = vetor[pos];             // Pivo o return da funcao MEDIANA
    int i = p-1;                    // i = menor elemento

	while (1){
      // Compara o pivo
      do {
	    j--;
	  }while (vetor[j] > pivot);

      do {
        i++;
	  }while (vetor[i] < pivot );

      // Parada
	  if (i >= j){
	    return j;
	  }

	  // Troca vetor[i] com vetor[j]
	  aux = vetor[i];
	  vetor[i] = vetor[j];
	  vetor[j] = aux;
	  // Troca vetor[i] com vetor[j]
	}
}

int* quickSort2(int *vetor, int p, int r) {
  int q;
  if (p < r){
        q = particaoMediana(vetor, p, r);
        quickSort2(vetor, p, q-1); //chamada recursiva da particao a esquerda do pivo
        quickSort2(vetor, q+1, r); //chamada recursiva da particao a direita do pivo
  }
  return vetor;
}
/* ./QUICKSORT2 */

// menu p/ escolha do algoritmo
int menu() {
    int opcao;
    printf("\n\tEscolha o algoritmo\n");
    printf("1 - QuickSort (pivo no meio)\n");
    printf("2 - QuickSort (mediana de 3 aleatorio)\n");
    printf("3 - HeapSort\n");
    printf("\nDigite uma opcao: ");
    scanf("%d",&opcao);
    return opcao;
}

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

    switch (algoritmo) {
        case 1:
            printf("\t\t\tQUICKSORT (PIVO NO MEIO)");
            printf("\n\t\tTamanho entrada: %d", tamanho);
            t1 = clock();
            quickSort1(elements,tamanho);
            t1 = clock() - t1;
            printf("\n-> Funcao quickSort1 (pivo no meio) executou em %f segundos\n", ((float)t1)/CLOCKS_PER_SEC);
            break;
        case 2:
            printf("\t\t\tQUICKSORT (MEDIANA DE 3)");
            printf("\n\t\tTamanho entrada: %d", tamanho);
            t2 = clock();
            quickSort2(elements,esq,dir);
            t2 = clock() - t2;
            printf("\n-> Funcao quickSort2 (mediana de 3 aleatorios) executou em %f segundos\n", ((float)t2)/CLOCKS_PER_SEC);
            break;
        case 3:
            printf("\t\t\tHEAPSORT");
            printf("\n\t\tTamanho entrada: %d", tamanho);
            t3 = clock();
            heapSort(elements,tamanho);
            t3 = clock() - t3;
            printf("\n-> Funcao heapSort executou em %f segundos\n", ((float)t3)/CLOCKS_PER_SEC);
            break;
        default:
            printf("\nDigite uma opcao valida");
    }

    fclose(f);

    return 0;
}
