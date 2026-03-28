#include "entregavel.h"

int main() {
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
    char s[33];
    char sd[33];
    char co = '0';
    char memoria_dados[8][33]; // Memória de 8 linhas de 32 bits.



    FILE * leitura = fopen("exemplos_projeto/instrucoes.txt", "r"); 
    if (!leitura) {
        printf("Erro ao abrir o arquivo de leitura.\n");
        return 1;
    }

    char instrucao[20];
    while (fscanf(leitura, "%s", instrucao) != EOF) {
            if(strcmp(instrucao, "ILOAD") == 0){
                int indice;
                fscanf(leitura, "%d", &indice); // captura o 'x' do iload
                ILOAD(h, indice, lv, mar, sp, tos, mdr, memoria_dados);
            }

            else if (strcmp(instrucao, "DUP") == 0){ // DUP
                DUP(mar, sp, mdr, tos, memoria_dados);
            }

            else if (strcmp(instrucao, "BIPUSH") == 0) { // BIPUSH
                char valor_binario[9]; // 8 bits + '\0'
                fscanf(leitura, "%s", valor_binario);  // captura o valor de 8 bits da instrução BIPUSH
                BYPUSH(h, valor_binario, sp, mar, mdr, mbr, tos, memoria_dados);
            }
                
            else{
                printf("Instrução desconhecida.\n", instrucao);
            }
    }
    
    fclose(leitura);
    return 0;
}