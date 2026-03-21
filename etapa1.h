#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processamentoEntradas(char * ir, char * a, char * b);
void and(char* a, char* b, char* s);
char* calculoULA(int f0, int f1, char * a, char * b, char* co, char *s);
void or(char * a, char * b, char *s);
void somaArit(char * a, char * b, char * co, char *s);
void incremento(char *s, char *co);
void inversor(char *a);
void logCiclo(int pc, char* ir, char* a, char* b, char* s, char co, FILE* log);

void processamentoEntradas(char* ir, char* a, char* b){ 
    // Separando as  instruções em variáveis e convertendo para inteiro.
    int ena  = ir[2] - '0';
    int enb  = ir[3] - '0';
    int inva = ir[4] - '0';
    int inc  = ir[5] - '0';
    
    // aplicando os enables.
    if(!ena) inversor(a);   // para a = 11111111111111111111111111111111, desativar basta inverte-lo
    if(!enb) b[31] = '0';   // para b = 00000000000000000000000000000001, desativar basta mudar o último bit para 0
    
    // inversão de a.
    if (inva) inversor(a);
}

char * calculoULA(int f0, int f1, char *a, char *b, char *co, char *s){
    // direcionando para a operação correta a partir das entradas F0 e F1
    if(f0 == 0 && f1 == 0){ // AND
        and(a, b, s);
    }

    if(f0 == 0 && f1 == 1){ // OR
        or(a, b, s);
    }

    if(f0 == 1 && f1 == 0){ // B complemento
        inversor(b);
    }

    if(f0 == 1 && f1 == 1){ // SUM
        somaArit(a, b, co, s);
    }

    return s;
}

void and(char* a, char* b, char* s){
    // lógica do operador AND
    for (int i = 0; i < 32; i++) {
        if (a[i] == '1' && b[i] == '1') {
            s[i] = '1';
        }
        else {
            s[i] = '0';
        }
    }

    s[32] = '\0';
}

void or(char *a, char *b, char *s) {
    // lógica do operador OR
    for (int i = 0; i < 32; i++) {
        if (a[i] == '0' && b[i] == '0') {
            s[i] = '0';
        }

        else s[i] = '1';
    }

    s[32] = '\0';
}

void somaArit(char *a, char *b, char *co, char *s) {
    int carry = 0, soma;

    // processamento de cada caractere da direita para esquerda, guardando o carry
    for (int i = 31; i >= 0; i--) {
        if (a[i] != b[i]) soma = 1; // simula o a^b
        else soma = 0;

        if (carry) {    // se tem carry da operação anterior
            carry = soma && carry;
            soma = soma^1;
        }

        else {
            if (a[i] == '1' && b[i] == '1') carry = 1;
            else carry = 0;
        }

        // insere o resultado na saída
        s[i] = soma + '0';
    }
    s[32] = '\0';

    if (*co == '1') return; // assegura que um carry adicionado em outras operações não vai ser sobrescrito
    *co = carry + '0';
}

void inversor(char *a) {
    // inverte 1 para 0 e 0 para 1 enquanto não achar o fim da string
    for(int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '0') {
            a[i] = '1';
        }
        else {
            a[i] = '0';
        }
    }
}

void incremento(char *s, char *co) {
    // adiciona 1 ao final, que deve ser processado como uma soma aritmética por conta da possibilidade de haver um carry
    somaArit(s, "00000000000000000000000000000001", co, s);
}

void logCiclo(int pc, char* ir, char* a, char* b, char* s, char co, FILE*log) {
    // printando o resultado do ciclo

    if (pc == 1) {
        fprintf(log, "b = %s\n", b);
        fprintf(log, "a = %s\n\n", a);

        fprintf(log, "Comecando!!!!\n");
        fprintf(log,"==============================================\n\n");
    }

    fprintf(log,"Ciclo %d\n\n", pc);
    fprintf(log,"PC = %d\n", pc);
    fprintf(log,"IR = %s\n", ir);
    fprintf(log,"b = %s\n", b);
    fprintf(log,"a = %s\n", a);
    fprintf(log,"s = %s\n", s);
    fprintf(log,"co = %c\n\n", co);
    fprintf(log,"==============================================\n");
}