#ifndef L0Q1_H
#define L0Q1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM_MAX_LINHA 1000

#define false (0)
#define true (1)

#pragma region STRUTURAS

typedef struct ponto Ponto;

struct ponto {
    char *coordenadaPonto;
    float distanciaOrigem;
    // cálculo de distância
    double x; 
    double y;
    // encadeamento
    Ponto* prox;
    Ponto* ant;
};

#pragma endregion

#pragma region FUNÇÕES

// relacionadas à strings
double convStrNum(char* stringPonto, int* idx);
void proximoNumOuSinal (char** string);
char* obterSubstring(char* stringPonto, char separador, int idx);
int proximaCoordenada(char* stringPonto, int* idx);

// relacionadas à estrutura de pontos
Ponto criarPonto0();
Ponto* adicionarPontoLista(Ponto* pontoInicio, Ponto* novoPonto);
int atribuirCoordenadasPonto(Ponto* structPonto, char* stringPonto, int* idx);
double calcularDistanciaPontos(Ponto ponto1, Ponto ponto2);
Ponto* obterPontoLista(char* linha, int* idx);

#pragma endregion

#endif

#pragma region PRINCIPAL 

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
    
    // teste
    Ponto ponto_teste;
    int idx = 0;
    fgets(linha, TAM_MAX_LINHA, entrada);
    atribuirCoordenadasPonto(&ponto_teste, linha, &idx);
    //
    
    while(fgets(linha, TAM_MAX_LINHA,  entrada) != NULL){
        fputs(linha, saida);
    }

    fclose(entrada);
    fclose(saida);

    return 1;
}

// Gerencia a lógica do programa para a linha atual
void gerenciarLinha (char* linha)
{
    // indexador
    int idx = 0; 
    
    // obtém a lista de pontos da entrada
    Ponto* pontoInicio = obterPontoLista(linha, &idx); 
}

Ponto* obterPontoLista(char* linha, int* idx)
{
    Ponto* pontoInicio = (Ponto*) malloc(sizeof(Ponto));
    pontoInicio->prox = NULL;

    // verifica se há pelo menos um ponto e atribui como inicial
    if (atribuirCoordenadasPonto(pontoInicio, linha, idx) == false) 
        return NULL;

    // adiciona novos pontos na lista enquanto for possível atribuir - a linha não terminar, por exemplo
    Ponto* novoPonto = (Ponto*) malloc(sizeof (Ponto));
    while(atribuirCoordenadasPonto(novoPonto, linha, idx) == true)
    {
        pontoInicio = adicionarPontoLista(pontoInicio, novoPonto);
        novoPonto = (Ponto*) malloc (sizeof(Ponto));
    }
    
    return pontoInicio;
}

#pragma endregion

#pragma region PONTOS

// insere um ponto na lista retornando o novo início
Ponto* adicionarPontoLista (Ponto* pontoInicio, Ponto* novoPonto)
{
    // encadeamento
    pontoInicio->ant = novoPonto;
    novoPonto->prox = pontoInicio;

    // deve-se tornar o pontoInicio igual a este através do retorno
    return novoPonto; 
}

// Função para calcular distância entre pontos - basta passar o ponto0 para calcular
// distância até a origem
double calcularDistanciaPontos(Ponto ponto1, Ponto ponto2)
{
    return sqrt(pow((ponto1.y - ponto2.y), 2) + pow((ponto1.x - ponto2.x), 2));
};

// Cria o ponto 0
Ponto criarPonto0()
{
    Ponto ponto0;
    ponto0.x = 0; ponto0.y = 0;
    return ponto0;
};

// função para atribuir propriedades x e y de um ponto com base
// numa string no formato: "(x, y)"
int atribuirCoordenadasPonto(Ponto* structPonto, char* stringPonto, int* idx)
{
    // inicializa / zera x e y do ponto
    structPonto->x = 0;
    structPonto->y = 0;

    if (proximaCoordenada(stringPonto, idx) == false)
        return false;
    
    //structPonto->coordenadaPonto = obterSubstring(stringPonto, ')', idx);
    structPonto->coordenadaPonto = obterSubstring(stringPonto, ')', *idx);

    // para o x:
    *idx += 1; // incrementa em 1 pois parou no '('
    structPonto->x = convStrNum(stringPonto, idx);

    // para o y:
    *idx += 1; // incremente em 1 pois parou no ','
    structPonto->y = convStrNum(stringPonto, idx);
    
    Ponto ponto0 = criarPonto0();

    structPonto->distanciaOrigem = calcularDistanciaPontos(*structPonto, ponto0);

    // testando output
    printf("\nX: %lf;", structPonto->x);
    printf("\nY: %lf;", structPonto->y);
    printf("\nDistância: %lf;", structPonto->distanciaOrigem);
    printf("\nSubstring: %s.\n", structPonto->coordenadaPonto);
    //
    
    return true;
}

#pragma endregion

#pragma region FUNÇÕES STRING

// passa o indexador para a próxima coordenada ou final de linha
int proximaCoordenada(char* stringPonto, int* idx)
{
    // encontra próxima coordenada ou o final da linha
    while (stringPonto[*idx] != '(' && stringPonto[*idx] != '\n')
        *idx += 1;
    
    // verifica se a linha acabou
    if (stringPonto[*idx] == '\n')
        return false;
    else
        return true;
};

// obtém a substring equivalente ao início da string passada até o separador
char* obterSubstring(char* stringPonto, char separador, int idx)
{
    int i;

    for (i = idx; stringPonto[i] != separador; i++); // encontra o tamanho

    char* substring = (char*) malloc(sizeof(char) * ((++i - idx) + 1)); // aloca retorno

    for (i = idx; stringPonto[i] != separador; i++)
        substring[i - idx] = stringPonto[i]; // copia até o separador

    substring[(i - idx)] = stringPonto[i]; // último char, ainda que seja o separador
    substring[(i - idx) + 1] = '\0'; // terminador nulo no final

    return substring; // retorna a substring
}

double convStrNum (char* stringPonto, int* idx)
{
    double retorno = 0; // retorno

    int decimal = 0; // bool para saber se estamos à direita ou esquerda da vírgula

    double div = (double) 10.0; // controlador da casa decimal da parte fracionária

    // enquanto o conteúdo da posição atual do indexador for número ASCII, ponto ou sinal de número negativo
    while ((stringPonto[*idx] > 47 && stringPonto[*idx] < 58) || stringPonto[*idx] == '-' || stringPonto[*idx] == '.')
    {
        if(stringPonto[*idx] == '-')
        {
            // torna o número negativo e passa o indexador para a próxima casa significativa
            retorno += (double) ((stringPonto[*idx + 1] - 48) * -1);
            *idx += 2;
            continue;
        }
        
        if(stringPonto[*idx] == '.')
        {
            // tratar char recebido como casa à direita da vírgula e acrescer indexador
            decimal = 1;
            *idx += 1;
        }

        if (decimal)
        {
            // soma ou subtrai a depender do valor de retorno em um número
            // na casa decimal atual - controlada pela variável div
            retorno += retorno > 0 ? ((double) (stringPonto[*idx] - 48))/div : ((double) ((48 - stringPonto[*idx]) * -1))/div;
            div *= (double) 10.0;
        }
        else 
        {
            // acresce a casa atual do retorno e soma com o número da posição atual do indexador 
            retorno *= 10;
            retorno += retorno >= 0 ? ((double) (stringPonto[*idx] - 48)) : ((double) ((stringPonto[*idx] - 48) * -1));
        }

        *idx += 1; // incrementa o indexador
    }

    return retorno; // retorna o número equivalente àquele trecho
}

// ela vai até o primeiro sinal ou número, vai acrescendo um número que, se vier como 0, será equivalente
// ao double
/*
void proximoNumOuSinal (char** string)
{
    // avança até o próximo número ou sinal numérico
    while ((*(*(string) + sizeof(char)) < 48 || *(*(string) + sizeof(char)) > 57) && (*(*(string) + sizeof(char)) != '-'))
        *(string) += sizeof(char);
}
*/

#pragma endregion