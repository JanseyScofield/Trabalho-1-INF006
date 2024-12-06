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

#pragma region Utils
int checarTipo(char *string);
float stringParaNumero(char *string);
#pragma endregion

#pragma region Pontos
double distanciaEntrePontos(Ponto a, Ponto b);
void inicializarPonto(char *stringPonto, Ponto *ponto);
#pragma endregion

#pragma region Sorts
void ordenarInts(int *array, int n);
void ordenarFloats(float *array, int n);
void ordenarPontos(Ponto *array, int n);
#pragma endregion

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

    char *strPonto1 = "(-13.4,-1)";
    Ponto novoPonto1;
    inicializarPonto(strPonto1, &novoPonto1);

    char *strPonto2 = "(4,12.5)";
    Ponto novoPonto2;
    inicializarPonto(strPonto2, &novoPonto2);

    char *strPonto3 = "(-13.4,10)";
    Ponto novoPonto3;
    inicializarPonto(strPonto3, &novoPonto3);

    Ponto array[] = {novoPonto1, novoPonto2, novoPonto3};
    for(int i = 0; i < 3; i++){
        for(int j =0; j < strlen(array[i].pontoStr); j++){
            printf("%c", array[i].pontoStr[j]);
        }
        printf(" ");
    }
    printf("\n");
    ordenarPontos(array, 3);
    for(int i = 0; i < 3; i++){
        for(int j =0; j < strlen(array[i].pontoStr); j++){
            printf("%c", array[i].pontoStr[j]);
        }
        printf(" ");
    }
    printf("\n");
    return 1;
}

int checarTipo(char *string){
    int iCont;

    for(iCont = 0; iCont < strlen(string); iCont++){
        if(string[iCont]  == '('){
            return 1; // É um ponto
        }
        if(string[iCont] >= 'A' && string[iCont] <= 'z'){
            return 2; // É uma string
        }
        if(string[iCont] == '.'){
            return 3; // É um float
        }
    }
    return 4; // É um inteiro
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
    }
  
    iCont++;
    jCont = 0;
    while(stringPonto[iCont] != ')'){
        stringY[jCont] = stringPonto[iCont];
        iCont++;
        jCont++;
    }
    ponto->x = stringParaNumero(stringX);
    ponto->y = stringParaNumero(stringY);
    ponto->distanciaOrigem = ponto->x < 0? distanciaEntrePontos(*ponto, origem) * -1 : distanciaEntrePontos(*ponto, origem);
}


void ordenarInts(int *array, int n){
    int iCont, jCont;
    int key;

    for(iCont = 1; iCont < n; iCont++){
        key = array[iCont];
        jCont = iCont - 1;

        while(array[jCont] > key &&  jCont >=0){
            array[jCont + 1] = array[jCont];
            jCont--;
        }

        array[jCont + 1] = key;
    }
}

void ordenarFloats(float *array, int n){
    int iCont, jCont;
    float key;

    for(iCont = 1; iCont < n; iCont++){
        key = array[iCont];
        jCont = iCont - 1;

        while(array[jCont] > key &&  jCont >=0){
            array[jCont + 1] = array[jCont];
            jCont--;
        }

        array[jCont + 1] = key;
    }
}

void ordenarPontos(Ponto *array, int n){
    int iCont, jCont;
    Ponto key;

    for(iCont = 1; iCont < n; iCont++){
        key = array[iCont];
        jCont = iCont - 1;

        while(array[jCont].distanciaOrigem > key.distanciaOrigem && jCont >=0){
            array[jCont + 1] = array[jCont];
            jCont--;
        }

        array[jCont + 1] = key;
    }
}