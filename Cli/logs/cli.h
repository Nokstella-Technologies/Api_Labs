#ifndef CLI_H
# define CLI_H

# define FileLog "./logs/logs.txt"
# define Error 1
# define Sucess 2
# define USER "root"
# define HOST get_host()
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

typedef struct s_data {
	char	n_line[124];
	int		type;
}			t_data;

typedef struct s_project
{
	int	get;
	int	post;
	int	delete;
	int	put;
}		t_project;

typedef struct s_users
{
	int	post;
	int	delete;
}		t_users;

typedef struct s_routes {
	t_project project;
	t_users users;
	int	autheticated;
	int	other;
}			t_routes;

typedef struct s_unix {
	char	*method;
	char	*routes;
	char	*data;
	char	*status;
	int		list;
}			t_unix;

#endif