
#ifndef SERVER_H
# define SERVER_H

# include "mongoose.h"
# include "utils.h"

typedef struct s_res
{
	int		status;
	char	*message;
}		t_res;

// Routes
void	routes(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

// Controllers
void	usersController(struct mg_http_message *hm, t_res *res);
void	projectsController(struct mg_http_message *hm, t_res *res);
void	authenticationController(struct mg_http_message *hm, t_res *res);

// Services
void	projectsDeleteServices(struct mg_http_message *hm, t_res *res);
void	projectsCreateServices(struct mg_http_message *hm, t_res *res);
void	projectsEditServices(struct mg_http_message *hm, t_res *res);
void	projectsFindAllServices(struct mg_http_message *hm, t_res *res);
void	authenticationService(struct mg_http_message *hm, t_res *res);
void	userCreateService(struct mg_http_message *hm, t_res *res);
void	usersDeleteServices(struct mg_http_message *hm, t_res *res);
// logs
void	generateLogs(const void *buf, size_t len, void *userdata);
// lib function

void			error(char *type ,t_res *res ,char *message,int status);
void	authenticated(void (service) (struct mg_http_message *, t_res *),
	struct mg_http_message *hm, t_res *res);
void			send_log(struct mg_http_message *hm, t_res *res,
	const char *messageOk, const char *messageError);

#endif