/*
    Questão 08:
    Desenvolver uma função recursiva que, dada
    uma string, exiba-a invertida.
*/
#include <stdio.h>
#include <string.h>

void exibeInversa(char s1[],int j){
    if(j >= 0){
        printf("%c", s1[j]);
        exibeInversa(s1, j-1);
    }
}

int main(){
    char string[30] = {"FAETERJ"};
    int tam = strlen(string) - 1;
    exibeInversa(string, tam);
    
    return 0;
}