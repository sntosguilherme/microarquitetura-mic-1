CC = gcc
CFLAGS = -Wall -Wextra -I. -IEtapa1 -IEtapa2 -IEtapa3

# Target para testar todos
all: run-etapa1Tar1 run-etapa2 run-etapa2Tar1 run-etapa2Tar2 run-etapa3Tar1

# Target para limpeza dos binários
clean:
	rm -f Etapa1/etapa1Tar1 Etapa2/etapa2 Etapa2/etapa2Tar1 Etapa2/etapa2Tar2 Etapa3/etapa3Tar1
	rm -f Etapa1/saidas/*.txt Etapa2/saidas/*.txt Etapa3/saidas/*.txt

# Compilação e execução da Etapa 1 - Tarefa 1
Etapa1/etapa1Tar1: Etapa1/etapa1Tar1.c Etapa1/etapa1Tar1.h
	$(CC) $(CFLAGS) -o $@ $<

run-etapa1Tar1: Etapa1/etapa1Tar1
	cd Etapa1 && ./etapa1Tar1

# Compilação e execução da Etapa 2
Etapa2/etapa2: Etapa2/etapa2.c Etapa2/etapa2.h
	$(CC) $(CFLAGS) -o $@ $<

run-etapa2: Etapa2/etapa2
	cd Etapa2 && ./etapa2

# Compilação e execução da Etapa 2 - Tarefa 1
Etapa2/etapa2Tar1: Etapa2/etapa2Tar1.c Etapa2/etapa2Tar1.h
	$(CC) $(CFLAGS) -o $@ $<

run-etapa2Tar1: Etapa2/etapa2Tar1
	cd Etapa2 && ./etapa2Tar1

# Compilação e execução da Etapa 2 - Tarefa 2
Etapa2/etapa2Tar2: Etapa2/etapa2Tar2.c Etapa2/etapa2Tar2.h
	$(CC) $(CFLAGS) -o $@ $<

run-etapa2Tar2: Etapa2/etapa2Tar2
	cd Etapa2 && ./etapa2Tar2

# Compilação e execução da Etapa 3 - Tarefa 1
Etapa3/etapa3Tar1: Etapa3/etapa3Tar1.c Etapa3/etapa3.h
	$(CC) $(CFLAGS) -o $@ $<

run-etapa3Tar1: Etapa3/etapa3Tar1
	cd Etapa3 && ./etapa3Tar1

.PHONY: all clean run-etapa1Tar1 run-etapa2 run-etapa2Tar1 run-etapa2Tar2 run-etapa3Tar1
