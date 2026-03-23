/* OQ FAZ CADA COMPONENTE
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
    -co é carry on na saída (valor de vai um) para os mafiosos

Planejamento da execução do programa
    1- Armazenamento das variáveis iniciais A e B
    2- Abrir o arquivo de leitura, armazenar a linha e a palavra 
    3- Armazenamento da combinação de sinais
    4- Processamento das instruções 
    5- Escrita dos valores de IR, PC, A, B, S e o Vai-um no log
    6- Próxima linha
*/

#include "etapa1.h"

// Protótipos para visualizar melhor os tipos das funções
void processamentoEntradas(char * ir, char * a, char * b);
char* calculoULA(int f0, int f1, char * a, char * b, char* co, char *s);
void and(char* a, char* b, char* s);
void or(char * a, char * b, char *s);
void somaArit(char * a, char * b, char * co, char *s);
void incremento(char *s, char *co);
void inversor(char *a);
void zerar(char *a);
void logCiclo(int pc, char* ir, char* a, char* b, char* s, char co, FILE* log);

int main(){
    // Declarações

    // char b[33];  estão declaradas dentro do loop
    // char a[33];
    int PC = 0;     // contador de programa
    char IR[8];     // registrador de instrução (tamanho 8 para 6bits, \0 e \n)
    char s[33];     // saida
    char co;        // carry on
    int f0;
    int f1;

    // leitura do arquivo
    char arquivo[] = "entrada-e-saida/programa_etapa1.txt";
    FILE *leitura;
    leitura = fopen(arquivo, "r");
    
    if (leitura == NULL) {
        printf("Erro ao abrir o arquivo de instrucoes."); // checagem da abertura correta do arquivo
        return 1;
    }

    // abertura do arquivo de saida do log
    FILE * log = fopen("entrada-e-saida/saida.txt", "w");
    if(!log) {
        printf("Erro ao abrir o arquivo de log.\n");
        return 1;
    }

    // o contador vai identificar qual linha do arquivo está sendo lido, enquanto o registrador da respectiva linha
    // armazena a palavra de 6 bits contida nela

    while (fgets(IR, sizeof(IR), leitura) != NULL) {
        char b[] = "00000000000000000000000000000001";
        char a[] = "11111111111111111111111111111111";
        PC++;
        // a ideia aqui é fazer os passos 2, 3, 4 e 5

        co = '0';
        f0 = IR[0] - '0';
        f1 = IR[01] - '0';
        
        processamentoEntradas(IR, a, b);
        calculoULA(f0, f1, a, b, &co, s);

        if (IR[5] == '1') incremento(s, &co);

        logCiclo(PC, IR, a, b, s, co, log);
    }

    fclose(leitura);
    fclose(log);
    return 0;
}