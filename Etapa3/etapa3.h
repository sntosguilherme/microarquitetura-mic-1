#include "../Etapa2/etapa2Tar2.h"

void barramentoBE3(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr);
void wrMemoria(char *ir, char *mar, char *mdr, char memoria[8][33]);
void logMemoria(char memoria[8][33], FILE *log);
void logEntradaE3(char memoria[8][33], char *ir, int cycle, char *b_bus, char *c_bus, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);
void logFinalE3(char memoria[8][33], char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);


void barramentoBE3(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr) {
    // valor decimal selecionado representa qual registrador vai ser a entrada B
    char ctrlB[5];  // 4 bits

    for (int i = 0; i < 4; i++) {   // inserindo o controle do barramento B
        ctrlB[i] = ir[i+19];
    }

    ctrlB[4] = '\0';

    switch (bin2dec(ctrlB)) {
    case 0:
        strcpy(b, mdr);
        strcpy(b_bus, "mdr");       // indicador do registrador escolhido
        break;
    
    case 1:
        strcpy(b, pc);
        strcpy(b_bus, "pc");
        break;
    
    case 2: // MBR com 24 primeiros bits iguais ao bit mais alto
        strcpy(b_bus, "mbr");
        char x = mbr[0];

        for (int i = 0, j = 0; i < 32; i++) {
            if (i < 24)         // de 0 a 23 é preenchido pelo caractere
                b[i] = x;
            else {              // de 24 a 32 é preenchido por mbr 
                b[i] = mbr[j];
                j++;
            }
        }
        
        break;
    
    // Quando MBRU é selecionado, a palavra deve ser preenchida até 32 bits utilizando zeros.
    case 3: 
        strcpy(b_bus, "mbru");

        for (int i = 0, j = 0; i < 32; i++) {
            if (i < 24) 
                b[i] = '0';
            else { 
                b[i] = mbr[j];
                j++;
            }
        }
        
        break;

    case 4:
        strcpy(b, sp);
        strcpy(b_bus, "sp");
        break;
    case 5:
        strcpy(b, lv);
        strcpy(b_bus, "lv");
        break;
    case 6:
        strcpy(b, cpp);
        strcpy(b_bus, "cpp");
        break;
    case 7:
        strcpy(b, tos);
        strcpy(b_bus, "tos");
        break;
    case 8:
        strcpy(b, opc);
        strcpy(b_bus, "opc");
        break;
    
    default:
        printf("Algo deu errado aq\n");
        break;
    }
}

void wrMemoria(char *ir, char *mar, char *mdr, char memoria[8][33]) {
    char mar2[5];
    for (int i = 0; i < 4; i++) {
        mar2[i] = mar[i+28];
    }
    mar2[4] = '\0';

    //printf("%s ", mar2); //teste
    int endereco = bin2dec(mar2);

    if (ir[17] == '1') {    // WRITE
        strcpy(memoria[endereco], mdr);
    }

    if (ir[18] == '1') {    // READ
        strcpy(mdr, memoria[endereco]);
    }
}

void logMemoria(char memoria[8][33], FILE *log) {
    fprintf(log, "*******************************\n");
    for (int i = 0; i < 8; i++) {
        fprintf(log, "%s\n", memoria[i]);   // imprimindo cada linha da memória
    }
    fprintf(log, "*******************************\n");
}

void logEntradaE3(char memoria[8][33], char *ir, int cycle, char *b_bus, char *c_bus, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log) {
    
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
    
    
    fprintf(log, "==============================================\n");
    fprintf(log, "Ciclo %d\n", cycle);

    fprintf(log, "ir = ");
    for (int i = 0; i < 23; i++) {
        fprintf(log, "%c", ir[i]);

        if (i == 7 || i == 16 || i == 18) 
            fprintf(log, " ");
    }

    fprintf(log, "\n\n");
    fprintf(log, "b_bus = %s\n", b_bus);
    fprintf(log, "c_bus: ");
    printC_bus(c_bus, log);
    fprintf(log, "\n");

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
void logFinalE3(char memoria[8][33], char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log) {
    
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