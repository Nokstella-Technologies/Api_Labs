NAME = server
HEADER = -I ./src/includes -I ./libs/mongoose/

SRC = shared/server.c shared/routes/*.c shared/middlewares/*.c \
	shared/error/*.c /utils/GenerateLog.c utils/*/*.c modules/*/*/*.c \
	database/connection.c

LIB_MONG =  libs/mongoose/*.c 
LIB_SQL = `mysql_config --cflags --libs`
LIB_JSON = -I/usr/include/jansson -ljansson -lssl -lcrypto -lrhonabwy
MYSQL = src/database/create.c
all: mysql logs2 logs
	gcc $(HEADER) $(MODELS) $(addprefix src/,$(SRC)) $(LIB_SQL) $(LIB_MONG) $(LIB_JSON) -g3 -Wall -Werror -Wextra -o $(NAME)

cp_logs:
	cp ./Cli/Logs2 /usr/local/bin
	cp ./Cli/Logs /usr/local/bin

mysql:
	gcc $(MYSQL) $(LIB_SQL) $(HEADER) -o create_db

logsLocal:
	make -C ./Cli
	make -C ./Cli logs
	cp ./Cli/Logs2 ./
	cp ./Cli/Logs ./

logs:
	make -C ./Cli

logs2:
	make -C ./Cli logs

install:
	sudo apt install -y libcurl4-gnutls-dev libmicrohttpd-dev openssl net-tools default-libmysqlclient-dev && cd libs && mkdir jansson && cd jansson && wget https://github.com/akheron/jansson/releases/download/v2.14/jansson-2.14.tar.gz && tar -xf jansson-2.14.tar.gz && cd jansson-2.14 && ./configure && make && make install && cd .. && cd .. && rm -rf jansson && cd rhonabwy && dpkg -i liborcania-dev_2.2.1_ubuntu_focal_x86_64.deb && dpkg -i libyder-dev_1.4.14_ubuntu_focal_x86_64.deb && dpkg -i libulfius-dev_2.7.6_ubuntu_focal_x86_64.deb && dpkg -i librhonabwy-dev_1.1.2_ubuntu_focal_x86_64.deb && cd .. && cd .. && make && apt update && apt upgrade -y

clean:
	rm server create_db Logs Logs2 ./Cli/Logs ./Cli/Logs2

re: clean make

.PHONY: all install mysql logs logs2 clean re logsLocal