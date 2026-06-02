/*
    Questão 05:
    Pede-se a implementação de uma função
    recursiva que exiba os n primeiros termos de
    uma PG (Progressão Geométrica), onde a1 é o
    seu primeiro termo e q a razão.
*/

#include <stdio.h>

void exibePG(int a1, int q, int n){
    if(n > 0){
        printf("%d ", a1);
        exibePG(a1 * q, q, n-1);
    }
}

int main(){
    
    exibePG(1, 2, 10);
    
    return 0;
}
