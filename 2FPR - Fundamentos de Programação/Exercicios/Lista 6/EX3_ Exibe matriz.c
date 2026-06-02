#include <stdio.h>

void exibeMatriz(int lin, int col, int matriz[][col]){
    int i,j;
    for(i = 0; i < lin; i++){
        printf("|");
        for(j = 0; j < col; j++){
            printf("%6d", matriz[i][j]);
        }
        printf("|");
        printf("\n");
    }
}

int main(){
    int matriz[3][3] = {{3,2,1}, 
                        {4,5,6}, 
                        {9,8,7}};
    
    exibeMatriz(3,3,matriz);
    
    
    
    return 0;
}