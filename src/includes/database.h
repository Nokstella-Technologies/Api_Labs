
#ifndef DATABASE_H
# define DATABASE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

/**
 * Infos for the database 
 */
# define USER "root"
# define HOST getenv("IP") == NULL ? "0.0.0.0" : getenv("ENV")
# define PORT 3306
# define PASS "mariadb"
# define DB "42api"

# include <mysql/mysql.h>

/**
 * @brief this function connects with the database.
 * 
 * @param con a struct that is need to the connection.
 * @return int 0 for OK and -1 for error.
 */
int	connect_mysql(MYSQL *con);

#endif