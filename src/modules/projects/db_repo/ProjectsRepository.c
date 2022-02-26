#include "project.h"
#include "server.h"

int addProject(char *name, char *lang, t_project *project)
{
	char query[100];
	MYSQL *con = mysql_init(NULL);

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "INSERT INTO `projects` VALUES(NULL, '%s', '%s');", name, lang);
	if(mysql_query(con, query)){
		mysql_close(con);
		return(-1);
	}
	sprintf(query, "SELECT * FROM `projects` WHERE name = \"%s\" ORDER BY id DESC  LIMIT 1;", name);
	mysql_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	if	(result == NULL) {
		return(-1);
	}
	MYSQL_ROW row;
	while((row = mysql_fetch_row(result))) {
		project->id = ft_strdup(row[0]);
		project->name = ft_strdup(row[1]);
		project->lang = ft_strdup(row[2]);
	}
	mysql_free_result(result);
	mysql_close(con);
	return(0);
}

int delProject (int id)
{
	MYSQL *con = mysql_init(NULL);
	char query[100];

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "DELETE FROM `projects` WHERE `projects`.`id` = %d;", id);
	if (mysql_query(con, query)) {
		mysql_close(con);
		return(-1);
	}
	uint64_t result = mysql_affected_rows(con);
	if	(result <= 0) {
		return(-1);
	}
	mysql_close(con);
	return(0);
}

int editProject (int id, char *name, t_project *project)
{
	MYSQL *con = mysql_init(NULL);
	char query[100];
	MYSQL_ROW row;
	
	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "UPDATE `projects` SET `name` = \"%s\" WHERE `projects`.`id` = %d;", name, id);
	if(mysql_query(con, query)){
		mysql_close(con);
		return(1);
	}
	sprintf(query, "SELECT * FROM `projects` WHERE id = %d ORDER BY id DESC  LIMIT 1;", id);
	mysql_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	if	(result == NULL) {
		return(-1);
	}
	while((row = mysql_fetch_row(result))) {
		project->id = ft_strdup(row[0]);
		project->name = ft_strdup(row[1]);
		project->lang = ft_strdup(row[2]);
	}
	mysql_free_result(result);
	mysql_close(con);
	return(0);
}

int searchProject (t_res *res)
{
	MYSQL *con = mysql_init(NULL);

	if (connect_mysql(con) < 0)
		return(-1);
	if (mysql_query(con, "SELECT * FROM projects;"))
	{
		mysql_close(con);
		return(-1);
	}
	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL){
		mysql_close(con);
		return(-1);
	}
	format_search(result, res);
	mysql_free_result(result);
	mysql_close(con);
	return(0);
}