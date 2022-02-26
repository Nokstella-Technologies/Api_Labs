
#include "server.h"

void usersController(struct mg_http_message *hm, t_res *res)
{
	if(strncmp(hm->method.ptr, "POST", 4) == 0) {
		userCreateService(hm, res);
		send_log(hm, res, "User created!", "Error to create user!");
	}
	else if(strncmp(hm->method.ptr, "DELETE", 6) == 0) {
		authenticated(&usersDeleteServices,hm,res);
		send_log(hm, res, "Deleted user!", "Error to deleted user!");
	}
	else {
		res->status = 405;
		res->message = calloc(20,sizeof(char));
		sprintf(res->message, "\"Error\": \"Wrong method\"");
		send_log(hm, res, "", "not allowed methor!");
	}
}