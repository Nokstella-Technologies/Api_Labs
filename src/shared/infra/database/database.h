#ifndef DATABASE_H
# define DATABASE_H

#define USER "root"
#define HOST "192.168.0.15"
#define PORT 3306
#define PASS "mariadb"
#define DB "42api"

#include <mysql/mysql.h>

int connect_mysql(MYSQL *con);

#endif