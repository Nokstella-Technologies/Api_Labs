
#include "server.h"

void projectsFindAllServices(struct mg_http_message *hm, t_res *res){
	res->status = 200;
	sprintf(res->message,"\"response\":\"ola\"");
}