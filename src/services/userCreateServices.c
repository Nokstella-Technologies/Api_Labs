
#include "server.h"

void	userCreateService(struct mg_http_message *hm, t_res *res)
{
	const char *name;
	const char *password;
	name = parseBodyContet(hm->body.ptr, "name");
	password = parseBodyContet(hm->body.ptr, "password");
	if (name == NULL || password == NULL)
		return (error("body-contet", res, "give me a name and a password, please!"));
	else if (strlen(password) < 6)
		return (error("body-contet", res, "give more than 6 digits for the password, please!"));

	res->status = 200;
	sprintf(res->message," \"id\":\"%s\", \"name\":\"%s\", \"password:\"", password, name);
}