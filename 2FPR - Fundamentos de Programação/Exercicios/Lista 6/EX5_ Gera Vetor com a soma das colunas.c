#include <stdio.h>
void zera(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        vetor[i] = 0;
    }
}
void geraVetor(int linha, int coluna, int matriz[linha][coluna], int vetor[coluna]){
    int i, j;
    for(i = 0; i < coluna; i++){
        for(j = 0; j < linha; j++){
            vetor[j] += matriz[i][j];
        }
    }
}
int main()
{
    int matriz[3][3] = {{1,2,3}, 
                        {4,5,6}, 
                        {7,8,9}};
    int vetor[3]; 
    zera(vetor, 3);
    
    geraVetor(3, 3, matriz, vetor);
    
    printf("Soma das colunas: ");
    for(int i = 0; i < 3; i++){
        printf("| %d |", vetor[i]);
    }
    
    
    
    return 0;
}
