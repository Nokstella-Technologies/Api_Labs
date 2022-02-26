#ifndef PROJECT_H
#define PROJECT_H

#include "database.h"
#include "server.h"

typedef struct s_project
{
	char *id;
	char *name;
	char *lang;
}			t_project;

int		addProject(char *name,char *lang, t_project *project);
int		delProject (int id);
int		editProject (int id, char *name, t_project *project);
int		searchProject (t_res *res);
void	format_search(MYSQL_RES *result, t_res *res);

#endif