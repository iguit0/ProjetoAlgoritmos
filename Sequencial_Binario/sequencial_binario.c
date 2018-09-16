#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// https://github.com/iguit0/Projeto-De-Algoritmos

typedef struct sCell{
   	int chave;
   	struct sCell* prox;
} CELULA;

CELULA* cria();
int vazia(CELULA *no);
void inserirdinamica(CELULA *lista);
void inseriraleatorio(CELULA *lista, int i);
void exibe(CELULA *lista);
void escolher_pesquisa();
CELULA* pesquisabinaria(CELULA *lista, int qnt);
void pesquisasequencial(CELULA *lista, int qnt);

int main() {
    int opc, opcinserir, qnt = 0, i = 0;
    CELULA *controle,* a;
    int *vet = (int *) malloc(sizeof (int));
    controle = cria();
    do {
        printf("\t\t\t--MENU--\n1) INSERIR\n2) CONSULTAR\n3) EXCLUIR\n4) EXIBIR TUDO\n5) ENCERRAR PROGRAMA\n\t\n\tDIGITE SUA OPCAO > ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                printf("Qual a maneira de insercao?\n1-Aleatorio\n2-Estático\n-->OPCAO:");
                scanf("%d", &opcinserir);
                if (opcinserir == 1) {
                    printf("Qual a quantidade de CELULA para gerar automaticamente?");
                    scanf("%d", &qnt);
                    inseriraleatorio(controle, qnt);
                }
                if (opcinserir == 2) {
                    qnt++;
                    inserirdinamica(controle);
                }
                system("clear");
                break;
                opcinserir = 0;
            case 2:
                printf("\n\tPesquisar como\n1 - Binaria\n2 - Sequencial\n\nOpcao > ");
                scanf("%d", &opcinserir);
                if (opcinserir == 1) {
                    a = pesquisabinaria(controle, qnt);
                }
                if (opcinserir == 2) {
                    pesquisasequencial(controle, qnt);
                }
                break;
            case 3:
                //excluir(controle, qnt);
                break;
            case 4:
                exibe(controle);
                break;
            case 5:
                printf("\nVoce saiu!!");
                system("clear");
                break;
            default:
                printf("Digite uma opcao valida!");
        }
    } while (opc != 5);

    free(controle);
    controle = NULL;
    return 0;
}

CELULA* cria() {
    CELULA* lista = (CELULA*) malloc(sizeof(CELULA));
    lista->prox = NULL;
    return lista;
}

int vazia(CELULA *no) {
    if (no->prox == NULL) return 1;
    else return 0;
}

void inserirdinamica(CELULA *lista) {
    CELULA *atual, *anterior;
    CELULA *novo = (CELULA*) malloc(sizeof(CELULA));
    int cont = 0;
    printf("Elemento ser inserido: ");
    scanf("%d", &novo->chave);
    novo->prox = NULL;
    atual = lista;
    anterior = NULL;
    if (vazia(atual) == 1) {
        novo->prox = NULL;
        lista->prox = novo;
    } else {
        while (atual != NULL && atual->chave <= novo->chave) {
            if (atual->chave == novo->chave) {
                cont++;
            }
            anterior = atual;
            atual = atual->prox;
        }
        if (cont == 0) {
            novo->prox = atual;
            if (anterior == NULL) {
                lista->prox = novo;
            } else {
                anterior->prox = novo;
            }
        } else {
            printf("ERRO! Numeros de chave iguais\n");
        }
    }
}

void inseriraleatorio(CELULA *lista, int quantidade) {
    CELULA *atual, *anterior;
    int j, num, cont = 0, i;
    srand(time(NULL));
    for (i = 0; i < quantidade; i++) {
        CELULA *novo = (CELULA *) malloc(sizeof (CELULA));
        novo->chave = i + 1;
        //printf("Valor de quantidade=%d e valor de chave aleatorio =%d\n", i, novo->chave);
        atual = lista;
        anterior = NULL;
        if (vazia(atual) == 1) {
            novo->prox = NULL;
            lista->prox = novo;
        }
        else {
            while (atual != NULL && atual->chave <= novo->chave) {
                if (atual->chave == novo->chave) {
                    cont++;
                }
                anterior = atual;
                atual = atual->prox;
            }
            if (cont == 0) {
                novo->prox = atual;
                if (anterior == NULL) {
                    lista->prox = novo;
                }
                else {
                    anterior->prox = novo;
                }
            } else {
                printf("ERRO! Numeros de chave iguais\n");
            }
        }
    }
}

CELULA* pesquisabinaria(CELULA *lista, int qnt) {
    CELULA *aux = lista;
    CELULA *a = lista;
    int valor, comparacao=0, chave = 0, inicio = 0, meio = 0, fim = (qnt - 1), ok = 0, x = 0;
    float tempo = 0;
    clock_t i, f;
    printf("\nDigite a chave: ");
    scanf("%d", &valor);
    i = clock();
    while (inicio <= fim) {
        //percorre a lista até achar o elemento do meio
        meio = (inicio + fim) / 2;
        x = 0;
        a = lista;
        while (x != meio) {
            a = a->prox;
            x++;
        }
        chave = a->chave; //pega a chave

        if (valor == chave) { //se for igual ao meio, exibe e encerra a busca
            printf("\t\t--Registro encontrado-- \n\n");
            printf("Valor: %d\n", a->chave);
            ok = 1;
            break;
        } else if (valor < chave) { ///se for menor, limita a busca a primeira metade
            fim = meio - 1;
        } else { //se for maior, limita a busca a segunda metade
            inicio = meio + 1;
        }

        comparacao++;
        aux = aux->prox;
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

void pesquisasequencial(CELULA *lista, int qnt) {
    CELULA *aux = lista;
    int valor, cont = 0, i, count = 0;
    float tempo = 0;
    clock_t in, f;
    setbuf(stdin, NULL);
    printf("Digite a chave :");
    scanf("%d", &valor);
    i = clock();
    while (aux != NULL) {
        cont++;
        if (aux->chave == valor) {
            count++;
            printf("\t\t--Registro encontrado-- \n\n");
            printf("Valor: %d\n", aux->chave);
        }
        aux = aux->prox;
    }
    f = clock();
    tempo = ((float) (f - in) / CLOCKS_PER_SEC);
    if (count == 0) {
        printf("\t\tREGISTRO NAO ENCONTRADO\n\n");
    }
    //printf("\nQuantidade de registros visitados: %d\n", cont);
    printf("\nTempo de execucao:  %.2f ms\n", (tempo*1000));
}

void exibe(CELULA *lista) {
    CELULA* aux = lista->prox;
    if (aux == NULL) {
        printf("vazio\n");
    } else {
        printf("Elementos > ");
        while (aux != NULL) {
            printf("%d ", aux->chave);
            aux = aux->prox;
        }
    }
    printf("\n\n");
}
