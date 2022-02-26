
#include "server.h"
#include "users.h"

void usersDeleteServices(struct mg_http_message *hm, t_res *res){
	int id;

	id = parseHeaderForId(hm->head.ptr, "/users/");
	if(id == -1)
		return(error("header-content", res, "give me a valid id, please!",406));
	if(delUsers(id) < 0)
		return(error("database", res, "is not possible to delete user from database!", 406));
	res->status = 200;
	res->message = calloc(50, sizeof(char));
	sprintf(res->message, "\"message\":\" user %d have been deleted\"\n", id);
}
