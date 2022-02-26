
#include "server.h"
#include "users.h"

static void formatResponseAuth(t_res *res, t_users *user, char *token)
{
	res->status = 200;
	res->message = calloc(strlen(user->name) + strlen(user->id) + strlen(token)
		+ 40, sizeof(char));
	sprintf(res->message," \"id\":\"%s\", \"name\":\"%s\", \"token\":\"%s\"",
		user->id, user->name, token);
	r_free(token);
	free(user->id);
	free(user->name);
	free(user->password);
}

void	authenticationService(struct mg_http_message *hm, t_res *res)
{
	char		*token;
	char		*password;
	t_users		user;

	user.id = NULL;
	user.name = parseBodyContet(hm->body.ptr, "name");
	password = parseBodyContet(hm->body.ptr, "password");
	if (user.name  == NULL || password== NULL)
		return (error("body-contet", res, "give me a name and a password, please!", 406));
	else if (strlen(password) < 6)
		return (error("body-contet", res, "give more than 6 digits for the password, please!",406));
	if (findUser(user.name, &user) < 0)
		return (error("body-content", res, "Password or User Wrong!", 406));
	if (compareHash((unsigned char *)password, (unsigned char *)user.password) < 0)
		return (error("body-content", res, "Password or User Wrong!", 406));
	if((token = createJWT()) == NULL)
		return (error("internal", res, "Impossible to create JWT!", 407));
	formatResponseAuth(res, &user, token);
}