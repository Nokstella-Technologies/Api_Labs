#include "database.h"

int connect_mysql(MYSQL *con)
{
	if (mysql_real_connect(con, HOST, USER, PASS, DB, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		mysql_close(con);
		return(-1);
	}
	return(0);
}
