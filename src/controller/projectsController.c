
#include "server.h"

t_res projectsController(struct mg_http_message *hm)
{
	t_res res;

	if(strncmp(hm->method.ptr, "GET", 3) == 0) {
		projectsFindAllServices(hm, &res);
		if(res.status >= 400)
			MG_ERROR((":%s:%s:Is not possibel to list anythig!", "GET", "/project"));
		else
			MG_INFO((":%s:%s:Create Project!", "GET", "/project"));
		return (res);
	}
	else if(strncmp(hm->method.ptr, "POST", 4) == 0) {
		projectsCreateServices(hm, &res);
		if(res.status >= 400)
			MG_ERROR((":%s:%s:The project dosen't created!", "POST", "/project"));
		else
			MG_INFO((":%s:%s:Create Project!", "POST", "/project"));
		return (res);
	}
	else if(strncmp(hm->method.ptr, "PUT", 3) == 0) {
		projectsEditServices(hm, &res);
		if(res.status >= 400)
			MG_ERROR((":%s:%s:The project dosen't edit!", "PUT", "/project"));
		else
			MG_INFO((":%s:%s:Create Project!", "PUT", "/project"));
		return (res);
	}
	else if(strncmp(hm->method.ptr, "DELETE", 6) == 0) {
		projectsDeleteServices(hm, &res);
		if(res.status >= 400)
			MG_ERROR((":%s:%s:The project dosen't delete!", "DELETE", "/project"));
		else
			MG_INFO((":%s:%s:Create Project!", "DELETE", "/project"));
		return (res);
	}
	else {
		res.status = 500;
		strcpy(res.message, "error message send a valid method!");
		MG_ERROR((":%s:%s:Create Project!", "WRONG METHOD" ,"/project"));
		return (res);
	}
}