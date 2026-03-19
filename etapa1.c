#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* OQ FAZ CADA COMPONENTE
A: OPERANDO 1
B: OPERANDO 2
ENA: Enable A. Quando está em 0, qualquer valor em A é ignorado e se torna 0. 
ENB: Enable B. Quando está em 0, qualquer valor em B é ignorado e se torna 0.
INVA: Inverte A bit a bit.
INC: Guarda o vai-um. Soma 1 ao resultado final.
F0 e F1: Em conjunto definem a operação a ser realizada.

Conjunto de operações:
    F0 = F1 = 0      -> indica que a saída é igual a A && B (A and B)
    F0 = 0 e F1 = 1  -> indica que a saída é igual a A + B 
    F0 = 1 e F1 = 0  -> indica que a saída é igual ao complemento de B

Planejamento da execução do programa
    1- Armazenamento das variáveis iniciais A e B
    2- Abrir o arquivo de leitura, armazenar a linha e a palavra 
    3- Armazenamento da combinação de sinais
    4- Processamento das instruções 
    5- Escrita dos valores de IR, PC, A, B, S e o Vai-um no log
    6- Próxima linha

*/


int main(){
    // A e B iniciais
    char b[] = "00000000000000000000000000000001";
    char a[] = "11111111111111111111111111111111";

    // leitura do arquivo
    char arquivo[] = "programa_etapa1.txt";
    FILE *leitura;
    leitura = fopen(arquivo, 'r');
    
    if (leitura == NULL) printf("Erro ao abrir o arquivo.");     // checagem da abertura correta do arquivo

    int PC = 0;     // contador de programa
    char IR[7];     // registrador de instrução

    // o contador vai identificar qual linha do arquivo está sendo lido, enquanto o registrador da respectiva linha
    // armazena a palavra de 6 bits contida nela

    fgets(IR, sizeof(IR), arquivo);
    while (strcmp(IR, NULL)) {
        PC++;
        // a ideia aqui é fazer os passos 2, 3, 4 e 5
    }

    fclose(leitura);
    return 0;
}