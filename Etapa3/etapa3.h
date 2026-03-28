#include "../Etapa2/etapa2Tar2.h"

void etapa3barramentoB(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr);
void wrMemoria(char *ir, char *mar, char *mdr, FILE *memoria);

void etapa3barramentoB(char *ir, char *b, char *b_bus, char *opc, char *tos, char *cpp, char *lv, char *sp, char *pc, char *mdr, char *mar, char *mbr) {
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

void wrMemoria(char *ir, char *mar, char *mdr, FILE *memoria);