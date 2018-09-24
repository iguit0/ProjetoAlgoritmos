#include <stdio.h>
#include <stdlib.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

typedef struct sLista {
    int chave;
    struct sLista* proximo;
} LISTA;

typedef struct sHash{
    LISTA* ptrLista;
}HASH;

int inserir(LISTA** lista, int elemento);
LISTA* criarCelula();
int vazia(LISTA** lista);

int main() {
    HASH* tabela;
    int n=0,elemento=0,opcao;
    printf("Tamanho > ");
    scanf("%d",&n);
    tabela = (HASH*) malloc(n*sizeof(HASH));

    //inserir(&tabela[1].ptrLista, 22); // posicao troco pela funcao k mod

    do {
        printf("\t\n\n TABELA HASH \t\n");
        printf("1 - Inserir\n");
        printf("2 - Vazio\n");
        printf("0 - Sair\n\n");
        printf("Digite sua opcao > ");
        scanf("%d",&opcao);
        switch (opcao) {
          case 1:
            printf("\nElemento > ");
            scanf("%d",&elemento);
            if(inserir(&tabela[1].ptrLista, elemento)==1) printf("Inserido com Sucesso\n");
            else printf("ERRO: Inserir\n");
            break;
          case 2:

            break;
          case 3:
            break;
          case 4:
            break;
          case 5:
            break;
          case 6:
            break;
          case 7:
            break;
          case 8:
            break;
          case 0:
            printf("Voce Saiu!!\n");
            break;
          default:
            printf("Digite uma opcao valida");
          }
    } while(opcao != 0);


    free(tabela);
    tabela = NULL;
    return 0;
}

LISTA* criarCelula() {
    LISTA* nova;
    nova = (LISTA *) malloc(sizeof(LISTA));
    return nova;
}

int vazia(LISTA** lista){
	if( (*lista) == NULL) return 1;
	else return 0;
}

int inserir(LISTA** lista, int elemento) {
    LISTA* novo = criarCelula();
    if (novo == NULL) return 0;
    novo->chave = elemento;
    novo->proximo = NULL;
    if(vazia(lista)){
        (*lista) = novo;
        return 0;
    }
    novo->proximo = (*lista);
    (*lista) = novo;
    //tabela[posicao] = novo;
    return 1;
}
