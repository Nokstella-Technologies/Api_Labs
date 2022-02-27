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

/**
 * @brief This function emulates repository functions in modern languages, make the connection with database and add a new project. 
 * 
 * @param name name of the projetct to the db
 * @param lang language to be added to the project in the db
 * @param project where the response of the db will be saved.
 * @return int 0 for OK and -1 for error.
 */
int		addProject(char *name,char *lang, t_project *project);

/**
 * @brief This function emulates repository functions in modern languages, make the connection with database and add a del a project.
 * 
 * @param id project id to be deleted in the db.
 * @return int 0 for OK and -1 for error.
 */
int		delProject (int id);

/**
 * @brief This function emulates repository functions in modern languages, make the connection with database and add a edit a project.
 * 
 * @param id project id to be edited in the db.
 * @param name project name to be edited in the db.
 * @param lang project lang to be edited in the db.
 * @param project where the response of the db will be saved.
 * @return int 0 for OK and -1 for error.
 */
int editProject (int id, char *name ,char *lang, t_project *project);

/**
 * @brief This function emulates repository functions in modern languages, make the connection with database and add a search a project.
 * 
 * @param res struct that stores all the projects. 
 * @return int 0 for OK and -1 for error.
 */
int		searchProject (t_res *res);

/**
 * @brief 
 * 
 * @param result 
 * @param res 
 */
void	format_search(MYSQL_RES *result, t_res *res);

#endif