#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "database.h"

char *get_host()
{
	char	hostbuffer[256];
	char	*IPbuffer;
	struct	hostent *host_entry;
	int		hostname;

	hostname = gethostname(hostbuffer, sizeof(hostbuffer));
	host_entry = gethostbyname(hostbuffer);
	IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
	return(IPbuffer);
}

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

int main(int argc, char **argv)
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	if (mysql_real_connect(con, HOST, USER, PASS, DB, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	else
	{
		printf("DB: Connected.\n");
	}
	if (mysql_query(con, "DROP TABLE IF EXISTS projects")) {
		finish_with_error(con);
	}
	else
	{
		printf("DB: Table projects dropped.\n");
	}
	//executa a query, no caso criar a table da db
	if (mysql_query(con, "CREATE TABLE projects(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), lang VARCHAR(255))")) {
		finish_with_error(con);
	}
	else
	{
		printf("DB: Table projects created.\n");
	}
	if (mysql_query(con, "DROP TABLE IF EXISTS users")) {
		finish_with_error(con);
	}
	else
	{
		printf("DB: Table users dropped.\n");
	}
	//executa a query, no caso criar a table da db
	if (mysql_query(con, "CREATE TABLE users(id INT PRIMARY KEY AUTO_INCREMENT, user VARCHAR(255) UNIQUE, password VARCHAR(255))")) {
		finish_with_error(con);
	}
	else
	{
		printf("DB: Table users created.\n");
	}
	if (mysql_query(con, "DROP TABLE IF EXISTS logs_api")) {
		finish_with_error(con);
	}
	else
	{
		printf("DB: Table logs_api dropped.\n");
	}
	//executa a query de criar a table do log
	if (mysql_query(con, "CREATE TABLE logs_api(id INT PRIMARY KEY AUTO_INCREMENT, method VARCHAR(255), uri VARCHAR(255), status VARCHAR(255), mensage VARCHAR(255), date VARCHAR(255))")) {
		finish_with_error(con);
	}
	else
	{
		printf("DB: Table logs_api created.\n");
	}
	
	//INSERT INTO projects VALUES(NULL,'min3italk',NOW());,

	//executa a query, dando insert em dado no db criado acima
	//id INT, nome CHAR 255, lang CHAR 255
	if (mysql_query(con, "INSERT INTO projects VALUES(1,'libft','c');\
	INSERT INTO projects VALUES(2,'gnl','c');\
	INSERT INTO projects VALUES(3,'printf','c');\
	INSERT INTO projects VALUES(4,'printf','c');\
	INSERT INTO projects VALUES(5,'b2br','c');\
	INSERT INTO projects VALUES(6,'solong','c');\
	INSERT INTO projects VALUES(7,'minitalk','c');"
	)) {
		finish_with_error(con);
	}
		else
	{
		printf("DB: Data insertion ok.\n");
	}
	//fechamos a conec
	mysql_close(con);
	printf("DB: Conection closed. Exiting...\n");
	exit(0);
}
