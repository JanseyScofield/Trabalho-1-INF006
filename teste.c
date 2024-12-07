#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define tam_maximo_linha (1000)

typedef struct{
    char *pontoStr;
    float x;
    float y;
    double distanciaOrigem;
} Ponto;


float stringParaNumero(char *string);
double distanciaEntrePontos(Ponto a, Ponto b);
void inicializarPonto(char *stringPonto, Ponto *ponto);

int main(){

    // FILE *entrada = fopen("L0Q1.in", "r");
    // FILE *saida = fopen("L0Q1.out", "w");

    // if(entrada == NULL || saida == NULL){
    //     printf("Erro ao abrir os arquivos.");
    //     return 0;
    // }

    // char *linha = malloc(sizeof(char) * tam_maximo_linha);

    // while(fgets(linha, tam_maximo_linha, entrada) != NULL){
        
    // }

    // fclose(entrada);
    // fclose(saida);

    //char *strPonto = "(-13.4,-1)";
    //Ponto novoPonto;
    //inicializarPonto(strPonto, &novoPonto);
    char *num1Str = "1.2";
    char *num2Str = "-13.45";
    float num1, num2;
    num1 = stringParaNumero(num1Str);
    num2 = stringParaNumero(num2Str);
    
    printf("%f %f", num1, num2);
    // printf("Ponto : (%f, %f)\n", novoPonto.x, novoPonto.y);
    // printf("Distancia pra origem : %f", novoPonto.distanciaOrigem);
    // char *numS = "3";
    // float num = stringParaNumero(n);
    return 1;
}

float stringParaNumero(char *string){
    int iCont, tamString = strlen(string), tamSemSinal;
    float numero = 0;
    float base = 1;
    int casaPonto = -1;    

    iCont = 0;
    tamSemSinal = tamString;

    if(string[iCont] == '-'){
        iCont++;
        tamSemSinal--;
    }

    if(tamSemSinal > 1){
        while(iCont < tamString){
            if(string[iCont] == '.'){
                casaPonto = iCont;
                iCont++;
                continue;
            }

            base *= 10;
            iCont++;
        }

        if(casaPonto != -1){
            for(iCont = casaPonto + 1; iCont <= tamString; iCont++){
                base /= 10;
            }
        }
    }
    
    iCont = 0; 
    while(iCont < tamString){
        if(string[iCont] != '.' && string[iCont] != '-'){
            numero +=  string[0] == '-' ? ((string[iCont] - '0') * base) * -1.0 : (string[iCont] - '0') * base;
            base /= 10;
        }
        iCont++;
    } 

    return numero;
}
