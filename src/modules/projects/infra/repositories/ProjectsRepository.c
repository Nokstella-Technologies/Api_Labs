
#include "server.h"
#include "../../repositories_h/project.h"

static void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int addProject(char *name)
{
	MYSQL *con = mysql_init(NULL);
	char query[64];

	if (mysql_real_connect(con, HOST, USER, PASS, DB, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return(1);
	}
	sprintf(query, "INSERT INTO projects VALUES(NULL, '%s', 'c');", name);
	if(mysql_query(con, query)){
		finish_with_error(con);
		mysql_close(con);
		return(1);
	}
	mysql_close(con);
	return(0);
}