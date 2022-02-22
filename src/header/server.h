
#ifndef SERVER_H
# define SERVER_H

static const char *s_http_addr = "http://0.0.0.0:8000";    // HTTP port
static const char *s_https_addr = "https://0.0.0.0:8001";  // HTTPS port
static const char *s_root_dir = ".";

#include "../libs/mongoose/mongoose.h"
// #include <curl/curl.h>
// #include <mongoc/mongoc.h>

typedef struct s_res
{
    int     status;
    char    *message;
}           t_res;

// Routes
void routes(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

// Controllers
t_res usersController(struct mg_http_message *hm);
t_res projectsController(struct mg_http_message *hm);

// Services
void projectsDeleteServices(struct mg_http_message *hm, t_res *res);
void projectsCreateServices(struct mg_http_message *hm, t_res *res);
void projectsEditServices(struct mg_http_message *hm, t_res *res);
void projectsFindAllServices(struct mg_http_message *hm, t_res *res);
#endif