
#include "server.h"

void	routes(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		t_res res;

		if (mg_http_match_uri(hm, "/project")) {
			projectsController(hm, &res);
			mg_http_reply(c, res.status, "Content-Type: application/json\n""charset: utf-8\n""Connection: keep-alive\n", "{%s}\n", res.message);
			free(res.message);
		} else if (mg_http_match_uri(hm, "/users")) {
			usersController(hm, &res);
			mg_http_reply(c, res.status, "Content-Type: application/json\n""charset: utf-8\n""Connection: keep-alive\n", "{%s}\n", res.message);
			free(res.message);
		} else if (mg_http_match_uri(hm, "/authentication")){
			authenticationController(hm, &res);
			mg_http_reply(c, res.status, "Content-Type: application/json\n""charset: utf-8\n""Connection: keep-alive\n", "{%s}\n", res.message);
			free(res.message);
		// }else if (mg_http_match_uri(hm, "/teste")) {
		// 	// Content-Type: application/json; charset=utf-8; Connection: keep-alive;
		// 	mg_http_reply(c, 200, "Content-Type: application/json\n""charset: utf-8\n""Connection: keep-alive\n", "{%s}\n", hm->head.ptr);
		// }
		}else {
			res.message = calloc(200, sizeof(char));
			sprintf(res.message,":%s:%s:%d:NOT FOUND", strtok((char *)hm->method.ptr, " ") ,strtok((char *)hm->uri.ptr, " "), 1);
			MG_ERROR((res.message));
			mg_http_reply(c,404,"Content-Type: application/json\n""charset: utf-8\n""Connection: keep-alive\n","{\"message\":\"%s\"}","NOT FOUND");
			free(res.message);
		}
	}
	(void) fn_data;
}
