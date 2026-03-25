#include "etapa1.h"

void logCiclo2(int pc, char* ir, char* a, char* b, char* s, char* sd, char co, int n, int z, FILE* log);
void deslocaSRA1(char* s);
void deslocaSLL8(char* s);


void logCiclo2(int pc, char* ir, char* a, char* b, char* s, char* sd, char co, int n, int z, FILE* log) {

    if (pc == 1) {
        fprintf(log, "b = %s\n", b);
        fprintf(log, "a = %s\n\n", a);

        fprintf(log, "Comecando!!!!\n");
        fprintf(log,"==============================================\n\n");
    }

    fprintf(log,"Ciclo %d\n\n", pc);
    fprintf(log,"PC = %d\n", pc);
    fprintf(log,"IR = %s\n", ir);
    fprintf(log,"b = %s\n", b);
    fprintf(log,"a = %s\n", a);
    fprintf(log,"s = %s\n", s);

    if (sd) fprintf(log, "sd = %s\n", sd); // printa o s deslocado se houver
    
    fprintf(log,"co = %c\n\n", co);
    fprintf(log,"==============================================\n");

}
