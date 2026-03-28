#include "etapa2Tar1.h"

int bin2dec(char *x);  // função auxiliar pra conversão binário para decimal
void barramentoB(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr);
void barramentoC(char *ir, char *sd, char *c_bus, char *h, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar);

void logEt2Tar2(char *ir, int cycle, char *b_bus, char *c_bus, char *mar, char *mdr, char *pc, char *mbr, char *sp, char *lv, char *cpp, char *tos, char *opc, char *h, FILE* log);








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

// função que printa quais registradores estão habilitados no barramento C
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
                     "dr = 00000000000000000000000000000000\n "
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