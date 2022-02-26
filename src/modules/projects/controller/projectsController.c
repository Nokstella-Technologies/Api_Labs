#include "server.h"

void projectsController(struct mg_http_message *hm, t_res *res)
{
	if(strncmp(hm->method.ptr, "GET", 3) == 0) {
		projectsFindAllServices(hm, res);
		send_log(hm, res, "Unable to complete your request.", 
			"Create Project!");
	}
	else if(strncmp(hm->method.ptr, "POST", 4) == 0) {
		authenticated(projectsCreateServices, hm, res);
		send_log(hm ,res , "Create Project!" ,"The Project was not created.");
	}
	else if(strncmp(hm->method.ptr, "PUT", 3) == 0) {
		authenticated(projectsEditServices, hm, res);
		send_log(hm, res, "Edit Project!","The Project was not edited.");
	}
	else if(strncmp(hm->method.ptr, "DELETE", 6) == 0) {
		authenticated(projectsDeleteServices, hm, res);
		send_log(hm, res, "Deleted Project!", "The Project was not deleted.");
	}
	else {
		res->status = 405;
		res->message = calloc(50,sizeof(char));
		sprintf(res->message, "\"Error\": \"Wrong method\"");
		send_log(hm, res, "", "not allowed methor!");
	}
}