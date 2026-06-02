/*
    Questão 06:
    Dada uma string s, desenvolver uma função
    recursiva que determine se s é ou não um
    palíndromo.

*/
#include <stdio.h>
#include <string.h>

int ehPalindromo(char s1[], int inicio, int fim){
    if(inicio > fim){
        //printf("É um palindromo");
        return 1;
    }
    else{
        if(s1[inicio] != s1[fim]){
            //printf("NÃO é um palindromo");
            return 0 ;
        }
        else{
            return ehPalindromo(s1, inicio+1, fim-1);
        }
    }
    
}

int main(){
    char string[30] = {"osso"};
    int tam = strlen(string)                                                                                                                  
     - 1;
    
    int resp = ehPalindromo(string, 0, tam);
    
    switch(resp){
        case 0: 
            printf("NÃO é um palindromo");
        case 1:
            printf("É um palindromo");
    }
    
    return 0;
}


