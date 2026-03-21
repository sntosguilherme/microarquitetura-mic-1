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

// Protótipos das funções

// aplica ENA, ENB, INVA em A e B.
// por meio de f0 e f1 determina qual operacao sera realizada em A e B.
// recebe F1, F2, A e B para poder repassar esses parâmetros caso necessário
// retorna saída

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processamentoEntradas(char* ir, char* a, char* b);
char* calculoULA(int f0, int f1, char* a, char* b, char* co);
char* somaArit(char* a, char* b, char* co);
void printBits(unsigned int n);

void log(int pc, char* ir, char* a, char* b, char* s, char* co) {
    if (!pc) {
        printf("a = %s\n", a);
        printf("b = %s\n\n", b);

        printf("Começando!!!!\n");
    }

    printf("==============================================\n\n");
    printf("Ciclo %d\n\n", pc);
    printf("IR = %s\n", ir);
    printf("b = %s\n", b);
    printf("a = %s\n", a);
    printf("s = %s\n", s);
    printf("co = %d\n\n", co);
    printf("==============================================\n");
}


void inversor(char *a) {
    // inverte 1 para 0 e 0 para 1 enquanto não achar o fim da string
    for(int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '0') {
            a[i] = '1';
        }
        else {
            a[i] = '0';
        }
    }
}

void and(char* a, char* b, char* s){
    // lógica do operador AND
    for (int i = 0; i < 32; i++) {
        if (a[i] == '1' && b[i] == '1') {
            s[i] = '1';
        }
        else {
            s[i] = '0';
        }
    }

    s[32] = '\0';

    return s;
}


int main(){
    char b[] = "00000000000000000000000000000001";
    char a[] = "11111111111111111111111111111111";

    // leitura do arquivo
    char arquivo[] = "programa_etapa1.txt";
    FILE *leitura;
    leitura = fopen(arquivo, "r");
    
    if (leitura == NULL) 
        printf("Erro ao abrir o arquivo.");     // checagem da abertura correta do arquivo

    int PC = 0;     // contador de programa
    char IR[7];     // registrador de instrução
    unsigned int S; // saida

    while (fgets(IR, sizeof(IR), arquivo)) {
        PC++;
        // a ideia aqui é fazer os passos 2, 3, 4 e 5
        unsigned int s;

        char co = '0';
        int f0 = IR[0] - '0';
        int f1 = IR[01] - '0';
        
        processamentoEntradas(IR, &a, &b);
        s = calculoULA(f0, f1, a, b, &co);

        printBits(s);
    }

    fclose(leitura);
    return 0;
}

char * calculoULA(int f0, int f1, char *a, char *b, char *co){
    char *s; // Saída do programa

    // direcionando para a operação correta a partir das entradas F0 e F1
    if(f0 == 0 && f1 == 0){ // AND
        and(a, b, s);
    }

    if(f0 == 0 && f1 == 1){ // OR

    }

    if(f0 == 1 && f1 == 0){ // B complemento
        inversor(b);
    }

    if(f0 == 1 && f1 == 1){ // SUM
        
    }

    return s;
}

void processamentoEntradas(char* ir, char* a, char* b){ 
    // Separando as  instruções em variáveis e convertendo para inteiro.
    int ena  = ir[2] - '0';
    int enb  = ir[3] - '0';
    int inva = ir[4] - '0';
    int inc  = ir[5] - '0';

    // convertendo A e B para unsigned int ( 32 bits ) para aplicar as operações.
    // strtoul converte uma string para um unsigned long. 
    // os parâmetros são a string, um ponteiro para onde a conversao parou (irrelevante no projeto) e a base numérica para qual será convertida. 2 = base binária.
    // *aNum = strtoul(a, NULL, 2);  
    // *bNum = strtoul(b, NULL, 2); 
    
    // aplicando os enables.
    if(!ena) *a = "00000000000000000000000000000000";
    if(!enb) *b = "00000000000000000000000000000000";
    
    //if(inva) *a = ~(*a); CHAMAR FUNÇÃO DE INVERTER NUMERO POR STRING
    if (inva) inversor(a);
}

char * somaArit(char * a, char * b, char * co) {
    int carry = 0, soma;
    char s[33]; // string da saída

    // processamento de cada caractere da direita para esquerda, guardando o carry
    for (int i = 31; i >= 0; i--) {
        if (a[i] != b[i]) soma = 1; // simula o a^b
        else soma = 0;

        if (carry) {
            carry = soma && carry;
            soma = soma^1;
        }

        else {
            if (a[i] == '1' && b[i] == '1') carry = 1;
            else carry = 0;
        }

        // insere o resultado na saída
        s[i] = soma + '0';
    }
    s[32] = '\0';

    *co = carry + '0';

    return s;
}

// talvez n precise mas vou deixar aqui por enquanto
void printBits(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        int k = n >> i; // move os bits pra direita
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}