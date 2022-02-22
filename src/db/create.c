#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

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
	if (mysql_real_connect(con, "192.168.0.15:3386", "root", "MariaDB", NULL, 3386, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	//executa a query, no caso criar db
	if (mysql_query(con, "CREATE TABLE projects(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), lang VARCHAR(255))")) {
		finish_with_error(con);
	}
	//executa a query, dando insert em dado no db criado acima
	//id INT, nome CHAR 255, lang CHAR 255
	if (mysql_query(con, "INSERT INTO projects VALUES(1,'libft','c')")) {
		finish_with_error(con);
	}
	//fechamos a conec
	mysql_close(con);
	exit(0);
}
