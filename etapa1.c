#include "etapa1.h"
#include <stdlib.h>
#include <string.h>

unsigned int somar(unsigned int a, unsigned int b, int *carry) {
    // Centraliza a lógica de soma com 64 bits para facilitar a captura do Carry Out.
    unsigned long long temp = (unsigned long long) a + b;
    if (carry) {
        *carry = (temp >> 32) & 1;
    }
    return (unsigned int) temp;
}

unsigned int calculoULA(int f0, int f1, unsigned int A, unsigned int B, int *co) {
    unsigned int s = 0;
    *co = 0;

    // F0 = 0 e F1 = 0 -> Saída é A AND B
    if (f0 == 0 && f1 == 0) s = A & B;

    // F0 = 0 e F1 = 1 -> Saída é A OR B
    else if (f0 == 0 && f1 == 1) s = A | B;

    // F0 = 1 e F1 = 0 -> Saída é o complemento de A (Inverte todos os bits)
    else if (f0 == 1 && f1 == 0) s = ~A;

    // F0 = 1 e F1 = 1 -> Saída é a soma aritmética de A e B
    else if (f0 == 1 && f1 == 1){
        // Delegado para a função auxiliar de soma para tratar o Carry Out (vai um)
        s = somar(A, B, co);
    }

    return s;
}

void processamentoEntradas(char *ir, unsigned int *A, unsigned int *B, FILE *log, int pc) {
    // Converte os caracteres do array de instrução (ir) para valores numéricos inteiros (0 ou 1)
    // Subtrair '0' do valor atual do índice da string, revela o valor numérico inteiro esperado.
    int f0 = ir[0] - '0';
    int f1 = ir[1] - '0';
    int ena  = ir[2] - '0';
    int enb  = ir[3] - '0';
    int inva = ir[4] - '0';
    int inc  = ir[5] - '0';

    // Salva o estado original em temporários para não alterar permanentemente os conteúdos de A e B
    unsigned int aTemp = *A;
    unsigned int bTemp = *B;

    // Aplica os sinais de controle nos temporários antes de serem enviados à ULA
    // Se ENA (Enable A) estiver desligado (0), ignora A e substitui por 0
    if (!ena) aTemp = 0;
    // Se ENB (Enable B) estiver desligado (0), ignora B e substitui por 0
    if (!enb) bTemp = 0;
    // Se INVA (Invert A) for verdadeiro, inverte todos os bits armazenados em aTemp usando NOT (~)
    if (inva) aTemp = ~aTemp;

    // LOG: estado ANTES das operações, mas com as portas já fechadas/abertas
    fprintf(log, "IR = %s\n", ir);

    fprintf(log, "b = ");
    printBin(bTemp, log);
    fprintf(log, "\n");

    fprintf(log, "a = ");
    printBin(aTemp, log);
    fprintf(log, "\n");

    int co = 0;
    unsigned int S = calculoULA(f0, f1, aTemp, bTemp, &co);

    // Incremento: Se verdadeiro, adiciona +1 ao resultado final vindo da ULA
    if (inc) {
        // Delegado para a função auxiliar, reaproveitando o tratamento de overflow em 64 bits
        S = somar(S, 1, &co);
    }

    // LOG: resultado
    fprintf(log, "s = ");
    printBin(S, log);
    fprintf(log, "\n");

    fprintf(log, "co = %d\n", co);

}

void printBin(unsigned int num, FILE *out){
    // Percorre os índices dos bits do mais significativo 31 ao menos significativo 0
    for(int i = 31; i >= 0; i--){
        // O bit shift para a direita (num >> i) garante que o bit desejado estará na direita agora
        // do valor final avaliado, o permitindo ser isolado pelo operador (& 1) resultando em 0 ou 1.
        fprintf(out, "%d", (num >> i) & 1);
    }
}