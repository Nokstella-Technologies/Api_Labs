NAME = server

HEADER = -I ./src/header/
SRC = server.c libs/mongoose/*.c controller/*.c routes/*.c services/* \
	logs/GenerateLog.c libs/utils/*

MYSQL = src/db/create.c

all:
	gcc $(HEADER) $(addprefix src/,$(SRC)) -g3 && ./a.out 

mysql:
	gcc $(MYSQL) `mysql_config --cflags --libs` -o create_bd
