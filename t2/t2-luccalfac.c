/*
    Nome: Lucca La Fonte Albuquerque Carvalho
    RA: 726563
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct adjVertex{
    int id;
    struct adjVertex* prox;
} AdjVertex;

typedef struct {
    AdjVertex* head;
    AdjVertex* tail;
} AdjList;

typedef struct {
    int* v;
    int begin;
    int end;
} Queue;


AdjList* genGraph(int, int);
void initAdjListVec(AdjList*, int);
void addToAdjList(AdjList*, int, int);
void initAdjVertex(AdjVertex*, int);
void freeGraph(AdjList*, int);
int erdosNumber(AdjList*, int);
void initQueue(Queue*, int);
void initVecs(int*, int*, int);
void insertInQueue(Queue*, int);
bool queueIsEmpty(Queue*);
int removeFromQueue(Queue*);
void freeQueue(Queue*);


int main(){
    int n, m, res;
    AdjList* adjListVec;

    scanf("%d %d", &n, &m);
    while(n!=0 ||m!=0 ){
        adjListVec = genGraph(n, m);
        res = erdosNumber(adjListVec, n);
        if(res==-1)
            printf("infinito\n");
        else
            printf("%d\n", res);
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
        addToAdjList(adjListVec, u, v);
        addToAdjList(adjListVec, v, u);
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

int erdosNumber(AdjList* adjVec, int n){
    Queue q;
    int* colorVec = (int*) malloc(n*sizeof(int));
    int* distVec = (int*) malloc(n*sizeof(int));
    int max=0;
    initQueue(&q, n);
    initVecs(colorVec, distVec, n);

    insertInQueue(&q, 0);
    colorVec[0] = 0;
    distVec[0] = 0;
    while(!queueIsEmpty(&q)){
        int vertexId = removeFromQueue(&q);
        AdjVertex* v = adjVec[vertexId].head;
        while(v!=NULL){
            if(colorVec[v->id]==-1){
                colorVec[v->id] = 0;
                distVec[v->id] = distVec[vertexId] + 1;
                if(max<distVec[v->id])
                    max = distVec[v->id];
                insertInQueue(&q, v->id);
            }
            v = v->prox;
        }
        colorVec[vertexId] = 1;
    }
    for(int i=0; i<n; i++){
        if(distVec[i]==-1){
            max = -1;
            break;
        }
    }
    freeQueue(&q);
    free(colorVec);
    free(distVec);
    return max;
}

void initQueue(Queue* q, int n){
    q->v = (int*) malloc(n*sizeof(int));
    q->begin = 0;
    q->end = 0;
}

void initVecs(int* vec1, int* vec2, int n){
    int i;
    for(i=0; i<n; i++){
        vec1[i] = -1;
        vec2[i] = -1;
    }
}

void insertInQueue(Queue* q, int t){
    q->v[q->end] = t;
    q->end = q->end + 1;
}

bool queueIsEmpty(Queue* q){
    return(q->begin==q->end);
}

int removeFromQueue(Queue* q){
    int r = q->v[q->begin];
    q->begin = q->begin + 1;
    return r;
}

void freeQueue(Queue* q){
    free(q->v);
}
