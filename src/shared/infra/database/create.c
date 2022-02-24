#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "database.h"

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{
	//conecta na db
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}	

	//infos de logins, passar pra define
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
