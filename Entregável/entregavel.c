#include "entregavel.h"

int main() {
    char memoria_dados[16][33]; // Memória de 16 linhas de 32 bits.

    char h[33], opc[33], tos[33], cpp[33], lv[33], sp[33], pc[33], mdr[33], mar[33];
    char mbr[9];
    int ciclo = 1;

    // Carregando memória de dados
    FILE *dados = fopen("entrada/dados_etapa3_tarefa1.txt", "r");
    if (!dados) {
        printf("Erro ao obter os valores da memoria.\n");
        return 1;
    }
    for (int i = 0; i < 16; i++) {
        fscanf(dados, "%s", memoria_dados[i]);
    }
    fclose(dados);

    // Carregando registradores do arquivo
    FILE *regs = fopen("entrada/registradores_etapa3_tarefa1.txt", "r");
    if (!regs) {
        printf("Erro ao abrir o arquivo de registradores.\n");
        return 1;
    }
    char nome_reg[10], igual[3];
    fscanf(regs, "%s %s %s", nome_reg, igual, mar);
    fscanf(regs, "%s %s %s", nome_reg, igual, mdr);
    fscanf(regs, "%s %s %s", nome_reg, igual, pc);
    fscanf(regs, "%s %s %s", nome_reg, igual, mbr);
    fscanf(regs, "%s %s %s", nome_reg, igual, sp);
    fscanf(regs, "%s %s %s", nome_reg, igual, lv);
    fscanf(regs, "%s %s %s", nome_reg, igual, cpp);
    fscanf(regs, "%s %s %s", nome_reg, igual, tos);
    fscanf(regs, "%s %s %s", nome_reg, igual, opc);
    fscanf(regs, "%s %s %s", nome_reg, igual, h);
    fclose(regs);

    // Abrindo arquivo de instruções
    FILE *leitura = fopen("entrada/instrucoes.txt", "r"); 
    if (!leitura) {
        printf("Erro ao abrir o arquivo de leitura.\n");
        return 1;
    }

    FILE *log = fopen("saida/saida-entregavel.txt", "w");
    if(!log) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    char instrucao[20];
    while (fscanf(leitura, "%s", instrucao) != EOF) {

            char b_bus[20];
            char c_bus[40];

            if(strcmp(instrucao, "ILOAD") == 0){
                int indice;

                strcpy(b_bus, "lv, sp");
                strcpy(c_bus, "h, mar, sp, tos");

                fscanf(leitura, "%d", &indice);
                logEntradaEntregavel(memoria_dados, instrucao, ciclo, b_bus, c_bus, indice, NULL, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
                ILOAD(h, indice, lv, mar, sp, tos, mdr, memoria_dados);
                logFinalEntregavel(memoria_dados, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
            }   

            else if (strcmp(instrucao, "DUP") == 0){
                strcpy(b_bus, "sp, tos");
                strcpy(c_bus, "mar, sp, mdr");
                logEntradaEntregavel(memoria_dados, instrucao, ciclo, b_bus, c_bus, -1, NULL, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
                DUP(mar, sp, mdr, tos, memoria_dados);
                logFinalEntregavel(memoria_dados, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
            }

            else if (strcmp(instrucao, "BIPUSH") == 0) {
                char valor_binario[9]; // 8 bits + '\0'
                strcpy(b_bus, "sp");
                strcpy(c_bus, "h, tos, mdr, sp, mar");

                fscanf(leitura, "%s", valor_binario);
                logEntradaEntregavel(memoria_dados, instrucao, ciclo, b_bus, c_bus, -1, valor_binario, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
                BIPUSH(h, valor_binario, sp, mar, mdr, mbr, tos, memoria_dados);
                logFinalEntregavel(memoria_dados, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
            }
    
            else{
                printf("Instrucao desconhecida: %s\n", instrucao);
            }
            ciclo++;
    }
    printf("saida armazenada em saida/saida-entregavel.txt\n");
    
    fclose(leitura);
    fclose(log); 
    return 0;
}