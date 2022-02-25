
#include "server.h"

void usersController(struct mg_http_message *hm, t_res *res)
{
	if(strncmp(hm->method.ptr, "POST", 4) == 0)
	{
		userCreateService(hm, res);
		if(res->status >= 400)
			MG_ERROR((":%s:%s:%d:Error to create user!", hm->method.ptr ,hm->uri.ptr, 1));
		else
			MG_INFO((":%s:%s:%d:User created!", hm->method.ptr ,hm->uri.ptr,2));
	}
	else if(strncmp(hm->method.ptr, "DELETE", 6) == 0)
	{
		usersDeleteServices(hm, res);
		if(res->status >= 400)
			MG_ERROR((":%s:%s:%d:Error to deleted user!.", hm->method.ptr ,hm->uri.ptr,1));
		else
			MG_INFO((":%s:%s:%d:Deleted user!", hm->method.ptr ,hm->uri.ptr,2));
	}
	else
	{
		res->status = 400;
		res->message = calloc(20,sizeof(char));
		sprintf(res->message, "\"Error\": \"Wrong method\"");
		MG_ERROR((":%s:%s:%d:not allowed methor!", hm->method.ptr ,hm->uri.ptr,1));
	}
}