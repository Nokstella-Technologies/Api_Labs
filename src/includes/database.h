#ifndef DATABASE_H
# define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define USER "root"
#define HOST "192.168.0.15"
#define PORT 3306
#define PASS "mariadb"
#define DB "42api"

#include <mysql/mysql.h>

int connect_mysql(MYSQL *con);

#endif