
#include "server.h"

void	projectsCreateServices(struct mg_http_message *hm, t_res *res)
{
	const char *name;

	name = parseBodyContet(hm->body.ptr, "name");
	if (name == NULL)
		return (error("body-contet", res, "give me a name, please!"));
	res->status = 200;
	sprintf(res->message, "\"message\":\"%s have been created\"\n", name);
}