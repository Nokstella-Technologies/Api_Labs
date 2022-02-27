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

/**
 * @brief Copy the from the (S + START) to (LEN).
 * 
 * @param s the address of the start of the string
 * @param start start the copy from here.
 * @param len number of the bytes to be copy.
 * @return a new address to with the copy.
 */
char			*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Function separe the string S in a Matrix with the separator C
 * 
 * @param s string to be splited
 * @param c the caracter that will be used to separate the string
 * @return a pointer to the other pointer that have all the parters of the
 * splited string S
 */
char			**ft_split(char const *s, char c);

/**
 * @brief Copy the STR to a new pointer.
 * 
 * @param str the string to be copy
 * @return a new address with the same string of str.
 */
char			*ft_strdup(const char *str);

#endif