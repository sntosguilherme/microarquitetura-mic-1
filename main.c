#include "etapa1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *leitura = fopen("exemplos_projeto/programa_etapa1.txt", "r");
    FILE *log = fopen("log.txt", "w");

    if (!leitura || !log) {
        printf("Erro ao abrir arquivos\n");
        return 1;
    }

    // 📌 Estado inicial (igual ao esperado)
    unsigned int A = strtoul("11111111111111111111111111111111", NULL, 2);
    unsigned int B = strtoul("00000000000000000000000000000001", NULL, 2);

    // 📌 Cabeçalho do log
    fprintf(log, "b = ");
    printBin(B, log);
    fprintf(log, "\n");

    fprintf(log, "a = ");
    printBin(A, log);
    fprintf(log, "\n\n");

    fprintf(log, "Start of Program\n");
    fprintf(log, "============================================================\n");

    char IR[8];
    int PC = 0;

    while (fgets(IR, sizeof(IR), leitura)) {
        IR[strcspn(IR, "\n")] = '\0';

        if (strlen(IR) == 0) {
            fprintf(log, "Cycle %d\n\n", PC + 1);
            fprintf(log, "PC = %d\n", PC + 1);
            fprintf(log, "> Line is empty, EOP.\n");
            break;
        }

        PC++;

        fprintf(log, "Cycle %d\n\n", PC);
        fprintf(log, "PC = %d\n", PC);

        processamentoEntradas(IR, &A, &B, log, PC);

        fprintf(log, "============================================================\n");
    }

    fclose(leitura);
    fclose(log);
    return 0;
}