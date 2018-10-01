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


AdjList* genGraph(int, int);
void initAdjListVec(AdjList*, int);
void addToAdjList(AdjList*, int, int);
void initAdjVertex(AdjVertex*, int);
void freeGraph(AdjList*, int);


int main(){
    int n, m;
    AdjList* adjListVec;

    scanf("%d %d", &n, &m);
    while(n!=0 ||m!=0 ){
        adjListVec = genGraph(n, m);
        int i;
        for(i=0; i<n; i++){
            printf("%d: ", i+1);
            AdjVertex* v = adjListVec[i].head;
            while(v!=NULL){
                printf("%d->", v->id+1);
                v = v->prox;
            }
            printf("N\n");
        }
        freeGraph(adjListVec, n);
        scanf("%d %d", &n, &m);
    }
}


AdjList* genGraph(int n, int m){
    AdjList* adjListVec;
    int u, v;

    adjListVec = (AdjList *) malloc(n*sizeof(AdjList));
    initAdjListVec(adjListVec, n);
    while(m>0){
        scanf("%d %d", &u, &v);
        addToAdjList(adjListVec, u-1, v-1);
        addToAdjList(adjListVec, v-1, u-1);
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

void initAdjVertex(AdjVertex* vertex, int id){
    vertex->id = id;
    vertex->prox = NULL;
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
