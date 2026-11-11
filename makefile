VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g
CC = gcc
PUERTO = 8080

ARCHIVO ?= ./pruebas/archivos/pokemones.csv


TP1_SRC = src/lista.c src/tp1_corregido/leer_linea.c src/tp1_corregido/tp1.c
TP1_TESTS = pruebas/pa2m.c pruebas/pruebas_alumno.c pruebas/pruebas_tp1/*.c

all: clean valgrind-demo

valgrind-demo: demo
	valgrind $(VALGRIND_FLAGS) ./demo $(PUERTO)

demo: main.c extra/engine.c extra/engine.h
	$(CC) $(CFLAGS) main.c extra/engine.c -o demo

pruebas: pruebas_alumno
	./pruebas_alumno

valgrind_alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas/*.c  
	$(CC) $(CFLAGS) src/*.c pruebas/*.c -o pruebas_alumno

main: main.c src/*.c
	$(CC) $(CFLAGS) main.c src/*.c -o main

ejecutar: main
	./main "$(ARCHIVO)"


clean:
	rm -f demo pruebas_alumno main




