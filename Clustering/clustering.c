#include <stdio.h>
#include <stdlib.h>

typedef struct sTipoItem {
    int vertice;
    double peso;
} ITEM;

typedef struct sCell {
    ITEM info;
    struct sCell* prox;
} CELULA;

typedef struct sLista {
    CELULA* primeiro;
    CELULA* ultimo;
} LISTA;

typedef struct sGrafo {
    LISTA adj; // lista de adjacência
    int numVertices;
    int numArestas;
} GRAFO;

GRAFO* criaGrafo(int numVertices, int numArestas);
void inicializarLista(CELULA** lista);
int existeAresta(LISTA* lista,int v);
void inserirAresta(GRAFO* grafo,int u,int v,double peso);
int inserir(LISTA* lista,int v,double peso);
void imprimeGrafo(GRAFO* grafo);

int main() {
    FILE* f;
    int i,u,v;
    double w;
    f = fopen("dados.txt","r");
    if(f == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    GRAFO* gr = criaGrafo(150,150);
    //LISTA** ptrLista;
    //CELULA** ptrLista;

    while(fscanf(f,"%d %d %lf",&u,&v,&w) != EOF){
        printf("%d %d %lf\n",u,v,w);
    }


    fclose(f);
    return 0;
}

GRAFO* criaGrafo(int numVertices, int numArestas) {
    int i;
    GRAFO* gr = (GRAFO*) malloc(numVertices*sizeof(GRAFO));
    if(gr == NULL) return NULL;
    gr->numArestas = numArestas;
    gr->numVertices = numVertices;
    for(i=0;i<gr->numVertices;i++){
        gr[i].adj.primeiro = NULL;
        gr[i].adj.ultimo = NULL;
    }
    return gr;
}

// Verificar se existe uma aresta em uma lista de adjacência
int existeAresta(LISTA* lista,int v) {
    CELULA* aux = lista->primeiro;
    int existe = 0;
    if(aux==NULL) return 0;
    while(aux != NULL) {
        if(aux->info.vertice == v) {
            existe = 1;
            return 1;
        }
        aux = aux->prox;
    }
    return existe;
}

void inserirAresta(GRAFO* grafo, int u,int v,double peso) {
    if(grafo == NULL) return;
    if (inserir(&grafo[u].adj,v,peso)) grafo->numArestas++;
}

int inserir(LISTA* lista,int v,double peso) {
    if(existeAresta(lista, v)){
        printf("\nA aresta já existe!");
        return 0;
    }
    CELULA* p = (CELULA*) malloc(sizeof(CELULA));
    if(p==NULL) return 0;
    p->info.vertice = v;
    p->info.peso = peso;
    p->prox = NULL;
    if(lista->primeiro == NULL) {
        lista->primeiro = p;
        lista->ultimo = p;
        return 1;
    }
    lista->ultimo->prox = p;
    lista->ultimo = p;
    return 1;
}

void imprimeGrafo(GRAFO* grafo) {
    if(grafo==NULL){
        printf("Grafo Vazio!\n");
        return;
    }
    // ...
}
