#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// estruturas do min heap
struct MinHeapNode {
    int v;
    int key;
};

struct MinHeap {
    int size;
    int capacity;
    int* pos; // necessario para o metodo decreaseKey()
    struct MinHeapNode** array;
};

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
		printf("\t\t\tG(%d,%d)\n\n",grafo->numVertices,grafo->numArestas);
		for(i = 0; i < grafo->numVertices; i++){
		    CELULA* aux = grafo[i].adj.primeiro;
			printf("Vertice: %d --> ", i);
			while(aux != NULL){
                if(aux->prox == NULL)
			        printf(" %d(%.2lf)", aux->info.vertice,aux->info.peso);
                else
                    printf(" %d(%.2lf),", aux->info.vertice,aux->info.peso);
				aux = aux->prox;
			}
			    printf("\n");
	    }
	}
}

void removeAresta(GRAFO* g,int orig,int dest){
    if(g==NULL){
        printf("Grafo Vazio!\n");
        return;
    }
    if(existeAresta(&g->adj,orig)){
        CELULA* aux;
        CELULA* prev;
        aux = g[orig].adj.primeiro;
        // caso especial onde eh o primeiro da lista
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
        g->numArestas--;
    } else {
        printf("\tA aresta (%d,%d) nao existe!\n",orig,dest);
        return;
    }
}

/* FUNCOES HEAPIFY */

// criar nova celula min heap
struct MinHeapNode* newMinHeapNode(int v, int key) {
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}

// criar e inicializar a min heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// funcao que troca dois nos da min heap. minHeapify() usa
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Executar heap em determinado indice
// Essa funcao tambem atualiza a posicao dos nos quando eles sao trocados
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        // Os nos a serem trocados em min heap
        struct MinHeapNode* smallestNode = minHeap->array[smallest];
        struct MinHeapNode* idxNode = minHeap->array[idx];

        // trocar posicoes
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // trocar posicoes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// checar se a min heap ta vazia
int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// encontrar o menor no da heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    // guarda no raiz
    struct MinHeapNode* root = minHeap->array[0];

    // Substitui o no raiz pelo ultimo no
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // atualiza posicao do ultimo no
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // decrementa o tamanho da heap
    // e raiz do heapify
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Funcao para diminuir o valor da chave de um determinado vertice v
// Esta funcao usa a posicao (*pos) do min heap para obter o indice atual do no no heap minimo
void decreaseKey(struct MinHeap* minHeap, int v, int key) {
    // pegar indice de v no vetor de heap
    int i = minHeap->pos[v];

    // pega o no e atualiza o valor de sua chave
    minHeap->array[i]->key = key;

    // Loop com complexidade O(logN)
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
        // trocar no com seu no pai
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // mover o indice do no pai
        i = (i - 1) / 2;
    }
}

// verificar se o vertice v é min heap ou nao
int isInMinHeap(struct MinHeap* minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size) return 1;
    else return 0;
}

// imprimir mst (nos pais)
void printArr(int* pai, int n) {
    int i;
    for (i = 1; i < n; ++i)
        printf("Vertice: %d => Pai: %d\n",i,pai[i]);
}

/* ./ FUNCOES HEAPIFY */

/* ------------ Algoritmo de PRIM ------------
* Parte de um vértice inicialmente na árvore, o algoritmo procura
* a aresta de menor peso que conecte um vértice da árvore a outro
* que ainda não esteja na árvore. Esse vértice é então adicionado
* na árvore e o processo se repete até que todos os vértices
* façam parte da árvore ou quando não se pode encontrar uma
* aresta que satisfaça essa condição. */
void primMST(GRAFO* grafo) {
    int V = grafo->numVertices; // numero dos vertices do grafo
    int parent[V]; // vetor para guardar o resultado da arvore geradora minima
    int key[V]; // vetor de chaves usadas para pegar aresta de menor peso

    // inicializa min Heap com o tamanho de vertices
    struct MinHeap* minHeap = createMinHeap(V);

    // inicializa min heap sendo V total de vertices do grafo.
    // valor da chave de todos os vertices eh, inicialmente
    // infinito (INT_MAX) <limits.h> (exceto o primeiro vertice)
    int v;
    for (v = 1; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }

    // setar chave do vertice da primeira posicao
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;

    // inicializa tamanho da min heap com o numero de vertices do grafo
    minHeap->size = V;

    // loop enquanto min heap nao estiver vazio
    while (!isEmpty(minHeap)) {
        // encontrar o vertice com valor minimo de chave
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // guardar numero de vertice encontrado

        // andar em todos os vertices adjacentes de u (vertice extraido)
        // e atualizar os valores da chave
        CELULA* pCrawl = grafo[u].adj.primeiro;
        while (pCrawl != NULL) {
            int v = pCrawl->info.vertice;

            // se v ainda nao esta incluido na MST e o peso de u-v
            // eh menor que o valor da chave de v, entao atualiza seu valor
            // e o no pai de v
            if (isInMinHeap(minHeap, v) && pCrawl->info.peso < key[v]) {
                key[v] = pCrawl->info.peso;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->prox;
        }
    }

    printf("\n\t\t PRIM - Arvore geradora minima resultante \n\n");
    printArr(parent,V);
}

int main() {
    GRAFO* gr = criaGrafo(6,0);

    FILE* f;
    int u,v;
    double w;
    f = fopen("teste-mst.txt","r");
    if(f == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    while(fscanf(f,"%d %d %lf",&u,&v,&w) != EOF) {
        inserirAresta(gr,u,v,w);
        //printf("%d %d %.2lf\n",u,v,w);
    }
    imprimirGrafo(gr);

    primMST(gr);

    free(gr);
    gr = NULL;
    return 0;
}
