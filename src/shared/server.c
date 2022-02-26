
#include "server.h"

int main(void)
{
	struct mg_mgr mgr;

	mg_mgr_init(&mgr);
	mg_log_set("2");
	mg_log_set_callback(&generateLogs, NULL);
	mg_http_listen(&mgr, "http://0.0.0.0:8000", &routes, NULL);
	mg_http_listen(&mgr, "http://0.0.0.0:8001", &routes, (void *) 1);
	for (;;) mg_mgr_poll(&mgr, 1000);
	mg_mgr_free(&mgr);
	return 0;
}