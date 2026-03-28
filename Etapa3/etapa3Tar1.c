#include "../Etapa2/etapa2Tar2.h" 

/* 
NOVO FORMATO DA MICROINSTRUÇÃO - 23 bits

ULA - 8 bits
Barramento C - 9 bits
Memória - 2 bits
Barramento B - 4 bits

Como estão organizados os 2 bits de memória: 
IR[21]-> x1: WRITE
IR[22]-> x2: READ
Os dois não podem estar em nível lógico alto simultaneamente.
 
*/

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
    char IR[25];    // Agora para 23 bits + \n + \0
    char s[33];
    char sd[33];
    char co = '0';
    char memoria_dados[8][33]; // Memória de 16 linhas de 32 bits.


    // Carregando inicialmente a memória. Cada loop pega uma linha inteira do arquivo.
    FILE *dados = fopen("entrada-e-saida-etapa3/dados_etapa3_tarefa1.txt", "r");
    
    if (!dados) {
        printf("Erro ao obter os valores da memoria.\n");
        return 1;
    }
    for (int i = 0; i < 8; i++) {
        fscanf(dados, "%s", memoria_dados[i]);
    }
    fclose(dados);
    

    // Abrindo arquivo para leitura
    char arquivo[] = "entrada-e-saida-etapa3/microinstrucoes_etapa3_tarefa1.txt";
    FILE *leitura;
    leitura = fopen(arquivo, "r");

    if (!leitura) {
        printf("Erro ao abrir o arquivo de instrucoes.\n"); // checagem da abertura correta do arquivo
        return 1;
    }

    // abertura do arquivo de saida do log
    FILE * log = fopen("entrada-e-saida-etapa3/tarefa1.txt", "w");
    if(!log) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    // Converter os 4 ultimos bits de MAR para um número de 0 a 15 correspondente a linha da memória. deve ser posto no loop de execução
    int obterEndereco(char *mar){
        // deve retornar o valor inteiro dos 3 últimos bits
    }

    return 0;
}