
#include "server.h"

void	routes(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		if (mg_http_match_uri(hm, "/project")) {
			t_res res = projectsController(hm);
			mg_http_reply(c, res.status, "", "{%s}\n", res.message);
		} else if (mg_http_match_uri(hm, "/users")) {
			t_res res = usersController(hm);
			mg_http_reply(c, res.status, "", "{%s}\n", res.message);
		} else if (mg_http_match_uri(hm, "/authentication")){
			t_res res = authenticationController(hm);
			mg_http_reply(c, 200, "", "{%s}\n", hm->head.ptr);
		}else if (mg_http_match_uri(hm, "/teste")) {
			mg_http_reply(c, 200, "", "{%s}\n", hm->head.ptr);
		}else {
			struct mg_http_serve_opts opts = {.root_dir = s_root_dir};
			mg_http_serve_dir(c, ev_data, &opts);
		}
	}
	(void) fn_data;
}