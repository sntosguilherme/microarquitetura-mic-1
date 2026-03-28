#include "../Etapa1/etapa1Tar1.h"

void processamentoEntradas2(char * ir, char * a, char * b);
void deslocaSRA1(char* s);
void deslocaSLL8(char* s);
int erro(int pc, char* ir, char* a0, char* b0, char* a, char* b, int sll8, int sra1, FILE* log);
void logCiclo2(int pc, char* ir, char* a0, char* b0, char* a, char* b, char* s, char* sd, char co, int n, int z, FILE* log);
int calcularN(char *sd);
int calcularZ(char *sd);

void processamentoEntradas2(char* ir, char* a, char* b){ 
    // em relação a função processamentoEntradas, só foi mudado o index, já que mudamos a quantidade de bits da instrução
    int ena  = ir[4] - '0';
    int enb  = ir[5] - '0';
    int inva = ir[6] - '0';
    int inc  = ir[7] - '0'; //nem é usado na função, da pra tirar
    
    // aplicando os enables.
    if(!ena) zerar(a);
    if(!enb) zerar(b);
    
    // inversão de a.
    if (inva) inversor(a);
}

void deslocaSRA1(char* s) {
    char a = s[0];

    for (int i = 1; s[i] != '\0'; i++) {
        char aux = s[i];
        s[i] = a;
        a = aux;
    }
}

void deslocaSLL8(char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (i+9 >= 32) {    // achei que seria 8, mas no exemplo da professora só dá certo com 9 (tlvz checar com ela depois)
            s[i] = '0';
        }
        else {
            s[i] = s[i+9];
        }
    }
}


int erro(int pc, char* ir, char* a0, char* b0, char* a, char* b, int sll8, int sra1, FILE* log) {
    if (sll8 && sra1) {
        // inicialmente igual ao logCiclo
        if (pc == 1) {
            fprintf(log, "b = %s\n", b0);
            fprintf(log, "a = %s\n\n", a0);

            fprintf(log, "Comecando!!!!\n");
            fprintf(log,"==============================================\n\n");
        }

        fprintf(log,"Ciclo %d\n\n", pc);
        fprintf(log,"PC = %d\n", pc);
        fprintf(log,"IR = %.8s\n", ir);

        // não printa o restante das variáveis e retorna erro
        fprintf(log,"> Erro! Instrucao invalida.\n");

        return 1;   // deu erro
    }

    return 0;
}

void logCiclo2(int pc, char* ir, char* a0, char* b0, char* a, char* b, char* s, char* sd, char co, int n, int z, FILE* log) {

    if (pc == 1) {
        fprintf(log, "b = %s\n", b0);
        fprintf(log, "a = %s\n\n", a0);

        fprintf(log, "Comecando!!!!\n");
        fprintf(log,"==============================================\n\n");
    }

    fprintf(log,"Ciclo %d\n\n", pc);
    fprintf(log,"PC = %d\n", pc);
    fprintf(log,"IR = %.8s\n", ir); // limitando exibição para os 8 primeiros chars para evitar quebra de linha.
    fprintf(log,"b = %s\n", b);
    fprintf(log,"a = %s\n", a);
    fprintf(log,"s = %s\n", s);
    fprintf(log, "sd = %s\n", sd);
    fprintf(log, "n = %d\n", n);
    fprintf(log, "z = %d\n", z);
    
    fprintf(log,"co = %c\n\n", co);
    fprintf(log,"==============================================\n");

}

int calcularFlagN(char *sd) {
    if (sd[0] == '1') return 1; // caso o primeiro bit seja 1, a flag será 1.
    return 0;
}

int calcularFlagZ(char *sd) {
    for (int i = 0; i < 32; i++) { // itera sobre todos os bits, se encontrare um 1 a flag será 0. 
        if (sd[i] == '1') {
            return 0;
        }
        }
    return 1;
}