/*
    ALUNO: Roger Natan da Silva Porto
    ALUNO: João Pedro De Britto Araújo
    ATIVIDADE 2, 2FPR NOITE

    Dadas uma matriz Mmxn e uma coluna col,
    desenvolver uma função que desloque todos os
    elementos da coluna col para a última coluna
    da matriz.
    Consequentemente, as colunas col+1 à última
    deverão serão deslocadas uma posição para a
    esquerda, conforme ilustrado no exemplo
    abaixo:
*/
#include <stdio.h>

// Exibe a mtriz com uma formatação 'bonitinha'
void exibeMatriz(int lin, int col, int matriz[lin][col]){
    for(int i = 0; i < lin; i++){
        printf("| ");
        for(int j = 0; j < col; j++){
            printf("%2d", matriz[i][j]);
        }
        printf(" |");
        printf("\n");
    }
    printf("\n\n");
}

// Armazena a coluna escolhida em um vetor auxiliar 
// Joga todas as colunas seguites 1 casa para a esquerda
// No fim cola o vetor na ultima coluna para finalziar  
int deslocaCol(int lin, int col, int matriz[lin][col], int colunaE) {
    if(colunaE > col - 1){
        return 0;
    }
    else {
        // Um único laço para percorrer cada linha da matriz
        for(int i = 0; i < lin; i++){
            
            // 1. Salva apenas o elemento da linha atual (O(1) de memória)
            int aux = matriz[i][colunaE]; 
            
            // 2. Desloca os elementos restantes dessa mesma linha para a esquerda
            for(int j = colunaE + 1; j < col; j++){
                matriz[i][j - 1] = matriz[i][j];
            }
            
            // 3. Joga o elemento salvo para a última coluna desta linha
            matriz[i][col - 1] = aux;
        }
    }
    return 1;
}
int main(){
    int matriz[5][6] = {
        {1, 5, 7, 1, 4, 6},
        {6, 2, 1, 4, 7, 7},
        {3, 6, 9, 7, 0, 1},
        {2, 4, 5, 7, 2, 4},
        {2, 4, 8, 9, 1, 2} 
    };
    
    exibeMatriz(5, 6, matriz);
    if(deslocaCol(5, 6, matriz, 5)){ // matriz com numero invalido para teste
        printf("=== MATRIZ APÓS A TROCA ===\n");
        exibeMatriz(5, 6, matriz);
    }
    else{
        printf("ERRO: O número da COLUNA selecionado é inválido.");
    }

    return 0;
}