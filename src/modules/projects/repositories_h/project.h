
#ifndef PROJECT_H
#define PROJECT_H

#define USER "root"
#define HOST "172.19.105.35"
#define PORT 3386
#define PASS "mariadb"
#define DB "42api"

#include <mysql/mysql.h>

int	addProject(char *name);

#endif