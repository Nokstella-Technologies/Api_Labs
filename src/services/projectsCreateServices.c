
#include "server.h"

void projectsCreateServices(struct mg_http_message *hm, t_res *res){
	res->status = 200;
	strcpy(res->message, "Project created");
}