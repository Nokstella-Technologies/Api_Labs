#include "project.h"
#include "server.h"

int addProject(char *name, t_project *project)
{
	char query[100];
	MYSQL *con = mysql_init(NULL);

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query, "INSERT INTO `projects` VALUES(NULL, '%s', 'c');", name);
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
	MYSQL_FIELD *line = mysql_fetch_field(result);
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
	if(mysql_query(con, query)){
		mysql_close(con);
		return(1);
	}
	MYSQL_RES *result = mysql_store_result(con);
	if	(result == NULL ) {
		return(-1);
	}
	mysql_close(con);
	return(0);
}

int editProject (int id, char *name, t_project *project)
{
	MYSQL *con = mysql_init(NULL);
	char query[100];
	
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
	MYSQL_ROW row;
	MYSQL_FIELD *line = mysql_fetch_field(result);
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
	char query[100];

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
	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	char *tmp;
	res->message = calloc(9, sizeof(char));
	sprintf(res->message, "\"data\":[");
	for (int i = 0;(row = mysql_fetch_row(result)); i++)
	{
		tmp = calloc(strlen(row[0]) + strlen(row[1])+ strlen(row[2]) + strlen(res->message) + 32, sizeof(char));
		if(i == 0)
			sprintf(tmp,"%s{\"id\":\"%s\",\"name\":\"%s\",\"lang\":\"%s\"}", res->message,row[0], row[1], row[2]);
		else
			sprintf(tmp,"%s,{\"id\":\"%s\",\"name\":\"%s\",\"lang\":\"%s\"}", res->message,row[0], row[1], row[2]);
		free(res->message);
		res->message = tmp;
	}
	tmp = calloc(strlen(res->message) + 2, sizeof(char));
	sprintf(tmp, "%s]", res->message);
	free(res->message);
	res->message = tmp;
	mysql_free_result(result);
	mysql_close(con);
	return(0);
}