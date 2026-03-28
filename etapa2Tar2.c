/*    
Etapa2 - Tarefa2:
    Novos registradores:
        9 de 32 bits    ->  H, OPC, TOS, CPP, LV, SP, PC, MDR e MAR
        H: Holding. Armazena dados que estão sendo transferidos pela memória
        MAR: Memory Address Register. Guarda o endereço onde a leitura ou escrita na memória será realizada.
        MDR: Memory Data Register. Guarda o dado que acabou de vir da memória ou que será enviado para ela.
        PC: Program Counter. Endereço da próxima instrução que a máquina buscará.
        1 de 8 bits     ->  MBR (ele vai ser completado os 32 bits dependendo do barramento B)
        MBR: Recebe apenas 8 bits. Pode Entrar no barramento de 2 maneiras:
            Forma 1: O bit mais à esquerda (índice 0 da string de 8 bits) é repetido 24 vezes antes do valor original.
            Forma 2: Quando o byte é apenas um índice ou valor positivo. Preenche os 24 bits da esquerda com 0. 

    Vamos receber agora palavras de 21 bits: 8 bits de controle da ULA, 9 bits barramento c, 4 bits barramento B
        - Bits do controle da ULA vão ser o que já temos implementado;
        - Controle do barramento C vai nos dizer quais registradores vão ser sobrescritos pelo Sd (saída deslocada) depois do processamento da ULA;
        - Controle do barraamento B vai dizer qual registrador será o valor da entrada B

    A entrada A agora será o valor armazenado no registrador H.
*/

#include "etapa2Tar2.h"

int main() {

    int PC = 0;     // contador de programa
    char IR[23];    // registrador de instrução
    char s[33];     // saida
    char sd[33];    // saida deslocada
    int f0;
    int f1;
    int sll8;       // deslocamento de 8 bits para esquerda
    int sra1;       // deslocamento aritmético em 1 bit pra direita
    char co;

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

    // leitura do arquivo
    char arquivo[] = "exemplos_projeto/programa_etapa2_tarefa2.txt";
    FILE *leitura;
    leitura = fopen(arquivo, "r");

    if (leitura == NULL) {
        printf("Erro ao abrir o arquivo de instrucoes."); // checagem da abertura correta do arquivo
        return 1;
    }

    // abertura do arquivo de saida do log
    FILE * log = fopen("saidas-etapa2/tarefa2.txt", "w");
    if(!log) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    while (fgets(IR, sizeof(IR), leitura) != NULL) {
        char b_bus[5];
        char c_bus[10];
        
        co = '0';
        sll8 = IR[0] - '0';
        sra1 = IR[1] - '0';
        f0 = IR[2] - '0';
        f1 = IR[3] - '0';

        if (erro2(ciclo, IR, log)) 
            continue;
        
        strcpy(a, h);
        
        barramentoB(IR, b, b_bus, opc, tos, cpp, lv, sp, pc, mdr, mar, mbr);

        processarC_bus(IR, c_bus);

        logEntrada(IR, ciclo, b_bus, c_bus, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
        
        processamentoEntradas2(IR, a, b);

        calculoULA(f0, f1, a, b, &co, s);

        if (IR[7] == '1') incremento(s, &co);

        strcpy(sd, s);

        if (sll8) deslocaSLL8(sd);
        if (sra1) deslocaSRA1(sd);

        barramentoC(IR, sd, c_bus, h, opc, tos, cpp, lv, sp, pc, mdr, mar);

        logFinal(mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);

        ciclo++;
    }

    printf("log armazenado com sucesso em entrada-e-saida/saida.txt.\n");
    fclose(leitura);
    fclose(log);
    return 0;
}