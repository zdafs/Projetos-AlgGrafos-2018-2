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
bool graphIsBi(AdjList*, int);
void initQueue(Queue*, int);
void initColorVec(int*, int);
void insertInQueue(Queue*, int);
bool queueIsEmpty(Queue*);
int removeFromQueue(Queue*);
void freeQueue(Queue*);


int main(){
    int n, m;
    AdjList* adjListVec;

    scanf("%d %d", &n, &m);
    while(n!=0 ||m!=0 ){
        adjListVec = genGraph(n, m);
        if(graphIsBi(adjListVec, n))
            printf("SIM\n");
        else
            printf("NAO\n");
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

bool graphIsBi(AdjList* adjVec, int n){
    Queue q;
    int* colorVec = (int*) malloc(n*sizeof(int));
    int i=0;
    initQueue(&q, n);
    initColorVec(colorVec, n);

    insertInQueue(&q, 0);
    colorVec[0] = 0;
    while(i<n){
        while(!queueIsEmpty(&q)){
            int vertexId = removeFromQueue(&q);
            AdjVertex* v = adjVec[vertexId].head;
            while(v!=NULL){
                if(colorVec[v->id]==colorVec[vertexId]){
                    return 0;
                }
                if(colorVec[v->id]==-1){
                    colorVec[v->id] = !colorVec[vertexId];
                    insertInQueue(&q, v->id);
                }
                v = v->prox;
            }
        }
        if(colorVec[i]==-1){
            insertInQueue(&q, i);
            colorVec[i] = 0;
        }
        i++;
    }
    freeQueue(&q);
    free(colorVec);
    return 1;
}

void initQueue(Queue* q, int n){
    q->v = (int*) malloc(n*sizeof(int));
    q->begin = 0;
    q->end = 0;
}

void initColorVec(int* vec, int n){
    int i;
    for(i=0; i<n; i++){
        vec[i] = -1;
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
