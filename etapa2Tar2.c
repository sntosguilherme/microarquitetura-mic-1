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
    char arquivo[] = "exemplos_projeto/programa_etapa2_tarefa1.txt";
    FILE *leitura;
    leitura = fopen(arquivo, "r");

    if (leitura == NULL) {
        printf("Erro ao abrir o arquivo de instrucoes."); // checagem da abertura correta do arquivo
        return 1;
    }

    // abertura do arquivo de saida do log
    FILE * log = fopen("saidas-etapa2/tarefa1.txt", "w");
    if(!log) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    /*
    Dentro do loop será feito o seguinte para o log se assemelhar com o da prof.

    processamento de a e b
    barramento B

    log1 (mostra a instrução, vai printar o b_bus, c_bus e os registradores antes)

    */

    while (fgets(IR, sizeof(IR), leitura) != NULL) {

        // strcpy(h, a);
        if (!erro(pc, IR, log)) {

            // processamentoEntradas2(IR, a, b);
            
            // log, 
        }
    }
}