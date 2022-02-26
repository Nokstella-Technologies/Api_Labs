
#include "server.h"


static void response(struct mg_connection *c,t_res *res)
{
		mg_http_reply(c, res->status, 
			"Content-Type: application/json\n"
			"charset: utf-8\n""Connection: keep-alive\n",
			"{%s}\n", res->message);
		free(res->message);
}

void	routes(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		t_res res;
		if(mg_http_match_uri(hm, "/")){
			mg_http_reply(c, 200, 
			"Content-Type: application/json\n"
			"charset: utf-8\n""Connection: keep-alive\n",
			"{\"Message\":\"Welcome to the 42 portfolio API\",\"routes\":[{\"uri:\":\"/projects\", \"method\":[\"GET\",\"POST\",\"DELETE\",\"PUT\"]},{\"uri:\":\"/authentication\",\"method\":[\"POST\"]},{\"uri:\":\"/users\",\"method\":[\"POST\",\"DELETE\"]}]}\n");
		}
		if (mg_http_match_uri(hm, "/project/*") ||
			mg_http_match_uri(hm, "/project")) {
			projectsController(hm, &res);
			response(c, &res);
		} 
		else if (mg_http_match_uri(hm, "/users/*") ||
				mg_http_match_uri(hm, "/users")) {
			usersController(hm, &res);
			response(c, &res);
		} 
		else if (mg_http_match_uri(hm, "/authentication") ||
				mg_http_match_uri(hm, "/authentication/")){
			authenticationController(hm, &res);
			response(c, &res);
		}
		else{
			MG_ERROR((":%s:/%s:%d:NOT FOUND",
				strtok((char *)hm->method.ptr, " ") ,strtok((char *)hm->uri.ptr, " /"), 1));
			error("error", &res, "NOT FOUND!", 404);
			response(c, &res);
		}
	}
	(void) fn_data;
}
