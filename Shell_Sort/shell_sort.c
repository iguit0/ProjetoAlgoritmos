#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void shell_sort(int* elementos, int n) {
    int i,j,h=1;
    do {
        h= 3 * h + 1;
    }while(h<n);
    do {
        h /= 3;
        for (i=h+1;i<=n;i++) {
            int x = elementos[i];
            j=i;
            while(elementos[j-h] > x) {
                elementos[j] = elementos[j-h];
                j-=h;
                if(j<=h){
                    goto L999;
                }
                L999: elementos[j] = x;
            }
        }
    }while(h!=1);
}

void crescente(int* vetor,int qtd) {
    int i = 0;
    char nome[100], temp[100];
    FILE *file;
    strcpy(nome,"entrada-crescente-");
    sprintf(temp, "%d.txt", qtd);
    strcat(nome, temp);
    file = fopen(nome, "w");
    for(i = 0; i < qtd; i++){
        vetor[i] = i;
        fprintf(file, "%d\n", i);
    }
    fclose(file);
}

void decrescente(int* vetor, int qtd){
    int i = 0, j = 0;
    char nome[100], temp[100];
    FILE *file;
    strcpy(nome,"entrada-decrescente-");
    sprintf(temp, "%d.txt", qtd);
    strcat(nome, temp);
    file = fopen(nome, "w");
    for(i = qtd; i > 0; i--){
        vetor[j++] = i;
        fprintf(file, "%d\n", i);
    }
    fclose(file);
}

void aleatorio(int* vetor, int qtd){
    int i = 0;
	int posicao = 0;
	int random;
	int inicio = 0;
	int final = 100;

    char nome[100], temp[100];
	srand((unsigned)time(NULL));
	FILE *file;
	strcpy(nome,"entrada-aleatorio-");
	sprintf(temp, "%d.txt", qtd);
	strcat(nome, temp);
	file = fopen(nome, "w");
	for(i = 0; i < qtd; i++){
		random = rand() % (final - inicio);
		random = random + inicio;
		fprintf(file, "%d\n", random);
		vetor[posicao] = random;
		posicao++;
	}
	fclose(file);
}

float tempo(int* vetor,int tamanho,int algoritmo){
    clock_t tInicial, tFinal;
    float tempoGasto;
    tInicial = clock();
    // algoritmo aqui
    tFinal = clock();
    float t2 = tFinal = tInicial;
    tempoGasto = ((float)(tFinal - tInicial))/(float)(CLOCKS_PER_SEC/1000);

    return tempoGasto;
}

// menu p/ escolha do algoritmo
int menu() {
    int opcao;
    printf("\n\tEscolha o algoritmo\n");
    printf("1 - Shell Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Selection Sort\n");
    printf("4 - Merge Sort\n");
    printf("Digite uma opcao: ");
    scanf("%d",&opcao);
    return opcao;
}

//menu metodo crescente
int menu2(){
	int opcao;
		printf("Escolha o metodo: \n");
		printf("1 - Crescente \n");
		printf("2 - Decrescente \n");
		printf("3 - Aleatorio \n");
        printf("Digite uma opcao: ");
		scanf("%d", &opcao);
	return opcao;
}

int menu3(){
	int opcao;
		printf("Escolha o tamanho: \n");
		printf("1 - 10 \n");
		printf("2 - 100 \n");
		printf("3 - 1000 \n");
		printf("4 - 10000 \n");
		printf("5 - 1000000 \n");
		printf("6 - 10000000 \n");
        printf("Digite uma opcao: ");
		scanf("%d", &opcao);
			switch(opcao){
				case 1:
					return 10;
					break;
				case 2:
					return 100;
					break;
				case 3:
					return 1000;
					break;
				case 4:
					return 10000;
					break;
				case 5:
					return 100000;
					break;
				case 6:
					return 1000000;
					break;
		}
}

int main() {
    int algoritmo;
    int metodo;
    int tamanho;
    algoritmo = menu();
    metodo = menu2();
    tamanho = menu3();

    int *v = (int *) malloc(tamanho*sizeof(int));

    switch (metodo) {
        case 1:
            crescente(v, tamanho);
            printf("\n[CRESCENTE] ~ Entrada de tamanho %d gerada com sucesso!!",tamanho);
            break;
        case 2:
            decrescente(v, tamanho);
            printf("\n[DESCRESCENTE] ~ Entrada de tamanho %d gerada com sucesso!!",tamanho);
            break;
        case 3:
            aleatorio(v, tamanho);
            printf("\n[ALEATORIO] ~ Entrada de tamanho %d gerada com sucesso!!",tamanho);
            break;
        default:
            printf("\nDigite uma opcao valida");
    }
    //float tempoGasto = tempo(v, tamanho, metodo);

    return 0;
}
