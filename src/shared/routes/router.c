#include "server.h"

static void response(struct mg_connection *c,t_res *res)
{
	char header[200];
	time_t t = time(&t);

	sprintf(header, "HTTP/1.1: %d %s\n""Content-Type: application/json\n"
		"charset: utf-8\n""Connection: keep-alive\n""Data: %s", res->status, res->status == 200 ? S200 : res->status == 400 ? S400 :res->status == 404 ? S404 :res->status == 405 ? S405 :res->status == 406 ? S406 :res->status == 407 ? S407 : S500, ctime(&t));
	mg_http_reply(c, res->status, (const char *)header,
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
		else {
			MG_ERROR((":%s:/%s:%d:NOT FOUND",
				strtok((char *)hm->method.ptr, " ") ,strtok((char *)hm->uri.ptr, " /"), 1));
			error("error", &res, "NOT FOUND!", 404);
			response(c, &res);
		}
	}
	(void) fn_data;
}
