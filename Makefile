NAME = server

HEADER = -I ./src/header/
SRC = server.c libs/mongoose/*.c controller/*.c routes/*.c services/*

all:
	gcc $(HEADER) $(addprefix src/,$(SRC)) && ./a.out