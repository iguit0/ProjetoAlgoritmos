/* https://github.com/iguit0/Projeto-De-Algoritmos */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Retorna -1 caso não encontre ou a posição, caso encontre.
 */
 int procura(int vetor[], int tamanho, int elementoProcurado) {
     int i;
     for (i = 0; i < tamanho; i++) {
         if (vetor[i] == elementoProcurado) {
             return i;
         }
     }
     return -1;
 }

int main() {
	int array[] = {1, 4, 5, 2, 42, 34, 54, 98, 89, 78, 67};
	int elementoProcurado;
    int i=0;
    printf("\tArray -> ");
    for(i=0;i<10;i++) {
        printf("%d ",array[i]);
    }
	printf("\nQual elemento quer procurar -> ");
	scanf("%d",&elementoProcurado);
	int posicao = procura(array,11,elementoProcurado);
	if(posicao == -1){
		printf("\nNao existe no vetor");
	} else {
		printf("\nElemento [%d] esta na posicao -> %d",elementoProcurado,posicao);
	}

	return 0;
}
