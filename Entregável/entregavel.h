// assumindo que etapa 3 tenha um include.h
// #include "../Etapa3/etapa3.h"
#include "../Etapa2/etapa2Tar2.h"

/*
    Essas funções executam os trechos explicitados na parte de entregável
    São apenas as bases para o real funcionamento
    Ainda falta implementar como o rd e write afeta o programa!!!!!!
*/


void ILOAD(char *h, int x, char *lv, char *mar, char *sp, char *tos, char *mdr);
void DUP(char *mar, char *sp, char *mdr, char *tos);
void BYPUSH(char *h, char *byte, char *sp, char *mar, char *mdr, char *tos);

void ILOAD(char *h, int x, char *lv, char *mar, char *sp, char *tos, char *mdr) {

    // H = LV
    strcpy(h, lv);

    char fakeCo = '0';
    for (int i = 0; i < x; i++) {
        incremento(h, &fakeCo);
    }

    // mar = h; rd
    mar = h;

    // sp = sp + 1
    char fakeCo = '0';
    incremento(sp, &fakeCo);
    
    // mar = sp = sp + 1; wr
    strcpy(mar, sp);
    
    // tos = mdr
    strcpy(tos, mdr);
}

void DUP(char *mar, char *sp, char *mdr, char *tos) {
    // sp = sp + 1
    char fakeCo = '0';
    incremento(sp, &fakeCo);

    // mar = sp = sp + 1
    strcpy(mar, sp);

    // mdr = tos; wr
    strcpy(mdr, tos);
}

void BYPUSH(char *h, char* byte, char *sp, char *mar, char *mdr, char* mbr, char *tos) {
    // sp = sp + 1
    char fakeCo = '0';
    incremento(sp, &fakeCo);


    // mar = sp + 1
    strcpy(mar, sp);

    // sp = mar = sp + 1
    strcpy(sp, mar);


    // fetch, insere diretamente em H os 8 bits recebidos e preenche ele com 0
    for (int i = 0, j = 0; i < 32; i++) {
        if (i < 24) {
            mbr[i] = '0';
        }
        else {
            mbr[i] = byte[j];
            j++;
        }
    }

    strcpy(h, mbr);

    // tos = h
    strcpy(tos, h);

    // mdr = tos = h; wr
    strcpy(mdr, tos);
}
