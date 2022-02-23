NAME = server
HEADER = -I ./src/shared/infra/header/ -I ./libs/l8w8jwt/include/ -I ./libs/mongoose/ -I libs/l8w8jwt/lib/chillbuff/include/ -I libs/l8w8jwt/lib/checknum/include/ -I libs/l8w8jwt/lib/chillbuff/include/ -I libs/l8w8jwt/lib/jsmn/include/ -I libs/l8w8jwt/lib/chillbuff/include/ -I libs/l8w8jwt/lib/acutest/include/ -I  libs/l8w8jwt/lib/doxygen-awesone/include/ -I libs/l8w8jwt/lib/mbedtls/include/ -I  libs/l8w8jwt/lib/ed25519/include/

MODELS = -I ./src/modules/*/repositories/
SRC = shared/infra/http/server.c shared/infra/http/*/*.c modules/*/*/*.c \
	logs/GenerateLog.c shared/error/*.c modules/*/infra/*/*.c
SRC_LOGS = Cli/logs/*.c
LIB_MONG =  libs/mongoose/*.c libs/utils/*.c
LIB_SQL = `mysql_config --cflags --libs`
LIB_JSON = -I/usr/include/json-c -L/usr/lib -ljson-c
MYSQL = src/shared/infra/database/create.c
MYSQLCHECK = src/shared/infra/database/check.c

all:
	gcc $(HEADER) $(MODELS) $(addprefix src/,$(SRC)) $(LIB_SQL) $(LIB_MONG) $(LIB_JSON) -g3 -o $(NAME) && ./$(NAME) 

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