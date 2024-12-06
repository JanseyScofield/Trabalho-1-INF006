#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define tam_maximo_linha (1000)

typedef struct{
    char *pontoStr;
    float x;
    float y;#include <stdio.h>
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
    char *num1Str = "-1";
    char *num2Str = "13.4";
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
    int iCont, tamString = strlen(string);
    float numero = 0;
    float base = 1;
    int casaPonto = -1;    

    iCont = string[0] == '-'? 2 : 1;
    while(iCont <= tamString){
        if(string[iCont] == '.'){
            casaPonto = iCont;
            iCont++;
            continue;
        }
        
        base *= 10;
        iCont++;
    }

    //printf("Casa ponto : %d", casaPonto);
    if(casaPonto != -1){
        for(iCont = casaPonto + 1; iCont <= tamString; iCont++){
            base /= 10;
        }
    }

    //printf("Base %f", base);
    iCont = string[0] == '-'? 1 : 0;
    while(iCont < tamString){
        if(string[iCont] != '.'){
            numero += (string[iCont] - '0') * base;
            base /= 10;
        }
        iCont++;
    } 

    return numero;
}

double distanciaEntrePontos(Ponto a, Ponto b){
    double quadradoDistancia = pow((b.x - a.x), 2) + pow((b.y - a.y), 2);
    return sqrt(quadradoDistancia);
}

void inicializarPonto(char *stringPonto, Ponto *ponto){
    int iCont, jCont;
    Ponto origem;
    origem.x = 0;
    origem.y = 0;

    ponto->pontoStr = stringPonto;
    char *stringX = malloc(sizeof(char) * (strlen(stringPonto) - 3));
    char *stringY = malloc(sizeof(char) * (strlen(stringPonto) - 3));

    for(iCont = 1, jCont = 0; stringPonto[iCont] != ','; iCont++, jCont++){
        stringX[jCont] = stringPonto[iCont];
        printf("%c ", stringX[jCont]);
    }

    // for(int i = 0; i < strlen(stringX); i++){
    //     printf("%c ", stringX[i]);
    // }
    iCont++;
    jCont = 0;
    while(stringPonto[iCont] != ')'){
        stringY[jCont] = stringPonto[iCont];
        iCont++;
        jCont++;
    }

    ponto->x = stringParaNumero(stringX);
    ponto->y = stringParaNumero(stringY);
    ponto->distanciaOrigem = distanciaEntrePontos(*ponto, origem);
}
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

    char *strPonto = "(-13.4,-1)";
    Ponto novoPonto;
    inicializarPonto(strPonto, &novoPonto);

    printf("Ponto : (%f, %f)\n", novoPonto.x, novoPonto.y);
    printf("Distancia pra origem : %f", novoPonto.distanciaOrigem);
    // char *numS = "3";
    // float num = stringParaNumero(n);
    // return 1;
}

float stringParaNumero(char *string){
    int iCont, tamString = strlen(string);
    float numero = 0;
    float base = 1;
    int casaPonto = -1;    

    for(iCont = 1; iCont <= tamString; iCont++){
        if(string[iCont] == '.'){
            casaPonto = iCont;
            continue;
        }
        base *=10;
    }

    if(string[0] == '-'){
        base *= -1;
    }

    printf("Casa ponto : %d", casaPonto);
    if(casaPonto != -1){
        for(iCont = casaPonto + 1; iCont < tamString; iCont++){
            base /= 10; printf("Base %f\n", base);
        }
    }

    printf("Base %f", base);

    for(iCont = 0 ; iCont < tamString; iCont++){
        if(string[iCont] != '.'){
            numero += (string[iCont] - '0') * base;
            base /= 10;
        }
    } 

    return numero;
}

double distanciaEntrePontos(Ponto a, Ponto b){
    double quadradoDistancia = pow((b.x - a.x), 2) + pow((b.y - a.y), 2);
    return sqrt(quadradoDistancia);
}

void inicializarPonto(char *stringPonto, Ponto *ponto){
    int iCont, jCont;
    Ponto origem;
    origem.x = 0;
    origem.y = 0;

    ponto->pontoStr = stringPonto;
    char *stringX = malloc(sizeof(char) * (strlen(stringPonto) - 3));
    char *stringY = malloc(sizeof(char) * (strlen(stringPonto) - 3));

    for(iCont = 1, jCont = 0; stringPonto[iCont] != ','; iCont++, jCont++){
        stringX[jCont] = stringPonto[iCont];
        printf("%c ", stringX[jCont]);
    }

    // for(int i = 0; i < strlen(stringX); i++){
    //     printf("%c ", stringX[i]);
    // }
    iCont++;
    jCont = 0;
    while(stringPonto[iCont] != ')'){
        stringY[jCont] = stringPonto[iCont];
        iCont++;
        jCont++;
    }

    ponto->x = stringParaNumero(stringX);
    ponto->y = stringParaNumero(stringY);
    ponto->distanciaOrigem = distanciaEntrePontos(*ponto, origem);
}
