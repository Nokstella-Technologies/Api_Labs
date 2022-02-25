
#include "server.h"

void error(char *type ,t_res *res ,char *message,int status)
{
	res->status = status;
	res->message = calloc(strlen(type) + strlen(message) + 30, sizeof(char));
	sprintf(res->message,"\"error\":\"%s\",\"message\":\"%s\"", type, message);
}