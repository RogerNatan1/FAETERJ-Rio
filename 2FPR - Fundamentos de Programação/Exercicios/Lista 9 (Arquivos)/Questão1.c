#include <stdio.h>
#include <string.h>

int contaCaracter(char nomeArq[]){
    FILE *arq;
    int contador = 0;
    char ch; 
    
    arq = fopen(nomeArq, "r");
    if(arq == NULL){
        fclose(arq);
        return 0;
    }
    else{
        while(fscanf(arq, "%c", &ch) != EOF){
            if(ch != NULL){
                contador++;
            }
        }   
    }
    fclose(arq);
    return contador;
}

int main(){
    char nomeArquivo[30];
    int resultado;
    
    printf("Digite o nome do arquivo: ");
    gets (nomeArquivo);
    
    resultado = contaCaracter(nomeArquivo);
    
    if(!resultado){
        printf("A quantidade de caracteres na palavra é de: %d", resultado);
    }
    else{
        printf("ERROR: Não foi possivel ler o arquivo!");
    }
    
    return 0;
}
