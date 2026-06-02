/*
    ALUNO: Roger Natan da Silva Porto
    ALUNO: João Pedro De Britto Araújo
    ATIVIDADE 1, 2FPR NOITE
*/

#include <stdio.h>
#include <string.h>

void substituiString(int posI, int posF, char stringOri[], char stringSub[]){
    int tamStringOri = strlen(stringOri); // Tamanho da string original
    int tamStringSub = strlen(stringSub); // Tamanho da String substituta
    int tamStringAlvo = posF - posI + 1; // Calculo para saber qual o tamanho da palavra que irá sair
    int dif = tamStringSub - tamStringAlvo; // Calcula a diferença de tamamho das strings (para aumenatar o array)

    // Usa o tamanho da string origial + a diferença para "criar" o tamanho suficiente
    for(int i = tamStringOri; i > posF; i--){
        stringOri[i + dif] = stringOri[i]; 
    }
    // Encaixa a nova string no buraco criado
    for(int i = 0; i < tamStringSub; i++){
        stringOri[posI + i] = stringSub[i];
    }
}
int main(){
    char stringOri[50] = "e ai, vc vem?";
    char stringSub[] = "";

    printf("%s\n\n", stringOri);
    substituiString(5, 5, stringOri, stringSub);
    printf("%s", stringOri);

    return 0;
}
