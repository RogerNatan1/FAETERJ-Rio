/*
  Questão 03:
    Desenvolver uma função recursiva que exiba
    todos os múltiplos do número N, inferiores ou
    iguais ao valor V.
    
*/

#include <stdio.h>

void exibeMultiplos(int n, int v, int i){
    if(i <= v){
        printf("%d ", i);
        return exibeMultiplos(n, v, i+n);
    }
}

int main(){
    
    exibeMultiplos(4, 25, 0);
    
    return 0;
}
