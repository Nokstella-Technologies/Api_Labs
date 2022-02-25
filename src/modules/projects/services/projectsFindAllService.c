
#include "server.h"
#include "project.h"
void projectsFindAllServices(struct mg_http_message *hm, t_res *res){
	if(searchProject(res) < 0)
		return (error("database", res, "not possible to find data on database!", 404));
	res->status = 200;
}