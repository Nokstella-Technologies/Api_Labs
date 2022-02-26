
#include "server.h"

static int s_signo;

static void signal_handler(int signo) {
  s_signo = signo;
}

int main(void)
{
	struct mg_mgr mgr;

	mg_mgr_init(&mgr);
	mg_log_set("2");
	mg_log_set_callback(&generateLogs, NULL);
	mg_http_listen(&mgr, "http://0.0.0.0:8000", &routes, NULL);
	mg_http_listen(&mgr, "http://0.0.0.0:8001", &routes, (void *) 1);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	for (;s_signo == 0;) mg_mgr_poll(&mgr, 1000);
	mg_mgr_free(&mgr);
	printf("Stop Server!");
	return 0;
}