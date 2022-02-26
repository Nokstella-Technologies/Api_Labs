#include "project.h"

void format_search(MYSQL_RES *result, t_res *res){
	MYSQL_ROW row;
	char *tmp;

	res->message = calloc(9, sizeof(char));
	sprintf(res->message, "\"data\":[");
	for (int i = 0;(row = mysql_fetch_row(result)); i++)
	{
		tmp = calloc(strlen(row[0]) + strlen(row[1])+ strlen(row[2]) +
			strlen(res->message) + 32, sizeof(char));
		if(i == 0)
			sprintf(tmp,"%s{\"id\":\"%s\",\"name\":\"%s\",\"lang\":\"%s\"}",
				res->message,row[0], row[1], row[2]);
		else
			sprintf(tmp,"%s,{\"id\":\"%s\",\"name\":\"%s\",\"lang\":\"%s\"}",
				res->message,row[0], row[1], row[2]);
		free(res->message);
		res->message = tmp;
	}
	tmp = calloc(strlen(res->message) + 2, sizeof(char));
	sprintf(tmp, "%s]", res->message);
	free(res->message);
	res->message = tmp;
}