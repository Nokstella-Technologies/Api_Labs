NAME = server
HEADER = -I ./src/includes -I ./libs/mongoose/

SRC = shared/server.c shared/routes/*.c shared/middlewares/*.c \
	shared/error/*.c \utils/GenerateLog.c utils/*/*.c modules/*/*/*.c \
	database/connection.c

LIB_MONG =  libs/mongoose/*.c 
LIB_SQL = `mysql_config --cflags --libs`
LIB_JSON = -I/usr/include/jansson -ljansson -lssl -lcrypto -lrhonabwy
MYSQL = src/database/create.c

all: mysql logs
	gcc $(HEADER) $(MODELS) $(addprefix src/,$(SRC)) $(LIB_SQL) $(LIB_MONG) $(LIB_JSON) -g3 -Wall -Werror -Wextra -o $(NAME)

mysql:
	gcc $(MYSQL) $(LIB_SQL) $(HEADER) -o create_db

logs:
	make -C ./Cli
	mv ./Cli/Logs ./Logs

logs2:
	make -C ./Cli logs
	mv ./Cli/Logs ./Logs

.PHONY: install mysql all logs logs2