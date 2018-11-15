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

int main() {
    GRAFO* gr = criaGrafo(150,22500);
    FILE* f;
    int u,v;
    double w;
    f = fopen("dados.txt","r");
    if(f == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    int i=0;
    printf("\tG(%d,%d)\n",gr->numVertices,gr->numArestas);

    while(fscanf(f,"%d %d %lf",&u,&v,&w)!=EOF){
        inserirAresta(gr,u,v,w);
        //printf("%d %d %.2lf\n",u,v,w);
    }
    /*
    //outra forma de ler o arquivo
    for(i=0;i<22500;i++){
        fscanf(f,"%d %d %lf",&u,&v,&w);
        //printf("%d %d %lf\n",u,v,w);
        inserirAresta(gr,u,v,w);
    }*/
    imprimirGrafo(gr);

    return 0;
}
