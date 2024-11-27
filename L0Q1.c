#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_MAX_LINHA 1000

typedef struct{
    char *coordenadaPonto;
    float distanciaOrigem;
} Ponto;

int main(){
    // Armazenando os arquivos de entrada e saida em variaveis:
    FILE *entrada = fopen("L0Q1.in", "r");
    FILE *saida = fopen("L0Q1.out", "w");

    // Validando se foi possivel acessa-los:
    if(entrada == NULL || saida == NULL){
        printf("Nao foi possivel carregar os arquivos de entrada e saida.\n");
        return 0;
    }
    //Escrevendo o conteudo de um arquivo no outro:
    char *linha = malloc(TAM_MAX_LINHA * sizeof(char));

    while(fgets(linha, TAM_MAX_LINHA,  entrada) != NULL){
        fputs(linha, saida);
    }

    fclose(entrada);
    fclose(saida);

    return 1;
}