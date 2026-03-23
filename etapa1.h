/* OQ FAZ CADA COMPONENTE
A: OPERANDO 1
B: OPERANDO 2
ENA: Enable A. Quando está em 0, qualquer valor em A é ignorado e se torna 0. 
ENB: Enable B. Quando está em 0, qualquer valor em B é ignorado e se torna 0.
INVA: Inverte A bit a bit.
INC: Guarda o vai-um. Soma 1 ao resultado final.
F0 e F1: Em conjunto definem a operação a ser realizada.

Conjunto de operações:
    F0 = 0 e F1 = 0  -> indica que a saída é igual a A && B (A and B)
    F0 = 0 e F1 = 1  -> indica que a saída é igual a A | B  (A or B)
    F0 = 1 e F1 = 0  -> indica que a saída é igual ao complemento de B
    F0 = 1 e F1 = 1  -> indica que a saída é igual a soma aritmética

Detalhe: 
    -co é carry on na saída (valor de vai um) para os mafiosos

Planejamento da execução do programa
    1- Armazenamento das variáveis iniciais A e B
    2- Abrir o arquivo de leitura, armazenar a linha e a palavra 
    3- Armazenamento da combinação de sinais
    4- Processamento das instruções 
    5- Escrita dos valores de IR, PC, A, B, S e o Vai-um no log
    6- Próxima linha
*/

// Protótipos das funções

// aplica ENA, ENB, INVA em A e B.
// por meio de f0 e f1 determina qual operacao sera realizada em A e B.
// recebe F1, F2, A e B para poder repassar esses parâmetros caso necessário
// retorna saída

#ifndef ETAPA1_H
#define ETAPA1_H

#include <stdio.h>

unsigned int somar(unsigned int a, unsigned int b, int *carry);

unsigned int calculoULA(int f0, int f1, unsigned int A, unsigned int B, int *co);
void processamentoEntradas(char *ir, unsigned int *A, unsigned int *B, FILE *log, int pc);
void printBin(unsigned int num, FILE *out);

unsigned int somar(unsigned int a, unsigned int b, int *carry)

#endif