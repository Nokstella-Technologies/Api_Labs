
#ifndef SERVER_H
# define SERVER_H

static const char *s_http_addr = "http://0.0.0.0:8000";    // HTTP port
static const char *s_https_addr = "https://0.0.0.0:8001";  // HTTPS port
static const char *s_root_dir = ".";

#include "../libs/mongoose/mongoose.h"
#include <json-c/json.h>

// #include <curl/curl.h>
// #include <mongoc/mongoc.h>

typedef struct s_res
{
	int		status;
	char	message[128];
}		t_res;

// Routes
void	routes(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

// Controllers
t_res	usersController(struct mg_http_message *hm);
t_res	projectsController(struct mg_http_message *hm);

// Services
void	projectsDeleteServices(struct mg_http_message *hm, t_res *res);
void	projectsCreateServices(struct mg_http_message *hm, t_res *res);
void	projectsEditServices(struct mg_http_message *hm, t_res *res);
void	projectsFindAllServices(struct mg_http_message *hm, t_res *res);

// logs
void	timerLogs(void *buffer) ;
void	generateLogs(const void *buf, size_t len, void *userdata);
// lib function
char	*ft_strdup(const char *str);
void	error(char *type ,t_res *res ,char *message);
const char	*parseBodyContet(const char *buff, char *camp);
int		parseHeaderForId(const char *buff);
#endif