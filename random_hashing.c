#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
	srand(time(NULL));
	long i;
	int n;
	clock_t ini = clock(), fim;
	printf("\nDigite o tamanho do vetor de entrada \n");
	scanf("%d", &n);

	long *hash_vetor = (long*)malloc(n * sizeof(long));
	if(hash_vetor == NULL){
	    return 1;
	}
	for(i = 0; i < n; i++){
	    hash_vetor[i] = 0;
	}
	for(i = 0; i < n; i++){
	   // função hash S2
	   // h(K) = (p * K) mod M, sendo K o próprio elemento inteiro
	   long p = rand()%(n - 1);
	   long pos = (p * (i + 1))%n;
	   if(pos >= n)
	      return 1;
	   if(hash_vetor[pos] != 0){
	     long j = 1;
	     // endereçamento direto S2
		 // hj = (h(x) + j) mod M
	     while((j <= (n - 1)) && (hash_vetor[(pos + j)%n] != 0)){
		    j++;
		 }
		 pos = (pos + j)%n;
	   }
 	  hash_vetor[pos] = (i + 1);
	}
	char string[10];
	sprintf(string, "%d", n);
	FILE* arq = fopen(string, "w");
	if(arq == NULL){
	   return 1;
	}
	for(i = 0; i < n; i++){
	    fprintf(arq, "%ld\n", hash_vetor[i]);
	}
	fclose(arq);
	free(hash_vetor);
	fim = clock();
	double tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
	printf("Tempo consumido: %lf sec.\n", tempo);
    return 0;
}
