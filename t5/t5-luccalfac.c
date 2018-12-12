/*
    Nome: Lucca La Fonte Albuquerque Carvalho
    RA: 726563
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct adjVertex{
    int id;
    int peso;
    struct adjVertex* prox;
} AdjVertex;

typedef struct {
    AdjVertex* head;
    AdjVertex* tail;
} AdjList;

AdjList* genGraph(int, int);
void initAdjListVec(AdjList*, int);
void addToAdjList(AdjList*, int, int, int);
void initAdjVertex(AdjVertex*, int, int);
void freeGraph(AdjList*, int);
int* encontraMenoresCustos(int, int, AdjList*);
int pegaMenorDist(int*, int*, int);

int main(){
    int n, m, k;
    int* vetorEstufas;
    AdjList* adjListVec;

    scanf("%d %d %d", &n, &m, &k);

    adjListVec = genGraph(n, m);

    vetorEstufas = encontraMenoresCustos(n, k, adjListVec);

    freeGraph(adjListVec, n);

    for(int i=k; i<n-1; i++)
        printf("%d ", vetorEstufas[i]);

    printf("%d\n", vetorEstufas[n-1]);

    free(vetorEstufas);
}

AdjList* genGraph(int n, int m){
    AdjList* adjListVec;
    int u, v, peso;

    adjListVec = (AdjList *) malloc(n*sizeof(AdjList));
    initAdjListVec(adjListVec, n);
    while(m>0){
        scanf("%d %d %d", &u, &v, &peso);
        addToAdjList(adjListVec, u, v, peso);
        addToAdjList(adjListVec, v, u, peso);
        m--;
    }

    return adjListVec;
}

void initAdjListVec(AdjList* vec, int n){
    int i;

    for(i=0; i<n; i++){
        vec[i].head = NULL;
        vec[i].tail = NULL;
    }
}

void addToAdjList(AdjList* vec, int u, int v, int peso){
    AdjVertex* vertexV = (AdjVertex*) malloc(sizeof(AdjVertex));
    initAdjVertex(vertexV, v, peso);

    if(vec[u].head==NULL){
        vec[u].head = vertexV;
        vec[u].tail = vec[u].head;
        return;
    }
    vec[u].tail->prox = vertexV;
    vec[u].tail = vec[u].tail->prox;
}

void freeGraph(AdjList* vec, int n){
    int i;
    AdjVertex* aux;
    for(i=0; i<n; i++){
        while(vec[i].head!=NULL){
            aux = vec[i].head;
            vec[i].head = aux->prox;
            free(aux);
        }
    }
    free(vec);
}

void initAdjVertex(AdjVertex* vertex, int id, int peso){
    vertex->id = id;
    vertex->peso = peso;
    vertex->prox = NULL;
}

int* encontraMenoresCustos(int n, int k, AdjList* vec){
    int* dist = (int*) malloc(n*sizeof(int));
    int* vetorEstufas = (int*) malloc(n*sizeof(int));
    int* s = (int*) malloc(n*sizeof(int));

    for(int i=0; i<k; i++){
        dist[i] = 0;
        s[i] = 1;
        vetorEstufas[i] = i;
    }

    for(int i=k; i<n; i++){
        dist[i] = -1;
        s[i] = 1;
        vetorEstufas[i] = -1;
    }

    int u;
    while((u = pegaMenorDist(dist, s, n))!=-1){
        AdjVertex* vertex = vec[u].head;
        while(vertex!=NULL){
            if(s[vertex->id]){
                if((dist[vertex->id]>dist[u]+vertex->peso || dist[vertex->id]==-1)){
                    dist[vertex->id] = dist[u]+vertex->peso;
                    vetorEstufas[vertex->id] = vetorEstufas[u];
                }
                else if(dist[vertex->id]==dist[u]+vertex->peso && vetorEstufas[vertex->id]>vetorEstufas[u])
                    vetorEstufas[vertex->id] = vetorEstufas[u];
            }
            vertex = vertex->prox;
        }
    }

    /*for(int i=0; i<n; i++)
        printf("%d\n", dist[i]);

    printf("\n");*/

    free(dist);
    free(s);

    return vetorEstufas;
}


int pegaMenorDist(int* dist, int* s, int n){
    int minIndex=-1;

    for(int i=0; i<n; i++){
        if(minIndex==-1){
            if(s[i] && dist[i]!=-1)
                minIndex=i;
        }
        else if(s[i] && dist[i]!=-1 && dist[minIndex]>dist[i])
            minIndex = i;
    }

    if(minIndex!=-1)
        s[minIndex] = 0;

    return minIndex;
}
