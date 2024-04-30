#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int R;
    int G;
    int B;
} RGB;

RGB **lerArquivo(char nome[16], int *linhas, int *colunas) {
    // Abrir o arquivo
    FILE *fp;
    fp = fopen(nome, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char formato[3];
    fscanf(fp, "%s", formato); // lê o tipo de imagem P3 (color), P2 (P&B) 
    if (formato[0] != 'P' || (formato[1] != '3' && formato[1] != '2')) {
        printf("Formato de arquivo inválido.\n");
        fclose(fp);
        return NULL;
    }

    fscanf(fp, "%d %d", colunas, linhas); // lê o tamanho da matriz  
    
    // Criar uma matriz para armazenar os pixels como uma sequência de structs RGB
    RGB **matriz = (RGB **)malloc(*linhas * sizeof(RGB *));
    if (matriz == NULL) {
        printf("Erro ao alocar memoria para a matriz.\n");
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < *linhas; i++) {
        matriz[i] = (RGB *)malloc(*colunas * sizeof(RGB));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memoria para a linha %d.\n", i);
            // Liberar memória alocada anteriormente
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            fclose(fp);
            return NULL;
        }
    }

    int valor;
    fscanf(fp, "%d", &valor); // lê o valor máximo 

    // Ler os pixels da imagem
    for (int j = 0; j < *linhas; j++) {
        for (int i = 0; i < *colunas; i++) {  	
            fscanf(fp, "%d %d %d", &matriz[j][i].R, &matriz[j][i].G, &matriz[j][i].B);
        }
    }

    fclose(fp);
    return matriz;
}

void salvarArquivoPPM(char nome[], RGB **matriz, int linhas, int colunas) {
    FILE *fp;
    fp = fopen(nome, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    // Escrever o cabeçalho do arquivo PPM
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", colunas, linhas);
    fprintf(fp, "255\n");

    // Escrever os pixels da imagem em formato PPM
    for (int j = 0; j < linhas; j++) {
        for (int i = 0; i < colunas; i++) {
            // Garantir que os valores RGB estejam no intervalo de 0 a 255
            int r = matriz[j][i].R;
            int g = matriz[j][i].G;
            int b = matriz[j][i].B;
            if (r < 0) r = 0; else if (r > 255) r = 255;
            if (g < 0) g = 0; else if (g > 255) g = 255;
            if (b < 0) b = 0; else if (b > 255) b = 255;

            // Escrever os valores RGB formatados corretamente
            fprintf(fp, "%d\n%d\n%d\n", r, g, b);
        }
    }

    fclose(fp);
}

void viraCinza(RGB **matriz, int linhas, int colunas) {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            int r = matriz[i][j].R;
            int g = matriz[i][j].G;
            int b = matriz[i][j].B;
            int cinza = (int)(r * 0.30 + g * 0.59 + b * 0.11);
            matriz[i][j].R = cinza;
            matriz[i][j].G = cinza;
            matriz[i][j].B = cinza;
        }
    }
}

void viraVelha(RGB **matriz, int linhas, int colunas){
    


}

int main() {
    printf("Me diga o nome do arquivo:\n");
    printf("Arquivo disponivel - 'fernandaoPBN.ppm'\n");
    char nomeArquivo[16];
    scanf("%s", nomeArquivo);
    
    int linhas, colunas;
    RGB **matriz = lerArquivo(nomeArquivo, &linhas, &colunas);
    if (matriz == NULL) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    // Aplicar filtro de escala de cinza
    viraCinza(matriz, linhas, colunas);

    // Salvar a imagem em escala de cinza em um novo arquivo PPM
    char nomeArquivoCinza[20];
    printf("Qual o nome vc quer dar ao arquivo cinza? adicione o .ppm no fim\n");
    scanf("%s", nomeArquivoCinza);
    salvarArquivoPPM(nomeArquivoCinza, matriz, linhas, colunas);
    printf("Imagem em escala de cinza salva como '%s'.\n", nomeArquivoCinza);

    // Liberar a memória alocada para a matriz
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
