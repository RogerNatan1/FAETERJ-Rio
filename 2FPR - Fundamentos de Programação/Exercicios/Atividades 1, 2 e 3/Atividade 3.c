#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char letra;
    int contador;
} TOcorrencia;

// Compara a palavra recebida com um vetor do struct
// Joga as letras que estão de fora para dentro do struct
// E faz a contabilidade de quantas vezes cada uma aparece
int contaOcorrencia(TOcorrencia ocorrencia[], char string[]){
    int contaD = 0;
    for(int i = 0; string[i]; i++){
        int encontrado = 0;
        for(int j = 0; j < contaD && !encontrado; j++){
            if(string[i] == ocorrencia[j].letra){
                ocorrencia[j].contador++;
                encontrado = 1;
            }
        }
        if(!encontrado){
            ocorrencia[contaD].letra = string[i];
            ocorrencia[contaD].contador = 1;
            contaD++;
        }
    }
    return contaD;
}

// Após montar o struct ser montado, aqui ele é organizado
// Comparando letra por letra para deixa-lô em ordem alfabetica
void ordenaStruct(TOcorrencia ocorrencias[], int tamF){
    for(int i = 0; i < tamF - 1; i++){
        for(int j = 0; j < tamF - 1 - i; j++){
            // Utilização da biblioteca 'ctype.h' para deixar as letras minusculas na comparação
            if(tolower(ocorrencias[j].letra) > tolower( ocorrencias[j+1].letra)){ 
                TOcorrencia aux = ocorrencias[j];
                ocorrencias[j] = ocorrencias[j + 1];
                ocorrencias[j + 1] = aux;
            }
        }
    }
}
int main(){
    TOcorrencia ocorrencias[50];
    char palavra[120] = "EDCBA";
    int tamFinal = contaOcorrencia(ocorrencias, palavra);

    ordenaStruct(ocorrencias, tamFinal);

    printf("Palavra: %s\n", palavra);
    for(int i = 0; i < tamFinal; i++){
        printf("Letra: %2c | Quantidade: %2d\n", ocorrencias[i].letra, ocorrencias[i].contador);
    }

    return 0;
}
