SRC = ./logs/clidb.c

SRC_LOGS = ./logs/main.c ./utils/ft_split.c ./utils/ft_strdup.c ./utils/ft_substr.c

all:
	gcc -I ./logs $(SRC) `mysql_config --cflags --libs` -o Logs2

logs:
	gcc -I ./logs $(SRC_LOGS) -o Logs

.PHONY: logs all