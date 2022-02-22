
#include "server.h"

void	projectsEditServices(struct mg_http_message *hm, t_res *res){
	const char *name;
	int			id;

	name = parseBodyContet(hm->body.ptr);
	id = parseHeaderForId(hm->head.ptr);
	if (id == -1 || name == NULL)
		return (error("header-content", res, "give me a valid id and a name, please!"));
	res->status = 200;
	sprintf(res->message, "\"message\":\"%s have been edited!\"\n", name);
}