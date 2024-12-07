#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define tam_maximo_linha (1000)
#define qtd_itens_tipo (200)
#pragma region Structs
typedef struct{
    char *pontoStr;
    float x;
    float y;
    double distanciaOrigem;
} Ponto;

typedef struct{
    int *arrayInts;
    int n; 
} IntsLinha;

typedef struct{
    float *arrayFloats;
    int n; 
} FloatsLinha;

typedef struct{
    Ponto *arrayPontos;
    int n; 
} PontosLinha;

typedef struct{
    char **arrayStrings;
    int n; 
} StringsLinha;
#pragma endregion

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
void ordernarListaPalavras(char **array, int n);
#pragma endregion

#pragma region Prints
void escreverPontos(Ponto *pontos, int n, FILE *arquivoSaida);
void escreverStrings(char **strings, int n, FILE *arquivoSaida);
void escreverFloats(float *listaFloats, int n, FILE *arquivoSaida);
void escreverInts(int *listaInts, int n, FILE *arquivoSaida);
#pragma endregion

int main(){
    FILE *entrada = fopen("L0Q2.in", "r");
    FILE *saida = fopen("L0Q2.out", "w");

    if(entrada == NULL || saida == NULL){
        printf("Erro ao abrir os arquivos.");
        return 0;
    }

    char *linha = malloc(sizeof(char) * tam_maximo_linha);

    while(fgets(linha, tam_maximo_linha, entrada) != NULL){
        int iCont, jCont, kCont, tipoAtual;
        int tamanhoStringAtual;

        PontosLinha pontosLista;
        pontosLista.arrayPontos = malloc(sizeof(Ponto) * qtd_itens_tipo);
        pontosLista.n = 0;

        StringsLinha stringLinha;
        stringLinha.arrayStrings = malloc(sizeof(char*) * qtd_itens_tipo);
        stringLinha.n = 0;

        FloatsLinha floatsLinha;
        floatsLinha.arrayFloats = malloc(sizeof(float) * qtd_itens_tipo);
        floatsLinha.n = 0;

        IntsLinha intsLinha;
        intsLinha.arrayInts = malloc(sizeof(int) * qtd_itens_tipo);
        intsLinha.n = 0;

        int inicio = 0, fim = 0, tamanho;
        while (linha[fim] != '\0') {
            while (linha[fim] != ' ' && linha[fim] != '\n' && linha[fim] != '\0') {
                fim++;
            }

            tamanho = fim - inicio;

            if (tamanho > 0) {
                char *stringAtual = malloc((tamanho + 1) * sizeof(char));
                for(kCont = 0; kCont < tamanho; kCont++){
                    stringAtual[kCont] = linha[inicio + kCont];
                }
                stringAtual[tamanho] = '\0';

                int tipoAtual = checarTipo(stringAtual);

                switch (tipoAtual) {
                    case 1: {
                        Ponto novoPonto;
                        inicializarPonto(stringAtual, &novoPonto);
                        pontosLista.arrayPontos[pontosLista.n++] = novoPonto;
                        break;
                    }
                    case 2:
                        stringLinha.arrayStrings[stringLinha.n++] = stringAtual;
                        break;
                    case 3:
                        floatsLinha.arrayFloats[floatsLinha.n++] = stringParaNumero(stringAtual);
                        free(stringAtual);
                        break;
                    case 4:
                        intsLinha.arrayInts[intsLinha.n++] = (int)stringParaNumero(stringAtual);
                        free(stringAtual);
                        break;
                }
            }
            
            while (linha[fim] == ' ' || linha[fim] == '\n') {
                fim++;
            }
            inicio = fim;
        }

        ordernarListaPalavras(stringLinha.arrayStrings, stringLinha.n);
        ordenarInts(intsLinha.arrayInts, intsLinha.n);
        ordenarFloats(floatsLinha.arrayFloats, floatsLinha.n);
        ordenarPontos(pontosLista.arrayPontos, pontosLista.n);

        escreverStrings(stringLinha.arrayStrings, stringLinha.n, saida);
        escreverInts(intsLinha.arrayInts, intsLinha.n, saida);
        escreverFloats(floatsLinha.arrayFloats, floatsLinha.n, saida);
        escreverPontos(pontosLista.arrayPontos, pontosLista.n, saida);
        fputs("\n", saida);
    }

    fgetc(saida);
    fclose(entrada);
    fclose(saida);
    return 1;
}
#pragma region Utils
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
#pragma endregion

#pragma region Pontos
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
#pragma endregion

#pragma region Sorts
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

void ordernarListaPalavras(char **array, int n){
    int iCont, jCont, kCont, atual;

    for(iCont = 1; iCont < n; iCont++){
        atual = 0;
        char *key = malloc(sizeof(char) * (strlen(array[iCont]) + 1)); 
        
        for(kCont = 0; kCont < strlen(array[iCont]); kCont++){
            key[kCont] = array[iCont][kCont];
        }

        jCont = iCont - 1;

        while(jCont >= 0){
            if(array[jCont][atual] == key[atual]){
                atual++;
            }
            else if(array[jCont][atual] > key[atual]){
                array[jCont + 1] = array[jCont];
                jCont--;
            }
            else{
                break;
            }
        }

        array[jCont + 1] = key;
    }
}
#pragma endregion

#pragma region Prints
void escreverPontos(Ponto *pontos, int n, FILE *arquivoSaida){
   int iCont;

    fputs(" p:", arquivoSaida);
    for(iCont = 0; iCont < n; iCont++){
        if(iCont != 0){
            fputs(" ", arquivoSaida);
        }
        fputs(pontos[iCont].pontoStr, arquivoSaida);
    }
}

void escreverStrings(char **strings, int n, FILE *arquivoSaida){
    int iCont;

    fputs("str:", arquivoSaida);
    for(iCont = 0; iCont < n; iCont++){
        if(iCont != 0){
            fputs(" ", arquivoSaida);
        }
        fputs(strings[iCont], arquivoSaida); 
    }
}

void escreverFloats(float *listaFloats, int n, FILE *arquivoSaida){
    int iCont;
    
    fputs(" float:", arquivoSaida);
    for(iCont = 0; iCont < n; iCont++){
        if(iCont != 0){
            fputs(" ", arquivoSaida);
        }
        fprintf(arquivoSaida,"%.2f", listaFloats[iCont]);
    }
}

void escreverInts(int *listaInts, int n, FILE *arquivoSaida){
    int iCont;
    
    fputs(" int:", arquivoSaida);
    for(iCont = 0; iCont < n; iCont++){
        if(iCont != 0){
            fputs(" ", arquivoSaida);
        }
        fprintf(arquivoSaida,"%d", listaInts[iCont]);
    }
}
#pragma endregion