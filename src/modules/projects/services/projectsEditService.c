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

void	projectsEditServices(struct mg_http_message *hm, t_res *res){
	const char *name;
	const char *lang;
	int			id;
	t_project project;

	name = parseBodyContet(hm->body.ptr, "name");
	lang = parseBodyContet(hm->body.ptr, "lang");
	id = parseHeaderForId(hm->head.ptr, "/project/");
	if (id == -1 || name == NULL)
		return (error("header-content", res, "give me a valid id and a name, please!", 406));
	if(editProject(id, (char *)name,(char *) lang, &project))
		return (error("database", res, "not possible to edit data on database!", 500));
	reponse_format_project(&project, res);
}