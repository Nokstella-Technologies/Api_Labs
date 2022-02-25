
#include "server.h"
#include "users.h"


void	userCreateService(struct mg_http_message *hm, t_res *res)
{
	const char *name;
	const char *password;
	unsigned char *encrypted_pass;
	t_users user;

	name = parseBodyContet(hm->body.ptr, "name");
	password = parseBodyContet(hm->body.ptr, "password");
	if (name == NULL || password == NULL)
		return (error("body-contet", res, "give me a name and a password, please!",405));
	else if (strlen(password) < 6)
		return (error("body-contet", res, "give more than 6 digits for the password, please!",405));
	else if((encrypted_pass = encrypt((unsigned char *)password, strlen(password))) == NULL)
		return (error("database", res, "error to encrypt!",500));
	else if(addUsers((char *)name, encrypted_pass, &user) < 0)
		return (error("database", res, "is not possible to create the user in database!",400));
	res->status = 200;
	res->message = (char *)calloc(strlen(user.id) + strlen(user.name) + 30 , sizeof(char));
	sprintf(res->message, "\"%s\":\"%s\",\"%s\":\"%s\"", "id", user.id,"name",user.name);
	free(user.id);
	free(user.name);
	free(encrypted_pass);
}