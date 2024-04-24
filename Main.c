#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int R;
    int G;
    int B;
} RBG;

int main(){
    int linhas = 1280,  colunas = 852;
    int **matriz = (int **)malloc(sizeof(int *));

    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }


    return 0;
}