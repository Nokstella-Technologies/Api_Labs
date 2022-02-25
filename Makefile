NAME = server
HEADER = -I ./src/includes -I ./libs/mongoose/

SRC = shared/server.c shared/routes/*.c shared/middlewares/*.c \
	utils/GenerateLog.c utils/*/*.c modules/*/*/*.c  database/connection.c

SRC_LOGS = Cli/logs/*.c
LIB_MONG =  libs/mongoose/*.c 
LIB_SQL = `mysql_config --cflags --libs`
LIB_JSON = -I/usr/include/jansson -ljansson  -lssl -lcrypto -lrhonabwy
MYSQL = src/shared/infra/database/create.c
MYSQLCHECK = src/shared/infra/database/check.c

all:
	gcc $(HEADER) $(MODELS) $(addprefix src/,$(SRC)) $(LIB_SQL) $(LIB_MONG) $(LIB_JSON) -g3 -o $(NAME)

run:
	./$(NAME)
mysql:
	gcc $(MYSQL) $(LIB_SQL) -o create_db

mysqlcheck:
	gcc $(MYSQLCHECK) $(LIB_SQL) -o check_db



install:
	sudo apt install libjson-c-dev && sudo apt install default-libmysqlclient-dev && sudo apt install libmariadb-dev && sudo apt install autoreconf
	cd libs && mkdir jansson
	cd libs/jansson && wget https://github.com/akheron/jansson/releases/download/v2.14/jansson-2.14.tar.gz && tar -xf jansson-2.14.tar.gz
	cd libs/jansson/jansson-2.14 && ./configure && make && sudo make install
	

	cd libs && git clone git@github.com:benmcollins/libjwt.git libjwt
	cd libjwt && autoreconf -i
	

logs:
	gcc $(SRC_LOGS) -o Logs
.PHONY: install mysql all logs