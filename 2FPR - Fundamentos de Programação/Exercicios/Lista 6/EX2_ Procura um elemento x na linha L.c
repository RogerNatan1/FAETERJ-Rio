#include <stdio.h>


int procuraElemento(int lin, int col, int matriz[lin][col], int elemento, int linha){
    int i,j = linha - 1;
    for(i = 0; i < col; i++){
        if(elemento == matriz[j][i]){
            return 1;
        }
    }
    return 0;
}
int main(){
    int matriz[3][3] = {{1,2,3}, 
                        {4,5,6}, 
                        {7,8,9}};
    
    if(procuraElemento(3,3,matriz,6,2) != 0){
        printf("O número foi encontrado!");
    }
    else{
        printf("O número NÃO foi encontrado!");
    }
    
    return 0;
}