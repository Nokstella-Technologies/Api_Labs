#include "server.h"

void projectsController(struct mg_http_message *hm, t_res *res)
{
	if(strncmp(hm->method.ptr, "GET", 3) == 0) {
		projectsFindAllServices(hm, res);
		if(res->status >= 400)
			MG_ERROR((":%s:%s:%d:Unable to complete your request.", hm->method.ptr ,hm->uri.ptr ,1));
		else
			MG_INFO((":%s:%s:%d:Create Project!", hm->method.ptr ,hm->uri.ptr ,2));
	}
	else if(strncmp(hm->method.ptr, "POST", 4) == 0) {
		if(authenticated(parseToken(hm->head.ptr)) == 0)
			projectsCreateServices(hm, res);
		else
			error("Auth", res, "Invalid Token!",403);
		if(res->status >= 400)
			MG_ERROR((":%s:%s:%d:The Project was not created.", hm->method.ptr ,hm->uri.ptr ,1));
		else
			MG_INFO((":%s:%s:%d:Create Project!", hm->method.ptr ,hm->uri.ptr ,2));
	}
	else if(strncmp(hm->method.ptr, "PUT", 3) == 0) {
		if(authenticated(parseToken(hm->head.ptr)) == 0)
			projectsEditServices(hm, res);
		else
			error("Auth", res, "Invalid Token!",403);
		if(res->status >= 400)
			MG_ERROR((":%s:%s:%d:The Project was not edited.", hm->method.ptr ,hm->uri.ptr,1));
		else
			MG_INFO((":%s:%s:%d:Create Project!", hm->method.ptr ,hm->uri.ptr,2));
	}
	else if(strncmp(hm->method.ptr, "DELETE", 6) == 0) {
		if(authenticated(parseToken(hm->head.ptr)) == 0)
			projectsDeleteServices(hm, res);
		else
			error("Auth", res, "Invalid Token!", 403);
		if(res->status >= 400)
			MG_ERROR((":%s:%s:%d:The Project was not deleted.", hm->method.ptr ,hm->uri.ptr,1));
		else
			MG_INFO((":%s:%s:%d:Create Project!", hm->method.ptr ,hm->uri.ptr,2));
	}
	else {
		res->status = 405;
		res->message = calloc(30,sizeof(char));
		sprintf(res->message, "\"Error\": \"Wrong method\"");
		MG_ERROR((":%s:%s:%d:not allowed methor!",hm->method.ptr ,hm->uri.ptr ,1));
	}
}