
#include "server.h"



void projectsDeleteServices(struct mg_http_message *hm, t_res *res){
	int id;

	id = parseHeaderForId(hm->head.ptr);
	if(id == -1)
		return(error("header-content", res, "give me a valid id, please!"));
	res->status = 200;
	sprintf(res->message, "\"message\":\"%d have been deleted\"\n", id);

}