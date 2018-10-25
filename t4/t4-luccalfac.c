/*
    Nome: Lucca La Fonte Albuquerque Carvalho
    RA: 726563
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct adjVertex{
    int id;
    struct adjVertex* prox;
} AdjVertex;

typedef struct {
    AdjVertex* head;
    AdjVertex* tail;
} AdjList;

/*typedef struct {
    int* v;
    int top;
} Stack;*/

int* getPesos(int);
AdjList* genGraph(int, int);
void initAdjListVec(AdjList*, int);
void addToAdjList(AdjList*, int, int);
void initAdjVertex(AdjVertex*, int);
void freeGraph(AdjList*, int);
int maxTime(AdjList*, int*, int);
void DFS(AdjList*, int, int*, int*);
void initVecColor(int*, int);
void DFSaux(AdjList*, int, int*, int*, int*);

int main(){
    int n, m;
    AdjList* adjListVec;
    int* pesos;

    scanf("%d %d", &n, &m);
    while(n!=0 ||m!=0 ){
        pesos = getPesos(n);
        adjListVec = genGraph(n, m);
        printf("%d\n", maxTime(adjListVec, pesos, n));
        freeGraph(adjListVec, n);
        free(pesos);
        scanf("%d %d", &n, &m);
    }
}

int* getPesos(int n){
    int* res = (int*) malloc(n*sizeof(int));

    for(int i=0; i<n; i++)
        scanf("%d", &(res[i]));

    return res;
}

AdjList* genGraph(int n, int m){
    AdjList* adjListVec;
    int u, v;

    adjListVec = (AdjList *) malloc(n*sizeof(AdjList));
    initAdjListVec(adjListVec, n);
    while(m>0){
        scanf("%d %d", &u, &v);
        addToAdjList(adjListVec, u, v);
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

void addToAdjList(AdjList* vec, int u, int v){
    AdjVertex* vertexV = (AdjVertex*) malloc(sizeof(AdjVertex));
    initAdjVertex(vertexV, v);

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

void initAdjVertex(AdjVertex* vertex, int id){
    vertex->id = id;
    vertex->prox = NULL;
}

int maxTime(AdjList* adjVec, int* pesos, int n){
    int max=0;
    //Stack* p = (Stack*) malloc(sizeof(Stack));

    //initStack(p, n);
    DFS(adjVec, n, pesos, &max);

    return max;
}

void DFS(AdjList* adjVec, int n, int* pesos, int* max){
    int* vecColor = (int*) malloc(n*sizeof(int));

    initVecColor(vecColor, n);
    for(int i=0; i<n; i++){
        if(vecColor[i]==-1){
            DFSaux(adjVec, i, pesos, vecColor, max);
        }
    }
}

void initVecColor(int* vecColor, int n){
  for(int i=0; i<n; i++)
    vecColor[i] = -1;
}

void DFSaux(AdjList* adjVec, int u, int* pesos, int* vecColor, int* max){
    AdjVertex* vertex;
    int maxLocal = pesos[u];

    vecColor[u] = 0;
    vertex = adjVec[u].head;
    while(vertex!=NULL){
        if(vecColor[vertex->id]==-1)
            DFSaux(adjVec, vertex->id, pesos, vecColor, max);
        if(maxLocal<pesos[u]+pesos[vertex->id])
            maxLocal = pesos[u]+pesos[vertex->id];
        vertex = vertex->prox;
    }
    vecColor[u] = 1;
    pesos[u] = maxLocal;
    if((*max)<maxLocal)
        *max = maxLocal;
}
