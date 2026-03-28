#include "etapa2Tar1.h"

int bin2dec(char *x);  // função auxiliar pra conversão binário para decimal
void barramentoB(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr);
void barramentoC(char *ir, char *sd, char *c_bus, char *h, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar);
void processarC_bus(char *ir, char *c_bus);
void printC_bus(char *c_bus, FILE* log);

int erro2(int pc, char* IR, FILE *log);

void logEntrada(char *ir, int cycle, char *b_bus, char *c_bus, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);
void logFinal(char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);


int bin2dec(char *x) {
    int decimal = 0;
    int base = 8;

    for (int i = 0; i < 4; i++) {
        if (x[i] == '1') {
            decimal += base;
        }
        base /= 2;

    }

    return decimal;
}

void barramentoB(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr) {
    // valor decimal selecionado representa qual registrador vai ser a entrada B
    char ctrlB[5];  // 4 bits

    for (int i = 0; i < 4; i++) {   // inserindo o controle do barramento B
        ctrlB[i] = ir[i+17];
    }

    printf("Seliga -> %d\n\n", bin2dec(ctrlB));
    printf("Passei\n");
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
        int j = 0;

        for (int i = 0; i < 32; i++) {
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
        strcpy(b_bus, "mbr");
        char x = mbr[0];
        int j;

        for (int i = 0; i < 32; i++) {
            if (i < 24)         // de 0 a 23 é preenchido pelo caractere
                b[i] = x;
            else {              // de 24 a 32 é preenchido por mbr 
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

void barramentoC(char *ir, char *sd, char *c_bus, char *h, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar) {
    
    // vai pegar 9 bits de ir e ver qual bits tão habilitados, selecionando os registradores e sobreescrevendo eles por sd
    for(int i = 0; i < 9; i++) {
        if (c_bus[i] == '1') {
            switch(8-i) {
            case 0:
                strcpy(mar, sd);
                break;

            case 1:
                strcpy(mdr, sd);
                break;

            case 2:
                strcpy(pc, sd);
                break;

            case 3:
                strcpy(sp, sd);
                break;  

            case 4:
                strcpy(lv, sd);
                break;

            case 5:
                strcpy(cpp, sd);
                break;

            case 6:
                strcpy(tos, sd);
                break;  

            case 7:
                strcpy(opc, sd);
                break;

            case 8:
                strcpy(h, sd);
                break;
            }
        }
    }
}

int erro2(int pc, char* IR, FILE *log) {
    if (IR[0] == '1' && IR[1] == '1') {
        fprintf(log, "Ciclo %d\n\n", pc);
        fprintf(log,"> Erro! Instrucao invalida.\n");

        return 1;
    }

    return 0;
}

// chamar na main ANTES do logEntrada e do barramento C
void processarC_bus(char *ir, char *c_bus) {
    
    for(int i = 8, j = 0; i < 17; i++, j++) {
        c_bus[j] = ir[i];
    }
}

void printC_bus(char *c_bus, FILE* log) {
    // usado pra printar de forma organizada que nem o dela
    int counterRegs = 0;
    
    for (int i = 0; i < 9; i++) {
        if (c_bus[i] == '1') counterRegs++;
    }

    if (!counterRegs){
        fprintf(log, "Nenhum\n");
        return;
    }

    for (int i = 0; i < 9 && counterRegs; i++) {
        if (c_bus[i] == '1') {
            switch(i) {
            case 0:
                fprintf(log, "h");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;

            case 1:
                fprintf(log, "opc");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;

            case 2:
                fprintf(log, "tos");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;

            case 3:
                fprintf(log, "cpp");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;  

            case 4:
                fprintf(log, "lv");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;

            case 5:
                fprintf(log, "sp");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;

            case 6:
                fprintf(log, "pc");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;  

            case 7:
                fprintf(log, "mdr");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;

            case 8:
                fprintf(log, "mar");
                if (counterRegs > 1) fprintf(log, ", ");

                counterRegs--;
                break;
            }
        }
    }
    
    fprintf(log, "\n");
}

void logEntrada(char *ir, int cycle, char *b_bus, char *c_bus, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log) {

    
    if (cycle == 1) {   // colocando como string caso ela bote registradores diferentes
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
    for (int i = 0; i < 21; i++) {
        fprintf(log, "%c", ir[i]);

        if (i == 7 || i == 16) 
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

void logFinal(char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log) {

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
    
}