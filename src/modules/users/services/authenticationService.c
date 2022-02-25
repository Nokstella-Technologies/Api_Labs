
#include "server.h"
#include "users.h"


void	authenticationService(struct mg_http_message *hm, t_res *res)
{
	const char	*name;
	const char	*password;
	char		*token;
	t_users		user;

	user.id = NULL;
	name = parseBodyContet(hm->body.ptr, "name");
	password = parseBodyContet(hm->body.ptr, "password");
	if (name == NULL || password == NULL)
		return (error("body-contet", res, "give me a name and a password, please!",405));
	else if (strlen(password) < 6)
		return (error("body-contet", res, "give more than 6 digits for the password, please!",405));
	if (findUser((char *)name, (char *)password, &user) < 0)
		return (error("body-content", res, "Password or User Wrong!",405));
	if (compareHash((unsigned char *)password, user.password) < 0)
		return (error("body-content", res, "Password or User Wrong!",405));
	if((token = createJWT()) == NULL)
		return (error("internal", res, "Impossible to create JWT!",500));
	res->status = 200;
	res->message = calloc(strlen(name) + strlen(user.id) + strlen(token) + 40, sizeof(char));
	sprintf(res->message," \"id\":\"%s\", \"name\":\"%s\", \"token\":\"%s\"", user.id, name, token);
	r_free(token);
	free(user.id);
	free(user.name);
	free(user.password);
}