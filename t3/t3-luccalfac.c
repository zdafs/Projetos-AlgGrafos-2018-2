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

typedef struct {
  int* v;
  int top;
} Stack;

AdjList* genGraph(int, int);
void initAdjListVec(AdjList*, int);
void addToAdjList(AdjList*, int, int);
void initAdjVertex(AdjVertex*, int);
void freeGraph(AdjList*, int);
int isConnected(AdjList*, int);
void initStack(Stack*, int);
int DFS(AdjList*, int, Stack*);
void initVecColor(int*, int);
void DFSaux(AdjList*, int, Stack*, int*);
int stackIsEmpty(Stack*);
int pop(Stack*);
void push(Stack*, int);


int main(){
  int n, m;
  AdjList* adjListVec;

  scanf("%d %d", &n, &m);
  while(n!=0 ||m!=0 ){
    adjListVec = genGraph(n, m);
    printf("%d\n", isConnected(adjListVec, n));
    freeGraph(adjListVec, n);
    scanf("%d %d", &n, &m);
  }
}

AdjList* genGraph(int n, int m){
  AdjList* adjListVec;
  int u, v, p;

  adjListVec = (AdjList *) malloc(n*sizeof(AdjList));
  initAdjListVec(adjListVec, n);
  while(m>0){
    scanf("%d %d %d", &u, &v, &p);
    addToAdjList(adjListVec, u-1, v-1);
    if(p==2)
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

int isConnected(AdjList* adjVec, int n){
  AdjList* adjVecT;
  Stack* p = (Stack*) malloc(sizeof(Stack));

  initStack(p, n);//sei nao em
  DFS(adjVec, n, p);
  adjVecT = (AdjList *) malloc(n*sizeof(AdjList));
  initAdjListVec(adjVecT, n);
  for(int i=0; i<n; i++){
    AdjVertex* aux = adjVec[i].head;
    while(aux!=NULL){
      addToAdjList(adjVecT, aux->id, i);
      aux = aux->prox;
    }
  }
  if(DFS(adjVecT, n, p)>1)
    return 0;
  return 1;
}

void initStack(Stack* p, int n){
  p->v = (int*) malloc(n*sizeof(int));
  p->top = -1;
}

int DFS(AdjList* adjVec, int n, Stack* p){
  int* vecColor = (int*) malloc(n*sizeof(int));
  int count = 0;

  initVecColor(vecColor, n);
  if(stackIsEmpty(p)){
    for(int i=0; i<n; i++){
      if(vecColor[i]==-1){
        DFSaux(adjVec, i, p, vecColor);
        count++;
      }
    }
  }
  else{
    while(!stackIsEmpty(p)){
      int vertexIndex = pop(p);
      if(vecColor[vertexIndex]==-1){
        DFSaux(adjVec, vertexIndex, NULL, vecColor);
        count++;
      }
    }
  }

  return count;
}

void initVecColor(int* vecColor, int n){
  for(int i=0; i<n; i++)
    vecColor[i] = -1;
}

void DFSaux(AdjList* adjVec, int u, Stack* p, int* vecColor){
  AdjVertex* vertex;

  vecColor[u] = 0;
  vertex = adjVec[u].head;
  while(vertex!=NULL){
    if(vecColor[vertex->id]==-1)
      DFSaux(adjVec, vertex->id, p, vecColor);
    vertex = vertex->prox;
  }
  vecColor[u] = 1;
  if(p!=NULL)
    push(p, u);
}

int stackIsEmpty(Stack* p){
  return(p->top==-1?1:0);
}

int pop(Stack* p){
  int res = p->v[p->top];
  p->top = p->top - 1;
  return res;
}

void push(Stack* p, int u){
  p->top = p->top + 1;
  p->v[p->top] = u;
}
