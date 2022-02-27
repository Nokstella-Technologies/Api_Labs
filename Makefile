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

install:
	sudo apt install -y libcurl4-gnutls-dev libmicrohttpd-dev openssl net-tools default-libmysqlclient-dev && cd libs && mkdir jansson && cd jansson && wget https://github.com/akheron/jansson/releases/download/v2.14/jansson-2.14.tar.gz && tar -xf jansson-2.14.tar.gz && cd jansson-2.14 && ./configure && make && make install && cd .. && cd .. && rm -rf jansson && cd rhonabwy && dpkg -i liborcania-dev_2.2.1_ubuntu_focal_x86_64.deb && dpkg -i libyder-dev_1.4.14_ubuntu_focal_x86_64.deb && dpkg -i libulfius-dev_2.7.6_ubuntu_focal_x86_64.deb && dpkg -i librhonabwy-dev_1.1.2_ubuntu_focal_x86_64.deb && cd .. && cd .. && make && apt update && apt upgrade -y

.PHONY: install mysql all logs logs2