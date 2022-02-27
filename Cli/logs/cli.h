#ifndef CLI_H
# define CLI_H

# define FileLog "./logs/logs.txt"
# define Error 1
# define Sucess 2
# define USER "root"
# define HOST "0.0.0.0"
# define PORT 3306
# define PASS "mariadb"
# define DB "42api"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>


typedef struct s_routes {
	char	*method;
	char	*uri;
	char	*status;
	char	*data;
}			t_routes;

typedef struct s_unix {
	char	*method;
	char	*routes;
	char	*data;
	char	*status;
	int		list;
}			t_unix;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);

#endif