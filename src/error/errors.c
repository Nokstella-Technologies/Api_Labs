
#include "server.h"

void error(char *type ,t_res *res ,char *message)
{
	res->status = 404;
	sprintf(res->message,"\"error\":\"%s\",\"message\":\"%s\"", type, message);
}