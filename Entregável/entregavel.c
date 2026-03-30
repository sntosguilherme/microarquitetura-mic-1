#include "entregavel.h"

int main() {
    int PC = 0;     // contador de programa
    char IR[25];    // Agora para 23 bits + \n + \0
    char s[33];     // saida
    char sd[33];    // saida deslocada
    int f0;
    int f1;
    int sll8;       // deslocamento de 8 bits para esquerda
    int sra1;       // deslocamento aritmético em 1 bit pra direita
    char memoria_dados[8][33]; // Memória de 8 linhas de 32 bits.

    char a[33]; 
    char b[33];

    int ciclo = 1;

    char h[]   = "00000000000000000000000000000001";
    char opc[] = "00000000000000000000000000000000";
    char tos[] = "00000000000000000000000000000010";
    char cpp[] = "00000000000000000000000000000000";
    char lv[]  = "00000000000000000000000000000000";
    char sp[]  = "00000000000000000000000000000000";
    char pc[]  = "00000000000000000000000000000000";
    char mdr[] = "00000000000000000000000000000000";
    char mar[] = "00000000000000000000000000000000";
    char mbr[] = "10000001";
    char co = '0';

    FILE *dados = fopen("entrada/dados_etapa3_tarefa1.txt", "r");
    if (!dados) {
        printf("Erro ao obter os valores da memoria.\n");
        return 1;
    }
    for (int i = 0; i < 8; i++) {
        fscanf(dados, "%s", memoria_dados[i]);
    }
    fclose(dados);

    FILE * leitura = fopen("entrada/instrucoes.txt", "r"); 
    if (!leitura) {
        printf("Erro ao abrir o arquivo de leitura.\n");
        return 1;
    }

    FILE * log = fopen("saida/saida-entregavel.txt", "w");
    if(!log) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    char instrucao[20];
    while (fscanf(leitura, "%s", instrucao) != EOF) {

            char b_bus[5];
            char c_bus[20];

            if(strcmp(instrucao, "ILOAD") == 0){
                int indice;

                // atribuindo as strings corretas para os barramentos B e C de acordo com ILOAD
                strcpy(b_bus,"lv");
                strcpy(c_bus,"mar,mdr");

                fscanf(leitura, "%d", &indice); // captura o 'x' do iload
                logEntradaEntregavel(memoria_dados,instrucao,ciclo,b_bus,c_bus,indice,NULL,mar,mdr,pc,mbr,sp,lv,cpp,tos,opc,h,log);
                ILOAD(h, indice, lv, mar, sp, tos, mdr, memoria_dados);
                logFinalEntregavel(memoria_dados, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
            }   

            else if (strcmp(instrucao, "DUP") == 0){ // DUP
                // atribuindo as strings corretas para os barramentos B e C de acordo com DUP
                strcpy(b_bus,"tos");
                strcpy(c_bus,"mdr,sp,mar");
                logEntradaEntregavel(memoria_dados,instrucao,ciclo,b_bus,c_bus,-1,NULL,mar,mdr,pc,mbr,sp,lv,cpp,tos,opc,h,log);
                DUP(mar, sp, mdr, tos, memoria_dados);
                logFinalEntregavel(memoria_dados, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
            }

            else if (strcmp(instrucao, "BIPUSH") == 0) { // BIPUSH
                char valor_binario[9]; // 8 bits + '\0'
                // atribuindo as strings corretas para os barramentos B e C de acordo com BIPUSH
                strcpy(b_bus,"mbr");
                strcpy(c_bus,"mdr,sp,mar");
                fscanf(leitura, "%s", valor_binario);  // captura o valor de 8 bits da instrução BIPUSH
                logEntradaEntregavel(memoria_dados,instrucao,ciclo,b_bus,c_bus,-1,valor_binario,mar,mdr,pc,mbr,sp,lv,cpp,tos,opc,h,log);
                BIPUSH(h, valor_binario, sp, mar, mdr, mbr, tos, memoria_dados);
                logFinalEntregavel(memoria_dados, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
            }
    
            else{
                printf("Instrução desconhecida.\n", instrucao);
            }
            ciclo++;
    }
    printf("saida armazenada em saida/saida-entregavel.txt");
    
    fclose(leitura);
    fclose(log); 
    return 0;
}