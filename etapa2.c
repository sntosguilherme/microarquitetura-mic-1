/* 
SLL8: desloca a saída S em 8 bits para a esquerda
SRA1: deslocamento aritmético para a direita em 1 bit, isso significa que o bit de sinal é preservado, exemplo depois
A: OPERANDO 1
B: OPERANDO 2
ENA: Enable A. Quando está em 0, qualquer valor em A é ignorado e se torna 0. 
ENB: Enable B. Quando está em 0, qualquer valor em B é ignorado e se torna 0.
INVA: Inverte A bit a bit.
INC: Guarda o vai-um. Soma 1 ao resultado final.
F0 e F1: Em conjunto definem a operação a ser realizada.

Conjunto de operações:
    F0 = 0 e F1 = 0  -> indica que a saída é igual a A && B (A and B)
    F0 = 0 e F1 = 1  -> indica que a saída é igual a A | B  (A or B)
    F0 = 1 e F1 = 0  -> indica que a saída é igual ao complemento de B
    F0 = 1 e F1 = 1  -> indica que a saída é igual a soma aritmética

Detalhe: 
    Nessa etapa 2, a ULA tem mais duas saídas N e Z,
        N = 1 quando a saída é negativa
        Z = 1 quando a saída é zero
    
    SLL8 e SRA1 nunca podem estar habilitadas simultaneamente
    
    Explicando SRA1. Ele preserva o sinal, por exemplo, 
        antes de SRA1: 1111 0010 
        depoi de SRA1: 1111 1001
    É como se o 1 mais a esquerda fosse propagado para a direita. 

    SLL8 só desloca 8 bits a esquerda, preenchendo com 0
        antes de SLL8: 1111 0010
        depoi de SLL8: 0000 0000

Planejamento da execução do programa

*/

#include "etapa2.h"

// Protótipos para visualizar melhor os tipos das funções

// logCiclo2 printa o S deslocado, se não houver desloc. passa NULL, n e z além do resto
void processamentoEntradas2(char * ir, char * a, char * b);
void deslocaSRA1(char* s);
void deslocaSLL8(char* s);
int erro(int pc, char* ir, char* a0, char* b0, char* a, char* b, int sll8, int sra1, FILE* log);
void logCiclo2(int pc, char* ir, char* a0, char* b0, char* a, char* b, char* s, char* sd, char co, int n, int z, FILE* log);

int main(){
    // Declarações

    int PC = 0;     // contador de programa
    char IR[10];    // registrador de instrução (tamanho 8 para 6bits, \0 e \n)
    char s[33];     // saida
    char sd[33];    // saida deslocada
    char co;        // carry on
    int f0;
    int f1;
    int sll8;       // deslocamento de 8 bits para esquerda
    int sra1;       // deslocamento aritmético em 1 bit pra direita
    int N = 0;          // fica 1 quando a saída é neg.
    int Z = 0;          // fica 1 quando a saída é apenas 0;

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

    // o contador vai identificar qual linha do arquivo está sendo lido, enquanto o registrador da respectiva linha
    // armazena a palavra de 6 bits contida nela

    while (fgets(IR, sizeof(IR), leitura) != NULL) {
        // b e a iniciais
        char b0[] = "10000000000000000000000000000000";
        char a0[] = "00000000000000000000000000000001";

        // cópias a serem mudadas
        char a[33], b[33];
        strcpy(a, a0);
        strcpy(b, b0);

        PC++;

        co = '0';
        sll8 = IR[0] - '0';
        sra1 = IR[1] - '0';
        f0 = IR[2] - '0';
        f1 = IR[3] - '0';
        
        // pensamento de como lidar com a checagem (NAO PODE SRA1 E SLL8 AO MSM TEMPO)
        /*  
            1:
                checar se ambos estão habilitados
                se estão, nada é feito e o log deve lidar
                se só um ou outro é habilitado chamar a devida função, func normal
            
            2:
                checar se ambos estão habilitados, se estiverem executar a função abaixo, se não, logCiclo2
                criar função erro, que é semelhante ao log mas apenas printa qual a linha, qual instrução foi feita e uma mensagem de erro

        */

        // se não der erro, ciclo será printado normalmente
        if (!erro(PC, IR, a0, b0, a, b, sll8, sra1, log)) {
            processamentoEntradas2(IR, a, b);
            calculoULA(f0, f1, a, b, &co, s);

            if (IR[7] == '1') incremento(s, &co);

            strcpy(sd, s);

            if (sll8) deslocaSLL8(sd);
            if (sra1) deslocaSRA1(sd);

            if (sd[0] == 1) N = 1;                                      // se for negativo
            if (!strcmp(sd, "00000000000000000000000000000000")) Z = 1; // se for zerado
            
            logCiclo2(PC, IR, a0, b0, a, b, s, sd, co, N, Z, log);
        }

    }

    printf("log armazenado com sucesso em entrada-e-saida/saida.txt.\n");
    fclose(leitura);
    fclose(log);
    return 0;
}