

#include "server.h"

void authenticationController(struct mg_http_message *hm, t_res *res)
{

	if(strncmp(hm->method.ptr, "POST", 4) == 0) {
		authenticationService(hm, res);
		send_log(hm,res,"Login In!","Wrong Login.");
	}
	else{
		res->status = 405;
		res->message = calloc(20,sizeof(char));
		sprintf(res->message, "\"Error\": \"Wrong method\"");
		send_log(hm, res, "", "not allowed methor!");
	}
}