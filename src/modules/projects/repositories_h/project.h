
#ifndef PROJECT_H
#define PROJECT_H

#include "database.h"

typedef struct s_project
{
	char *id;
	char *name;
	char *c;
}			t_project;


int addProject(char *name, t_project *project);
int delProject (int id);
int editProject (int id, char *name);
int searchProject (int *id, char *name);

#endif