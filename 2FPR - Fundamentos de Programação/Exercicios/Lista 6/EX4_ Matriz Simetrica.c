#include <stdio.h>

int defineSimetrica(int ordem, int matriz[][ordem]){
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j< ordem; j++){
            if(matriz[i][j] != matriz[j][i]){
                return 0;
            }
        }
    }
    return 1;
}
int main()
{
    int matriz[3][3] = {{1,2,3}, {2,5,8}, {3,8,4}};
    
    if(defineSimetrica(3, matriz) != 0){
        printf("A matriz é simetrica!");
    }
    else{
        printf("A matriz NÃO é simetrica!");
    }

    return 0;
}
