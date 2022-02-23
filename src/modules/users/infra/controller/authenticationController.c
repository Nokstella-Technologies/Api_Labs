

#include "server.h"

t_res authenticationController(struct mg_http_message *hm)
{
	t_res res;

	if(strncmp(hm->method.ptr, "POST", 4) == 0) {
		authenticationService(hm, &res);
		if(res.status >= 400)
			MG_ERROR((":%s:%s:Wrong Login.", "POST", "/authentication"));
		else
			MG_INFO((":%s:%s:Login In!", "POST", "/authentication"));
		return (res);
	}
	else{
		res.status = 400;
		strcpy(res.message, "\"Error\": \"Wrong method\"");
		MG_ERROR((":%s:%s:not allowed methor!", "WRONG METHOD" ,"/authentication"));
		return (res);
	}
}