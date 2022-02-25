
#include "users.h"

int addUsers(char *name, unsigned char *password, t_users *users)
{
	char query[300];
	MYSQL *con = mysql_init(NULL);

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "INSERT INTO `users` (`id`, `user`, `password`) VALUES(NULL, '%s', '%s');", name, password);
	if(mysql_query(con, query)){
		mysql_close(con);
		return(-1);
	}
	sprintf(query, "SELECT * FROM `users` WHERE user = \"%s\" ORDER BY id DESC  LIMIT 1;", name);
	mysql_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	if	(result == NULL) {
		return(-1);
	}
	MYSQL_ROW row;
	MYSQL_FIELD *line = mysql_fetch_field(result);
	while((row = mysql_fetch_row(result))) {
		users->id = ft_strdup(row[0]);
		users->name = ft_strdup(row[1]);
		users->password = ft_strdup(row[2]);
	}
	mysql_free_result(result);
	mysql_close(con);
	return(0);
}

int delUsers(int id)
{
	MYSQL *con = mysql_init(NULL);
	char query[100];

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "DELETE FROM `users` WHERE `users`.`id` = %d;", id);
	if(mysql_query(con, query)){
		mysql_close(con);
		return(1);
	}
	mysql_close(con);
	return(0);
}

int findUser(char *name, char *password, t_users *users)
{
	char query[100];
	MYSQL *con = mysql_init(NULL);

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "SELECT * FROM `users` WHERE user = \"%s\";", name);
	if(mysql_query(con, query)){
		mysql_close(con);
		return(-1);
	}
	MYSQL_RES *result = mysql_store_result(con);
	if	(result == NULL) {
		return(-1);
	}
	MYSQL_ROW row;
	MYSQL_FIELD *line = mysql_fetch_field(result);
	while((row = mysql_fetch_row(result))) {
		users->id = ft_strdup(row[0]);
		users->name = ft_strdup(row[1]);
		users->password = ft_strdup(row[2]);
	}
	if(users->id == NULL)
		return(-1);
	mysql_free_result(result);
	mysql_close(con);
	return(0);
}