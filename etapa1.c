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

void processamentoEntradas(char * ir, char*a, char*b, unsigned int * aNum, unsigned int * bNum);
unsigned int calculoULA(int f0, int f1, char* A, char* B, char* co);
char* and(unsigned int A, unsigned int B);
char* or(unsigned int A, unsigned int B);
char* compleB(unsigned int B);
char* somaArit(unsigned int, unsigned int, char* co);


int main(){
    // A e B iniciais
    char b[] = "00000000000000000000000000000001";
    char a[] = "11111111111111111111111111111111";

    // leitura do arquivo
    char arquivo[] = "programa_etapa1.txt";
    FILE *leitura;
    leitura = fopen(arquivo, "r");
    
    if (leitura == NULL) printf("Erro ao abrir o arquivo.");     // checagem da abertura correta do arquivo

    int PC = 0;     // contador de programa
    char IR[7];     // registrador de instrução

    // o contador vai identificar qual linha do arquivo está sendo lido, enquanto o registrador da respectiva linha
    // armazena a palavra de 6 bits contida nela

    while (fgets(IR, sizeof(IR), leitura) != NULL) {
        PC++;
        // a ideia aqui é fazer os passos 2, 3, 4 e 5
        unsigned int aNum;
        unsigned int bNum;
        processamentoEntradas(IR, a, b, &aNum, &bNum);
    }

    fclose(leitura);
    return 0;
}

unsigned int calculoULA(int f0, int f1, char* A, char* B, char* co){
    unsigned int s = 0; // Saída do programa

    *co = 0;

    // direcionando para a operação correta a partir das entradas F0 e F1
    if(f0 == 0 && f1 == 0){ // AND
        s = A & B;
    }

    if(f0 == 0 && f1 == 1){ // OR
        s = A | B;
    }

    if(f0 == 1 && f1 == 0){ // B complemento
        s = ~B;
    }

    if(f0 == 1 && f1 == 1){ // SUM
        
    }

    return s;
}

void processamentoEntradas(char * ir, char*a, char*b, unsigned int * aNum, unsigned int * bNum){ 
    // Separando as  instruções em variáveis e convertendo para inteiro.
    int f0 = ir[0] - '0';
    int f1 = ir[1] - '0';
    
    int ena  = ir[2] - '0';
    int enb  = ir[3] - '0';
    int inva = ir[4] - '0';
    int inc  = ir[5] - '0';

    // convertendo A e B para unsigned int ( 32 bits ) para aplicar as operações.
    // strtoul converte uma string para um unsigned long. 
    // os parâmetros são a string, um ponteiro para onde a conversao parou (irrelevante no projeto) e a base numérica para qual será convertida. 2 = base binária.
    *aNum = strtoul(a, NULL, 2);  
    *bNum = strtoul(b, NULL, 2); 
    
    // aplicando os enables.
    if(!ena) *aNum = 0;
    if(!enb) *bNum = 0;
    
    //invertendo A bit a bit caso INVA == 1. o operador '~' cumpre essa função.
    if(inva) *aNum = ~(*aNum);

    // aplicando o inc para ser mudado apenas no cáculo ULA
    char co = 0;

    unsigned int s = calculoULA(f0, f1, *aNum, *bNum, &co);
}