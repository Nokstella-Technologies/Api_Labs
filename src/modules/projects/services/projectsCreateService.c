#include "server.h"
#include "project.h"

static void reponse_format_project(t_project *project, t_res *res)
{
	res->status = 200;
	res->message = (char *)calloc(strlen(project->id) + strlen(project->name) +
		strlen(project->lang) + 30 , sizeof(char));
	sprintf(res->message, "\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"", "id",
		project->id,"name",project->name,"lang", project->lang);
	free(project->name);
	free(project->lang);
	free(project->id);
}

void	projectsCreateServices(struct mg_http_message *hm, t_res *res)
{
	t_project	project;

	project.name = parseBodyContet(hm->body.ptr, "name");
	project.lang = parseBodyContet(hm->body.ptr, "lang");
	if (project.name == NULL || project.lang == NULL)
		return (error("body-contet", res, "give me a name, please!", 406));
	if (addProject((char *)project.name, (char *)project.lang, &project) < 0)
		return (error("database",res,"not possible to save in database!", 406));
	reponse_format_project(&project, res);
}