/* https://github.com/iguit0/Projeto-De-Algoritmos */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 1000000

typedef struct sNo{
	int info;
	struct sNo* esquerda;
	struct sNo* direita;
}NO;

int main() {
	NO* raiz;
	NO* a;
	FILE* f;
	int opc, qnt = 0, i = 0,*elementos, valor;
	/*
	f =  fopen("entrada1e+06.txt","r");
	if (f == NULL) {
  		printf("\nErro na abertura do arquivo!");
  		exit(1);
	}

    elementos = (int*) malloc(n*sizeof(int));

    for(i=0;i<n;i++) {
        fscanf(f, "%d", &elementos[i]);
    }*/
	
	inicializar(&raiz);
	inserirRecursivo(&raiz,50); //teste
	inserirRecursivo(&raiz,40); //teste
	do {
        printf("\t\t\t--MENU--\n1) VAZIO\n2) PESQUISA BINARIA\n3) PESQUISA SEQUENCIAL\n4) EXIBIR TUDO\n5) ENCERRAR PROGRAMA\n\t\n\tDIGITE SUA OPCAO > ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                if(vazia(&raiz)==1) printf("\n\tArvore vazia!\n\n");
                else printf("\n\tArvore nao esta vazia!!\n\n");
                break;
            case 2:
            	//pesquisabinaria(&raiz,n);
                break;
            case 3:
            	pesquisasequencial(&raiz);
                break;
            case 4:
                exibe(&raiz);
                break;
            case 5:
                printf("\nVoce saiu!!");
                break;
            default:
                printf("Digite uma opcao valida!");
        }
    } while (opc != 5);

	
	free(raiz);
	raiz = NULL;
	return 0;
}

void pesquisasequencial(NO** raiz) {
    NO* aux = raiz;
    int valor, cont = 0, i, count = 0;
    float tempo = 0;
    clock_t in, f;
    //setbuf(stdin, NULL);
    printf("\nDigite a chave > ");
    scanf("%d", &valor);
    i = clock();
    while (aux != NULL) {
        cont++;
        if (aux->info == valor) {
            count++;
            printf("\t\t--Registro encontrado-- \n\n");
            printf("Valor: %d\n", aux->info);
        }
        aux = aux->esquerda;
    }
    f = clock();
    tempo = ((float) (f - in) / CLOCKS_PER_SEC);
    if (count == 0) {
        printf("\t\tREGISTRO NAO ENCONTRADO\n\n");
    }
    printf("\nQuantidade de registros visitados: %d\n", cont);
    printf("\nTempo de execucao:  %.2f ms\n", (tempo*1000));
}

NO* pesquisabinaria(NO** raiz, int qnt) {
    NO* aux = raiz;
    NO* a = raiz;
    int valor, comparacao=0, chave = 0, inicio = 0, meio = 0, fim = (qnt - 1), ok = 0, x = 0;
    float tempo = 0;
    clock_t i, f;
    printf("\nDigite a chave: ");
    scanf("%d", &valor);
    i = clock();
    while (inicio <= fim) {
        //percorre ate achar o elemento do meio
        meio = (inicio + fim) / 2;
        x = 0;
        a = raiz;
        while (x != meio) {
            a = a->direita;
            x++;
        }
        chave = a->info; //pega a chave

        if (valor == chave) { //se for igual ao meio, exibe e encerra a busca
            printf("\t\t--Registro encontrado-- \n\n");
            printf("Valor: %d\n", a->info);
            ok = 1;
            break;
        } else if (valor < chave) { ///se for menor, limita a busca a primeira metade
            fim = meio - 1;
        } else { //se for maior, limita a busca a segunda metade
            inicio = meio + 1;
        }
        comparacao++;
        aux = aux->direita;
    }
    f = clock();
    tempo = ((float) (f - i) / CLOCKS_PER_SEC);
    if (ok == 0) {
        printf("\t\tREGISTRO NAO ENCONTRADO\n\n");
        chave = 999999;
    }

    printf("\nNumero de comparacoes:  %i\n", comparacao);
    printf("\nTempo de execucao:  %.2f ms\n", (tempo*1000));
    return a;
}

void exibe(NO** raiz) {
	printf("\n%d", (*raiz)->info);
}


NO* criarCelula(){
	NO* nova = (NO *) malloc(sizeof(NO));
	if(nova == NULL) return NULL;
	nova->direita = NULL;
	nova->esquerda = NULL;
	return nova;
}

void inicializar(NO** raiz){
	(*raiz) = NULL;
}

int vazia(NO** raiz){
	if((*raiz) == NULL) return 1;
	return 0;
}

int inserirRecursivo(NO** raiz, int elemento){
	if(vazia(raiz)){
		NO* nova = criarCelula();
		nova->info = elemento;
		*raiz = nova;
		return 1;
	}
	if((*raiz)->info > elemento){
		return inserirRecursivo(&(*raiz)->esquerda,elemento);
	}else{
		return inserirRecursivo(&(*raiz)->direita,elemento);
	}
}

int inserirIterativo(NO** raiz, int elemento){
	NO* aux = *raiz;
	NO* nova = criarCelula();
	nova->info = elemento;
	if(vazia(raiz)){
		*raiz = nova;
		return 1;
	}
	while (aux != NULL){
		if(aux->info > elemento){
			if(aux->esquerda == NULL){
				aux->esquerda = nova;
				return 1;
			}
			aux = aux->esquerda;
		}else{
			if(aux->direita == NULL){
				aux->direita = nova;
				return 1;
			}
			aux = aux->direita;
		}
	}
	return 0;
}

void emOrdem(NO** raiz){
	if((*raiz)!= NULL){
		emOrdem(&(*raiz)->esquerda);
		printf("\n%d",(*raiz)->info);
		emOrdem(&(*raiz)->direita);
	}
}

void preOrdem(NO** raiz){
    if((*raiz) != NULL){
        printf("\n%d", (*raiz)->info);
        preOrdem(&(*raiz)->direita);
        preOrdem(&(*raiz)->esquerda);
    }
}

void posOrdem(NO** raiz){
    if((*raiz) != NULL){
        posOrdem(&(*raiz)->esquerda);
        posOrdem(&(*raiz)->direita);
        printf("\n%d", (*raiz)->info);
    }
}

int contarNos(NO* raiz){
   if(raiz == NULL)
        return 0;
   else
        return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int altura(NO* raiz){
   if((raiz == NULL) || (raiz->esquerda == NULL && raiz->direita == NULL))
       return 0;
   else
       return 1 + maior(altura(raiz->esquerda), altura(raiz->direita));
}

