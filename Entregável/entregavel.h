#include "../Etapa3/etapa3.h"

void ILOAD(char *h, int x, char *lv, char *mar, char *sp, char *tos, char *mdr, char memoria[][33]);
void DUP(char *mar, char *sp, char *mdr, char *tos, char memoria[][33]);
void BIPUSH(char *h, char* byte, char *sp, char *mar, char *mdr, char* mbr, char *tos, char memoria[][33]);
void logEntradaEntregavel(char memoria[][33], char *nome, int cycle, char *b_bus, char *c_bus, int indice, char *val_bin, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);
void logFinalEntregavel(char memoria[][33], char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);
int defInstrucao(char * nome, int indice, char * val_bin);
int getMemAddr(char *mar);
void logMemoriaEntregavel(char memoria[][33], FILE *log);


// Extrai os 4 últimos bits de MAR para usar como endereço de memória (0-15)
int getMemAddr(char *mar) {
    char mar_bits[5];
    for (int i = 0; i < 4; i++) {
        mar_bits[i] = mar[i + 28];
    }
    mar_bits[4] = '\0';
    return bin2dec(mar_bits);
}

// Imprime as 16 linhas da memória de dados no log
void logMemoriaEntregavel(char memoria[][33], FILE *log) {
    fprintf(log, "*******************************\n");
    for (int i = 0; i < 16; i++) {
        fprintf(log, "%s\n", memoria[i]);
    }
    fprintf(log, "*******************************\n");
}

void ILOAD(char *h, int x, char *lv, char *mar, char *sp, char *tos, char *mdr, char memoria[][33]) {

    // H = LV
    strcpy(h, lv);

    // H = H+1 (x vezes)
    char fakeCo = '0';
    for (int i = 0; i < x; i++) {
        fakeCo = '0';
        incremento(h, &fakeCo);
    }

    // MAR = H; rd
    strcpy(mar, h);

    // rd: MDR = memoria[endereço de MAR]
    strcpy(mdr, memoria[getMemAddr(mar)]);

    // SP = SP + 1
    fakeCo = '0';
    incremento(sp, &fakeCo);
    
    // MAR = SP; wr
    strcpy(mar, sp);

    // wr: memoria[endereço de MAR] = MDR
    strcpy(memoria[getMemAddr(mar)], mdr);
    
    // TOS = MDR
    strcpy(tos, mdr);
}

void DUP(char *mar, char *sp, char *mdr, char *tos, char memoria[][33]) {
    // SP = SP + 1
    char fakeCo = '0';
    incremento(sp, &fakeCo);

    // MAR = SP
    strcpy(mar, sp);

    // MDR = TOS; wr
    strcpy(mdr, tos);

    // wr: memoria[endereço de MAR] = MDR
    strcpy(memoria[getMemAddr(mar)], mdr);
}

void BIPUSH(char *h, char* byte, char *sp, char *mar, char *mdr, char* mbr, char *tos, char memoria[][33]) {
    // SP = MAR = SP + 1
    char fakeCo = '0';
    incremento(sp, &fakeCo);
    strcpy(mar, sp);

    // fetch: MBR = byte, H = MBR (com zeros à esquerda, sem passar pela ULA)
    strcpy(mbr, byte);
    for (int i = 0; i < 24; i++) {
        h[i] = '0';
    }
    for (int i = 0; i < 8; i++) {
        h[24 + i] = byte[i];
    }
    h[32] = '\0';

    // MDR = TOS = H; wr
    strcpy(tos, h);
    strcpy(mdr, tos);

    // wr: memoria[endereço de MAR] = MDR
    strcpy(memoria[getMemAddr(mar)], mdr);
}

void logEntradaEntregavel(char memoria[][33], char *nome, int cycle, char *b_bus, char *c_bus, int indice, char *val_bin, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log){
    if (cycle == 1) {
        fprintf(log, "==============================================\n");
        fprintf(log, "> Estado da memoria inicial\n");
        logMemoriaEntregavel(memoria, log);
        
        fprintf(log, "==============================================\n");
        fprintf(log, "> Estado dos registradores iniciais\n");
        fprintf(log, "mar = %s\n"
            "mdr = %s\n"
            "pc = %s\n"
            "mbr = %s\n"
            "sp = %s\n"
            "lv = %s\n"
            "cpp = %s\n"
            "tos = %s\n"
            "opc = %s\n"
            "h = %s\n\n", mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h);
            
            fprintf(log, "==============================================\n"
                "Comecando!\n");
        }
        
    int instrucao = defInstrucao(nome, indice, val_bin);
    switch (instrucao)
    {
    case 1:
        fprintf(log,"instrucao = %s %d\n", nome, indice);
        break;
    case 2:
        fprintf(log,"instrucao = %s %s\n", nome, val_bin);
        break;
    case 3:
            fprintf(log,"instrucao = %s\n", nome);
        break;    
    default:
        break;
    }
    fprintf(log, "==============================================\n");
    fprintf(log, "Ciclo %d\n", cycle);
    fprintf(log, "b_bus = %s\n", b_bus);
    fprintf(log, "c_bus = %s\n\n", c_bus);
    fprintf(log, "> Registradores antes da instrucao\n");
    fprintf(log, "mar = %s\n", mar);
    fprintf(log, "mdr = %s\n", mdr);
    fprintf(log, "pc = %s\n", pc);
    fprintf(log, "mbr = %s\n", mbr);
    fprintf(log, "sp = %s\n", sp);
    fprintf(log, "lv = %s\n", lv);
    fprintf(log, "cpp = %s\n", cpp);
    fprintf(log, "tos = %s\n", tos);
    fprintf(log, "opc = %s\n", opc);
    fprintf(log, "h = %s\n\n", h);
}
void logFinalEntregavel(char memoria[][33], char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log){
    fprintf(log, "> Registradores depois da instrucao\n");
    fprintf(log, "mar = %s\n", mar);
    fprintf(log, "mdr = %s\n", mdr);
    fprintf(log, "pc = %s\n", pc);
    fprintf(log, "mbr = %s\n", mbr);
    fprintf(log, "sp = %s\n", sp);
    fprintf(log, "lv = %s\n", lv);
    fprintf(log, "cpp = %s\n", cpp);
    fprintf(log, "tos = %s\n", tos);
    fprintf(log, "opc = %s\n", opc);
    fprintf(log, "h = %s\n\n", h);
    fprintf(log, "> Memoria depois da instrucao\n");
    logMemoriaEntregavel(memoria, log);
}   
int defInstrucao(char * nome, int indice, char * val_bin){
    if(strcmp(nome, "ILOAD") == 0){
        return 1;
    }
    if(strcmp(nome, "BIPUSH") == 0){
        return 2;
    }
    if(strcmp(nome,"DUP") == 0){
        return 3;
    }
    return 0;
}