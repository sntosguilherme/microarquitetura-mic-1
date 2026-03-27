#include "etapa2Tar1.h"

int bin2dec(char *x);  // função auxiliar pra conversão binário para decimal
void barramentoB(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr);
void barramentoC(char *ir, char *sd, char *c_bus, char *h, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar);
void printC_bus(char *c_bus, FILE* log);

int erro(int pc, char* IR, FILE *log);

void logEt2Tar2(char *ir, int cycle, char *b_bus, char *c_bus, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);


int bin2dec(char *x) {
    int decimal = 0;
    int base = 1;

    for (int i = strlen(x) - 1; i >= 0; i--) {
        if (x[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }

    return decimal;
}

void barramentoB(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr) {
    // valor decimal selecionado representa qual registrador vai ser a entrada B
    char ctrlB[5];  // 4 bits

    for (int i = 0; i < 4; i++) {   // inserindo o controle do barramento B
        ctrlB[i] = ir[i+17];
    }

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
    
    // Quando MBRU é selecionado, a palavra deve ser preenchida até 32 bits utilizando zeros.
    case 3: 
        strcpy(b_bus, "mbru");
        
        zerar(b);
        
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
    for(int i = 8, j = 0; i < 17; i++, j++) {
        c_bus[j] = ir[i];

        if (c_bus[i] == '1') {
            switch(i-8) {
            case 0:
                strcpy(h, sd);
                break;

            case 1:
                strcpy(opc, sd);
                break;

            case 2:
                strcpy(tos, sd);
                break;

            case 3:
                strcpy(cpp, sd);
                break;  

            case 4:
                strcpy(lv, sd);
                break;

            case 5:
                strcpy(sp, sd);
                break;

            case 6:
                strcpy(pc, sd);
                break;  

            case 7:
                strcpy(mdr, sd);
                break;

            case 8:
                strcpy(mar, sd);
                break;
            }
        }
    }
}

int erro(int pc, char* IR, FILE *log) {
    if (IR[0] == '1' && IR[1] == '1') {
        fprintf(log, "Ciclo %d\n\n", pc);
        fprintf(log,"> Erro! Instrucao invalida.\n");

        return 1;
    }

    return 0;
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
            switch(i-8) {
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

void logEt2Tar2(char *ir, int cycle, char *b_bus, char *c_bus, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log) {

    // se cycle iniciar com 0 mudar isso
    if (cycle == 1) {
        fprintf(log, "==============================================\n");
        fprintf(log, "> Estado dos registradores iniciais\n");
        fprintf(log, "mar = 00000000000000000000000000000000\n "
                     "mdr = 00000000000000000000000000000000\n "
                     "pc = 00000000000000000000000000000000\n "
                     "mbr = 10000001\n "
                     "sp = 00000000000000000000000000000000\n "
                     "lv = 00000000000000000000000000000000\n "
                     "cpp = 00000000000000000000000000000000\n "
                     "tos = 00000000000000000000000000000010\n "
                     "opc = 00000000000000000000000000000000\n "
                     "h = 00000000000000000000000000000001\n ");
    
        fprintf(log, "==============================================\n"
                     "Começando!\n");
                    }
    
    
    fprintf(log, "==============================================\n");
    fprintf(log, "Ciclo %d\n", cycle);
    for (int i = 0; i < 21; i++) {
        fprintf(log, "%c", ir[i]);

        if (i == 7 || i == 16) 
            fprintf(log, " ");
    }

    fprintf(log, "\n");
    fprintf(log, "b_bus = %s\n", b_bus);
    fprintf(log, "c_bus: ");
    printC_bus(c_bus, log);

    fprintf(log, "> Registradores depois da instrução\n");
    fprintf(log, "mar = %s", mar);
    fprintf(log, "mar = %s", mdr);
    fprintf(log, "mar = %s", pc);
    fprintf(log, "mar = %s", mbr);
    fprintf(log, "mar = %s", sp);
    fprintf(log, "mar = %s", lv);
    fprintf(log, "mar = %s", cpp);
    fprintf(log, "mar = %s", tos);
    fprintf(log, "mar = %s", opc);
    fprintf(log, "mar = %s", h);
    
}