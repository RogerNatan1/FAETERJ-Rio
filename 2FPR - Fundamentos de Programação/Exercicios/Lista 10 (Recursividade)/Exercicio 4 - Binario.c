/*
    Questão 04:
    Fazer uma função recursiva que, dado um
    número inteiro N, exiba o mesmo na base 2
    (binária).

*/
#include <stdio.h>

void exibeBinario(int n){
    if(n > 0){
        exibeBinario(n / 2);
        printf("%d ", n%2);
    } 
}
int main(){
    
    exibeBinario(28);
    
    return 0;
}


