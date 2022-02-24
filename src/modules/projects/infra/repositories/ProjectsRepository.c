
#include "project.h"
#include "server.h"

static void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

int connect_mysql(MYSQL *con)
{
	if (mysql_real_connect(con, HOST, USER, PASS, DB, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return(-1);
	}
	return(0);
}

int addProject(char *name, t_project *project)
{
	char query[90];
	MYSQL *con = mysql_init(NULL);;

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "INSERT INTO `projects` VALUES(NULL, '%s', 'c');", name);
	if(mysql_query(con, query)){
		finish_with_error(con);
		mysql_close(con);
		return(-1);
	}
	sprintf(query, "SELECT * FROM `projects` WHERE name = \"%s\" ORDER BY id DESC  LIMIT 1;", name);
	mysql_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	if	(result == NULL) {
		finish_with_error(con);
		return(-1);
	}
	MYSQL_ROW row;
	MYSQL_FIELD *line = mysql_fetch_field(result);
	while((row = mysql_fetch_row(result))) {
		project->id = ft_strdup(row[0]);
		project->name = ft_strdup(row[1]);
		project->c = ft_strdup(row[2]);
	}
	mysql_free_result(result);
	mysql_close(con);
	return(0);
}

int delProject (int id)
{
	MYSQL *con = mysql_init(NULL);
	char query[64];

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "DELETE FROM `projects` WHERE `projects`.`id` = %d;", id);
	if(mysql_query(con, query)){
		finish_with_error(con);
		mysql_close(con);
		return(1);
	}
	mysql_close(con);
	return(0);
}

int editProject (int id, char *name, t_project *project);
{
	MYSQL *con = mysql_init(NULL);
	char query[64];
	
	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "UPDATE `projects` SET `name` = %s WHERE `projects`.`id` = %d;", name, id);
	if(mysql_query(con, query)){
		finish_with_error(con);
		mysql_close(con);
		return(1);
	}
	printf("1 line affected.");
	mysql_close(con);
	return(0);
}

int searchProject (int *id, char *name)
{
	MYSQL *con = mysql_init(NULL);
	char query[64];

	if (connect_mysql(con) < 0)
		return(-1);
	if (mysql_query(con, "SELECT * FROM projects;"))
	{
		finish_with_error(con);
 	}
	printf("1 line affected.");
	mysql_close(con);
	return(0);
}