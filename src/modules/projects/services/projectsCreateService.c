
#include "server.h"
#include "project.h"

void	projectsCreateServices(struct mg_http_message *hm, t_res *res)
{
	const char *name;
	t_project project;

	name = parseBodyContet(hm->body.ptr, "name");
	if (name == NULL)
		return (error("body-contet", res, "give me a name, please!"));
	if (addProject((char *)name, &project) < 0)
		return (error("database", res, "not possible to save in database!"));
	res->status = 200;
	res->message = calloc(strlen(project.id) + strlen(project.name) + strlen( project.c) + 20 , sizeof(char));
	sprintf(res->message, "\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"", "id", project.id,"name",project.name,"c", project.c);
	free(project.name);
	free(project.c);
	free(project.id);
}