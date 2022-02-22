
#include "server.h"


static void log_message(const char *filename, const char *message) {
	FILE *fp = fopen(filename, "a");

	if (fp != NULL) {
		fprintf(fp, "%s", message);
		fclose(fp);
	}
}

static void broadcast_message(struct mg_mgr *mgr, const char *message) {
	struct mg_connection *c;

	for (c = mgr->conns; c != NULL; c = c->next) {
		if (c->label[0] == 'L') mg_http_printf_chunk(c, "%s", message);
	}
}

void	timerLogs(void *arg) {
	char buf[64];

	snprintf(buf, sizeof(buf), "Time is: %lu\n", (unsigned long) time(NULL));
	log_message("./src/logs/logs.txt", buf);
	broadcast_message(arg, buf);
}

void generateLogs(const void *buf, size_t len, void *userdata)
{
	(void) userdata;
	log_message("./src/logs/logs.txt", buf);
}