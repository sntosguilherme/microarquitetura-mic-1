#include "etapa3.h" 

/* 
NOVO FORMATO DA MICROINSTRUÇÃO - 23 bits

ULA - 8 bits
Barramento C - 9 bits
Memória - 2 bits
Barramento B - 4 bits

Como estão organizados os 2 bits de memória: 
IR[17]-> x1: WRITE -> no dados.txt, sobrescreve o endereço indicado por MAR pelo valor em MDR 
IR[18]-> x2: READ -> sobrescreve o registrador MDR pelo endereço indicado por MAR no dados.txt

Os dois não podem estar em nível lógico alto simultaneamente.
(ocorrem DEPOIS do processamento da instrução , o endereço indicado por MAR pelo oq eu entendi é o valor em decimal dele q corresponde a linha no arquivo de memória, começando da linha 0)

 
*/

int main() {

    char IR[25];    // Agora para 23 bits + \n + \0
    char s[33];     // saida
    char sd[33];    // saida deslocada
    int f0;
    int f1;
    int sll8;       // deslocamento de 8 bits para esquerda
    int sra1;       // deslocamento aritmético em 1 bit pra direita
    char co;
    char memoria_dados[8][33]; // Memória de 8 linhas de 32 bits.

    char a[33]; 
    char b[33];

    int ciclo = 1;

    char h[]   = "00000000000000000000000000000000";
    char opc[] = "00000000000000000000000000000000";
    char tos[] = "00000000000000000000000000000000";
    char cpp[] = "00000000000000000000000000000000";
    char lv[]  = "00000000000000000000000000000000";
    char sp[]  = "00000000000000000000000000000100";
    char pc[]  = "00000000000000000000000000000000";
    char mdr[] = "00000000000000000000000000000000";
    char mar[] = "00000000000000000000000000000100";
    char mbr[] = "00000000";

    // Carregando inicialmente a memória. Cada loop pega uma linha inteira do arquivo.
    FILE *dados = fopen("entrada/dados_etapa3_tarefa1.txt", "r");
    
    if (!dados) {
        printf("Erro ao obter os valores da memoria.\n");
        return 1;
    }
    for (int i = 0; i < 8; i++) {
        fscanf(dados, "%s", memoria_dados[i]);
    }
    fclose(dados);
    

    // Abrindo arquivo para leitura
    char arquivo[] = "entrada/microinstrucoes_etapa3_tarefa1.txt";
    FILE *leitura;
    leitura = fopen(arquivo, "r");

    if (!leitura) {
        printf("Erro ao abrir o arquivo de instrucoes.\n"); // checagem da abertura correta do arquivo
        return 1;
    }

    // abertura do arquivo de saida do log
    FILE * log = fopen("saidas/tarefa1.txt", "w");
    if(!log) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    // Converter os 4 ultimos bits de MAR para um número de 0 a 15 correspondente a linha da memória. deve ser posto no loop de execução

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
        
        barramentoBE3(IR, b, b_bus, opc, tos, cpp, lv, sp, pc, mdr, mar, mbr);

        processarC_bus(IR, c_bus);

        logEntradaE3(memoria_dados, IR, ciclo, b_bus, c_bus, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);
        
        processamentoEntradas2(IR, a, b);

        calculoULA(f0, f1, a, b, &co, s);

        if (IR[7] == '1') incremento(s, &co);

        strcpy(sd, s);

        if (sll8) deslocaSLL8(sd);
        if (sra1) deslocaSRA1(sd);

        barramentoC(IR, sd, c_bus, h, opc, tos, cpp, lv, sp, pc, mdr, mar);

        wrMemoria(IR, mar, mdr, memoria_dados);

        logFinalE3(memoria_dados, mar, mdr, pc, mbr, sp, lv, cpp, tos, opc, h, log);

        ciclo++;
    }

    printf("log armazenado com sucesso em saidas/tarefa1.txt.\n");
    fclose(leitura);
    fclose(log);

    return 0;
}