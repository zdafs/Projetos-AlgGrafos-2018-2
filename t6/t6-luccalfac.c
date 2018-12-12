/*
    Nome: Lucca La Fonte Albuquerque Carvalho
    RA: 726563
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** montaMatriz(int);
char isArbitragem(double**, int);

int main(){
    double** m;
    int n;

    scanf("%d", &n);
    while(n!=0){
        m = montaMatriz(n);
        printf("%c\n", isArbitragem(m, n));
        for(int i=0; i<n; i++)
            free(m[i]);
        free(m);
        scanf("%d", &n);
    }
}

double** montaMatriz(int n){
    double num;
    double** m;
    m = (double**) malloc(n*sizeof(double*));
    for(int i=0; i<n; i++)
        m[i] = (double*) malloc(n*sizeof(double));

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%lf", &num);
            m[i][j] = -log(num);
        }
    }

    return m;
}

char isArbitragem(double** m, int n){
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(m[i][j] > m[i][k] + m[k][j])
                    m[i][j] = m[i][k] + m[k][j];
            }
        }
    }

    for(int i=0; i<n; i++){
        if(m[i][i]<0)
            return 'S';
    }

    return 'N';
}
