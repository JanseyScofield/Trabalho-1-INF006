#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TAM_MAX_LINHA 1000

// estruturas
typedef struct{
    char *coordenadaPonto;
    float distanciaOrigem;
    // cálculo de distância
    double x; 
    double y;
} Ponto;

// funções
double calcularDistanciaPontos(Ponto ponto1, Ponto ponto2);
void convStrNum (char** stringPonto, double* num);
void atribuirCoordenadasPonto(Ponto* structPonto, char** stringPonto);
void proximoNumOuSinal (char** string);
char* obterSubstring(char** stringPonto, char separador);
Ponto criarPonto0();

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
    fgets(linha, TAM_MAX_LINHA, entrada);
    atribuirCoordenadasPonto(&ponto_teste, &linha);
    //
    
    while(fgets(linha, TAM_MAX_LINHA,  entrada) != NULL){
        fputs(linha, saida);
    }

    fclose(entrada);
    fclose(saida);

    return 1;
}

// função para atribuir propriedades x e y de um ponto com base
// numa string no formato: "(x, y)"
void atribuirCoordenadasPonto(Ponto* structPonto, char** stringPonto)
{
    // inicializa / zera x e y do ponto
    structPonto->x = 0;
    structPonto->y = 0;
    
    structPonto->coordenadaPonto = obterSubstring(stringPonto, ')');
    
    // para o x:
//    convStrNum(stringPonto, &(structPonto->x));

    // para o y:
 //   convStrNum(stringPonto, &(structPonto->y));
    
  //  Ponto ponto0 = criarPonto0();

   //structPonto->distanciaOrigem = calcularDistanciaPontos(*structPonto, ponto0);

}

// função que obtém substring '(x, y)' 
char* obterSubstring(char** stringPonto, char separador)
{
    int qnt = 1;
    printf("TESTE");
    proximoNumOuSinal(stringPonto);
    printf("TESTE;");
    
    *stringPonto += sizeof(char);
    
    while(**(stringPonto) != separador)
        qnt++;

    char* substring = (char*) malloc(sizeof(char) * (qnt + 1));
    
    for (int i = 0; i < qnt; i++)
    {
        *(substring + (sizeof(char) * i)) = *(*(stringPonto) + (sizeof(char) * i));
    }
    
    *(substring + (sizeof(char) * (qnt + 1))) = '\0';
    
    return substring;
}

// ela vai até o primeiro sinal ou número, vai acrescendo um número que, se vier como 0, será equivalente
// ao double
void convStrNum (char** stringPonto, double* num)
{
    // verificar decimal
    int decimal = 0;
    
    // divisor para a parte decimal
    float div = (float) 10;
    
    // converte até encontrar caracter não numérico / sinal numérico
    while (!((**(stringPonto) < 48 && **(stringPonto) > 56) || (**(stringPonto) != '-'))) 
    {
        if (**(stringPonto) == '-') // número é negativo
        {
            *(stringPonto) += sizeof(char);
            *(num) += (double) ((-1 * (**(stringPonto))) - 48);
        }
        
        if (**(stringPonto) == '.')
        {
            decimal = 1; // a partir deste momento os valores devem estar após a vírgula
            *(stringPonto) += sizeof(char);
        }
        
        if (decimal)
        {
            *(num) += *(num) > 0 ? ((double) (**(stringPonto) - 48))/div : ((double) ((**(stringPonto) * -1) - 48))/div; // soma ou subtrai valor na casa adequada
            div *= 10; // próximo char representa número de casa mais à esquerda
        }
        else
        {
            *(num) *= 10; // ordem do algarismo anterior acrescida
            *(num) += *(num) > 0 ? (double) (**(stringPonto) - 48) : (double)((-1 * (**(stringPonto))) - 48); // soma ou subtrai a depender do sinal
        }
        
        *(stringPonto) += sizeof(char); // indexador para o próximo caracter
    }
}

void proximoNumOuSinal (char** string)
{
    // avança até o próximo número ou sinal numérico
    while ((**(string) < 48 && **(string) > 56) || (**(string) != '-'))
        *(string) += sizeof(char);
}

// Função para calcular distância entre pontos - basta passar o ponto0 para calcular
// distância até a origem
double calcularDistanciaPontos(Ponto ponto1, Ponto ponto2)
{
    return sqrt(pow((ponto1.y - ponto2.y), 2) + pow((ponto1.x - ponto2.x), 2));
};

Ponto criarPonto0()
{
    Ponto ponto0;
    ponto0.x = 0; ponto0.y = 0;
    return ponto0;
}