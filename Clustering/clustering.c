#include <stdio.h>
#include <stdlib.h>

typedef struct sTipoItem {
    int vertice; // vertice destino
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
    LISTA adj;
    int numVertices;
    int numArestas;
} GRAFO;

GRAFO* criaGrafo(int numVertices, int numArestas) {
    int i;
    GRAFO* g = (GRAFO*) malloc(numVertices*sizeof(GRAFO));
    if(g == NULL){
        printf("\nErro ao alocar grafo!");
        return NULL;
    }
    g->numArestas = numArestas;
    g->numVertices = numVertices;
    for(i=0;i<g->numVertices;i++){
        g[i].adj.primeiro = NULL;
        g[i].adj.ultimo = NULL;
    }
    return g;
}

int existeAresta(LISTA* lista, int v){
    CELULA *aux = lista->primeiro;
    int existe = 0;
	if(aux == NULL){
        return 0;
    }
	while(aux != NULL){
        if(aux->info.vertice == v){
            existe = 1;
			break;
        }
        aux = aux->prox;
    }
	return existe;
}

int inserir(LISTA* lista,int v,double w){
    if(existeAresta(lista,v)){
        printf("A aresta ja existe!\n");
        return 0;
    }
    CELULA* p = (CELULA*) malloc(sizeof(CELULA));
    if(p==NULL){
        printf("Nao foi possivel alocar!\n");
        return 0;
    }
    (p->info).vertice = v;
    (p->info).peso = w;
    p->prox = NULL;
    if(lista->primeiro == NULL){
        lista->primeiro = p;
        lista->ultimo = p;
        return 1;
    }
    (lista->ultimo)->prox = p;
    lista->ultimo = p;
    return 1;
}

void inserirAresta(GRAFO* g,int u,int v,double w){
    if(g==NULL){
        return;
    }
    if(inserir(&g[u].adj,v,w)){
        g->numArestas++;
    }
}

void imprimirGrafo(GRAFO* grafo){
    if(grafo == NULL){
	   printf("\n Grafo Vazio!\n");
       return;
	}else{
		int i;
		for(i = 0; i < grafo->numVertices; i++){
		    CELULA* aux = grafo[i].adj.primeiro;
			printf("Vertice: %d --> ", i);
			while(aux != NULL){
			    printf(" %d(%.2lf)", aux->info.vertice,aux->info.peso);
				aux = aux->prox;
			}
			    printf("\n");
	    }
	}
}

void removeAresta(GRAFO* g,int orig,int dest){
    if(g==NULL){
        return;
    }
    CELULA* aux;
    CELULA* prev;
    aux = g[orig].adj.primeiro;
    if(aux->info.vertice == dest){
        g[orig].adj.primeiro = aux->prox;
        free(aux);
    }else{
        prev = aux;
        aux = aux->prox;
        while(aux!=NULL){
            if(aux->info.vertice==dest){
                prev->prox = aux->prox;
                free(aux);
                break;
            }
            prev = aux;
            aux = aux->prox;
        }
    }
}


/* Parte de um vértice inicialmente na árvore, o algoritmo procura
* a aresta de menor peso que conecte um vértice da árvore a outro
* que ainda não esteja na árvore. Esse vértice é então adicionado
* na árvore e o processo se repete até que todos os vértices
* façam parte da árvore ou quando não se pode encontrar uma
* aresta que satisfaça essa condição.
*/


int main() {
    GRAFO* gr = criaGrafo(3,0);
    FILE* f;
    int u,v;
    double w;
    f = fopen("entrada-teste.txt","r");
    if(f == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    while(fscanf(f,"%d %d %lf",&u,&v,&w) != EOF) {
        inserirAresta(gr,u,v,w);
        //printf("%d %d %.2lf\n",u,v,w);
    }
    printf("\t\t\tG(%d,%d)\n",gr->numVertices,gr->numArestas);
    imprimirGrafo(gr);
    removeAresta(gr,0,0);
    printf("\n\tDepois de remover o freekick (0,0)\n\n");
    printf("\t\t\tG(%d,%d)\n",gr->numVertices,gr->numArestas);
    imprimirGrafo(gr);


    free(gr);
    gr = NULL;
    return 0;
}
