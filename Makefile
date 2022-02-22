NAME = server

HEADER = -I ./src/header/
SRC = server.c libs/mongoose/*.c controller/*.c routes/*.c services/* \
	logs/GenerateLog.c libs/utils/* error/*.c

LIB_SQL = `mysql_config --cflags --libs`
LIB_JSON = -I/usr/include/json-c -L/usr/lib -ljson-c
MYSQL = src/db/create.c
MYSQLCHECK = src/db/check.c

all:
	gcc $(HEADER) $(addprefix src/,$(SRC)) $(LIB_JSON) -g3 && ./a.out 

mysql:
	gcc $(MYSQL) $(LIB_SQL) -o create_db

mysqlcheck:
	gcc $(MYSQLCHECK) $(LIB_SQL) -o check_db

install:
	sudo apt install libjson-c-dev && sudo apt install default-libmysqlclient-dev && \
	sudo apt install libmariadb-dev

.PHONY: install mysql all