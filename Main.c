#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int R;
    int G;
    int B;
} RGB;

RGB **lerArquivo(char nome[35], int *linhas, int *colunas) {
    // Caminho para a pasta de imagens
    char diretorio[] = "C:\\Users\\GOLD\\OneDrive\\Documentos\\T1_PBN\\imagens\\";
    char caminhoCompleto[100]; 
    strcpy(caminhoCompleto, diretorio); 
    strcat(caminhoCompleto, nome); 

    FILE *fp;
    fp = fopen(caminhoCompleto, "r");
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
    // Caminho para a pasta onde deseja salvar as imagens
    char diretorioSalvar[] = "C:\\Users\\GOLD\\OneDrive\\Documentos\\T1_PBN\\imagens\\";
    char caminhoCompleto[100]; 
    strcpy(caminhoCompleto, diretorioSalvar); 
    strcat(caminhoCompleto, nome); 

    FILE *fp;
    fp = fopen(caminhoCompleto, "w");
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

void maisBrilho(RGB **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            int r = matriz[i][j].R;
            int g = matriz[i][j].G;
            int b = matriz[i][j].B;
            int maisBR = (int)(r+60);
            int maisBG = (int)(g+60);
            int maisBB = (int)(b+60);
            matriz[i][j].R = maisBR;
            matriz[i][j].G = maisBG;
            matriz[i][j].B = maisBB;
        }
    }
}

void menosBrilho(RGB **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            int r = matriz[i][j].R;
            int g = matriz[i][j].G;
            int b = matriz[i][j].B;
            int maisBR = (int)(r-60);
            int maisBG = (int)(g-60);
            int maisBB = (int)(b-60);
            matriz[i][j].R = maisBR;
            matriz[i][j].G = maisBG;
            matriz[i][j].B = maisBB;
        }
    }
}

void maisVelha(RGB **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            int r = matriz[i][j].R;
            int g = matriz[i][j].G;
            int b = matriz[i][j].B;
            int maisBR = (int)(r-20);
            int maisBG = (int)(g-20);
            int maisBB = (int)(b-20);
            matriz[i][j].R = maisBR;
            matriz[i][j].G = maisBG;
            matriz[i][j].B = maisBB;
        }
    }
}

void negativo(RGB **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            int r = matriz[i][j].R;
            int g = matriz[i][j].G;
            int b = matriz[i][j].B;
            int negR = (int)(255 - r);
            int negG = (int)(255 - g);
            int negB = (int)(255 - b);
            matriz[i][j].R = negR;
            matriz[i][j].G = negG;
            matriz[i][j].B = negB;
        }
    }
}

void rotaciona(RGB ***matriz, int *linhas, int *colunas){
    // Transpor a matriz
    RGB **transposta = (RGB **)malloc(*colunas * sizeof(RGB *));
    for (int i = 0; i < *colunas; i++) {
        transposta[i] = (RGB *)malloc(*linhas * sizeof(RGB));
        for (int j = 0; j < *linhas; j++) {
            transposta[i][j] = (*matriz)[j][i];
        }
    }
    // Inverter cada linha da matriz transposta
    for (int i = 0; i < *colunas; i++) {
        for (int j = 0; j < *linhas / 2; j++) {
            RGB temp = transposta[i][j];
            transposta[i][j] = transposta[i][*linhas - j - 1];
            transposta[i][*linhas - j - 1] = temp;
        }
    }
    // Liberar a memória da matriz original
    for (int i = 0; i < *linhas; i++) {
        free((*matriz)[i]);
    }
    free(*matriz);
    // Atualizar as dimensões da matriz
    int temp = *linhas;
    *linhas = *colunas;
    *colunas = temp;
    // Atribuir a matriz transposta à matriz original
    *matriz = transposta;
}


int main() {
    char nomeArquivo[25], nomeArquivoNovo[25];
    int opcao, linhas, colunas; 
    RGB **matriz = NULL;

    printf("\nOla, seja bem vindo ao editor de fotos");
    printf("\nEstas sao as nossas imagens iniciais disponiveis para edicao:");
    printf("\n    1 - BTS.ppm");
    printf("\n    2 - Enner.ppm");
    printf("\n    3 - Fernandao.ppm");
    printf("\n    4 - Futebol.ppm");
    
    do {
        printf("\nDigite o nome da foto que voce quer editar ou 'exit' para sair!\n");
        scanf("%s", nomeArquivo);

        if (strcmp(nomeArquivo, "exit") == 0) {
            return 0; // Encerra o programa se o usuário digitar 'exit'
        }

        matriz = lerArquivo(nomeArquivo, &linhas, &colunas);
        if (matriz == NULL) {
            printf("Erro ao ler o arquivo.\n");
            return 1;
        }

        do {
            printf("\nQue edicao voce quer realizar?");
            printf("\n    1 - Gerar uma imagem tons de cinza");
            printf("\n    2 - Imagem tons de cinza -  gerar imagem negativa");
            printf("\n    3 - Imagem tons de cinza - aumentar o brilho");
            printf("\n    4 - Imagem tons de cinza - diminuir o brilho");
            printf("\n    5 - Rotacionar a imagem colorida -90");
            printf("\n    6 - Imagem colorida - envelhecimento da imagem");
            printf("\n    7 - Voltar e escolher outra imagem.");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    viraCinza(matriz, linhas, colunas);
                    break;
                case 2:
                    negativo(matriz, linhas, colunas);
                    break;
                case 3:
                    maisBrilho(matriz, linhas, colunas);
                    break;
                case 4:
                    menosBrilho(matriz, linhas, colunas);
                    break;
                case 5:
                    rotaciona(&matriz, &linhas, &colunas);
                    break;
                case 6:
                    maisVelha(matriz, linhas, colunas);
                    break;
                case 7:
                    break;
                default:
                    printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
                    continue; // Voltar ao início do loop interno para pedir uma nova opção válida
            }

            if (opcao != 7) {
                printf("Qual o nome vc quer dar ao arquivo? Adicione o .ppm no fim.\n");
                scanf("%s", nomeArquivoNovo);
                salvarArquivoPPM(nomeArquivoNovo, matriz, linhas, colunas);
                printf("Imagem editada salva como '%s'.\n", nomeArquivoNovo);
            }

        } while (opcao != 7);

        // Liberar memória alocada para a matriz
        for (int i = 0; i < linhas; i++) {
            free(matriz[i]);
        }
        free(matriz);

    } while (1); // Loop infinito até que o usuário deseje sair

    return 0;
}