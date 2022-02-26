
#include "server.h"
#include "project.h"

void projectsDeleteServices(struct mg_http_message *hm, t_res *res){
	int id;

	id = parseHeaderForId(hm->uri.ptr, "/project/");
	if (id == -1)
		return(error("header-content", res, "give me a valid id, please!", 406));
	if (delProject(id) < 0)
		return (error("database", res, "not possible to delete from database!", 500));
	res->status = 200;
	res->message = calloc(45, sizeof(char));
	sprintf(res->message, "\"message\":\"project id %d have been deleted\"\n", id);

}