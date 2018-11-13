#include <stdio.h>
#include <stdlib.h>

// Estrutura para modularizar o 'freekick' da célula
typedef struct sTipoItem {
    int vertice; // vertice destino (dest)
    double peso;
} ITEM;

// Estrutura para representar uma celula da lista de adjancecia
typedef struct sCell {
    ITEM info;
    struct sCell* prox;
} CELULA;

// Estrutura para representar uma lista de adjacencia
typedef struct sLista {
    CELULA* primeiro;
    CELULA* ultimo;
} LISTA;

// Estrutura para representar um grafo
// Um grafo é um array de lista de adjacencias
// O tamanho do grafo vai ser V (numero de vertices no grafo)
typedef struct sGrafo {
    LISTA* adj; // lista de adjacência
    int numVertices;
    int numArestas;
} GRAFO;

GRAFO* criaGrafo(int numVertices);
void inserirAresta(GRAFO* grafo,int u,int v,double peso);
void imprimeGrafo(GRAFO* grafo);

int main() {
    GRAFO* gr = criaGrafo(10);
    FILE* f;
    int i,u,v;
    double w;
    f = fopen("entrada-teste.txt","r");
    if(f == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    while(fscanf(f,"%d %d %lf",&u,&v,&w) != EOF){
        //printf("%d %d %.2lf\n",u,v,w);
        inserirAresta(gr,u,v,w);
    }

    imprimeGrafo(gr);

    fclose(f);
    free(gr);
    return 0;
}

// Criar nova celula para inserir na lista de adjacencia
CELULA* criarCelula(int dest) {
    CELULA* novo = (CELULA*) malloc(sizeof(CELULA));
    novo->info.vertice = dest;
    novo->prox = NULL;
    return novo;
}

// Funcao para criar o grafo com V vertices
GRAFO* criaGrafo(int numVertices) {
    GRAFO* g = (GRAFO*) malloc(sizeof(GRAFO));
    if(g == NULL){
        printf("\nErro ao alocar grafo!");
        return NULL;
    }
    g->numVertices = numVertices;
    g->adj = (LISTA*) malloc(numVertices*sizeof(LISTA));
    int i;
    for(i=0;i<numVertices;i++){
        g->adj[i].primeiro = NULL;
        g->adj[i].ultimo = NULL;
    }
    return g;
}

// Insere uma aresta no grafo
void inserirAresta(GRAFO* grafo, int u,int v,double peso) {
    // Insere uma aresta da raíz para destino
    // Uma nova celula é inserida na lista de adjacencia de raízes
    // a celula é inserida no inicio
    if(grafo == NULL) return;
    CELULA* novo = criarCelula(v);
    if(novo==NULL){
        printf("\nNao foi possivel alocar!");
        exit(1);
    }
    novo->info.peso = peso;
    novo->prox = grafo->adj[u].primeiro;
    grafo->adj[u].primeiro = novo;

    // como o grafo nao é direcionado, adiciona-se tambem
    // uma aresta do destino para a raíz
    novo = criarCelula(u);
    novo->info.peso = peso;
    novo->prox = grafo->adj[v].primeiro;
    grafo->adj[v].primeiro = novo;
}

// Imprimir a lista de adjacencia do grafo
void imprimeGrafo(GRAFO* g) {
	int v;
	for (v = 0; v < g->numVertices; ++v) {
        CELULA* aux = g->adj[v].primeiro;
		printf("V[%d]: ", v);
		while (aux) {
			printf("%d(%.2lf) -> ", aux->info.vertice,aux->info.peso);
			aux = aux->prox;
		}
		printf("\n");
	}
}
