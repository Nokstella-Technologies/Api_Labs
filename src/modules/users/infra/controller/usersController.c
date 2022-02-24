
#include "server.h"

void usersController(struct mg_http_message *hm, t_res *res)
{
	t_res res;

	if(strncmp(hm->method.ptr, "POST", 4) == 0)
	{
		userCreateService(hm, &res);
		if(res->status >= 400)
			MG_ERROR((":%s:%s:Error to create user!", "POST", "/users"));
		else
			MG_INFO((":%s:%s:User created!", "POST", "/users"));
		return (res);
	}
	else if(strncmp(hm->method.ptr, "DELETE", 6) == 0)
	{
		usersDeleteServices(hm, &res);
		if(res->status >= 400)
			MG_ERROR((":%s:%s:Error to deleted user!.", "DELETE", "/users"));
		else
			MG_INFO((":%s:%s:Deleted user!", "DELETE", "/users"));
		return (res);
	}
	else
	{
		res->status = 400;
		res->message = calloc(20,sizeof(char));
		sprintf(res->message, "\"Error\": \"Wrong method\"");
		MG_ERROR((":%s:%s:not allowed methor!", "WRONG METHOD" ,"/users"));
		return (res);
	}
}