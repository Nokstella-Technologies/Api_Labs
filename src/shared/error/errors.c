
#include "server.h"

void error(char *type ,t_res *res ,char *message)
{
	res->status = 404;
	res->message = calloc(strlen(res) + strlen(message) + 30, sizeof(char));
	sprintf(res->message,"\"error\":\"%s\",\"message\":\"%s\"", type, message);
}