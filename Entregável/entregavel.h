// assumindo que etapa 3 tenha um include.h
#include "../Etapa3/etapa3.h"

/*
    Essas funções executam os trechos explicitados na parte de entregável
    São apenas as bases para o real funcionamento
    Ainda falta implementar como o rd e write afeta o programa!!!!!!
*/


void ILOAD(char *h, int x, char *lv, char *mar, char *sp, char *tos, char *mdr, char memoria[8][33]);
void DUP(char *mar, char *sp, char *mdr, char *tos, char memoria[8][33]);
void BIPUSH(char *h, char* byte, char *sp, char *mar, char *mdr, char* mbr, char *tos, char memoria[8][33]);
void logEntradaEntregavel(char memoria[8][33], char *nome, int cycle, char *b_bus, char *c_bus, int indice, char *val_bin, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);
void logFinalEntregavel(char memoria[8][33], char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);
int defInstrucao(char * nome, int indice, char * val_bin);



void ILOAD(char *h, int x, char *lv, char *mar, char *sp, char *tos, char *mdr, char memoria[8][33]) {

    // H = LV
    strcpy(h, lv);

    char fakeCo = '0';
    for (int i = 0; i < x; i++) {
        incremento(h, &fakeCo);
    }

    // mar = h; rd
    strcpy(mar,h);

    // rd
    strcpy(mdr, memoria[bin2dec(mar)]);

    // sp = sp + 1
    fakeCo = '0';
    incremento(sp, &fakeCo);
    
    // mar = sp = sp + 1; wr
    strcpy(mar, sp);

    // wr 
    strcpy(memoria[bin2dec(mar)], mdr);
    
    // tos = mdr
    strcpy(tos, mdr);
}

void DUP(char *mar, char *sp, char *mdr, char *tos, char memoria[8][33]) {
    // sp = sp + 1
    char fakeCo = '0';
    incremento(sp, &fakeCo);

    // mar = sp = sp + 1
    strcpy(mar, sp);

    // mdr = tos; wr
    strcpy(mdr, tos);

    // wr 
    strcpy(memoria[bin2dec(mar)], mdr);
}

void BIPUSH(char *h, char* byte, char *sp, char *mar, char *mdr, char* mbr, char *tos, char memoria[8][33]) {
    // sp = sp + 1
    char fakeCo = '0';
    incremento(sp, &fakeCo);


    // mar = sp + 1
    strcpy(mar, sp);

    // sp = mar = sp + 1
    strcpy(sp, mar);

    strcpy(mbr,byte);
    // fetch, insere diretamente em H os 8 bits recebidos e preenche ele com 0
    for (int i = 0, j = 0; i < 32; i++) {
        if (i < 24) {
            h[i] = '0';
        }
        else {
            h[i] = byte[j];
            j++;
        }
    }
    h[32] = '\0';

    // tos = h
    strcpy(tos, h);

    // mdr = tos = h; wr
    strcpy(mdr, tos);

    // wr 
    strcpy(memoria[bin2dec(mar)], mdr);
}
void logEntradaEntregavel(char memoria[8][33], char *nome, int cycle, char *b_bus, char *c_bus, int indice, char *val_bin, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log){
    if (cycle == 1) {   // colocando como string caso ela bote registradores diferentes
        fprintf(log, "==============================================\n");
        fprintf(log, "> Estado da memoria inicial\n");
        logMemoria(memoria, log);
        
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
                "Começando!\n");
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
    fprintf(log, "> Registradores antes da instrução\n");
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
void logFinalEntregavel(char memoria[8][33], char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log){
    fprintf(log, "> Registradores depois da instrução\n");
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
    logMemoria(memoria, log);
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