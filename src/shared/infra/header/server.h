
#ifndef SERVER_H
# define SERVER_H

static const char *s_http_addr = "http://0.0.0.0:8000";    // HTTP port
static const char *s_https_addr = "https://0.0.0.0:8001";  // HTTPS port
static const char *s_root_dir = ".";

# include <jansson.h>
# include <rhonabwy.h>
# include "mongoose.h"


// #include "l8w8jwt/encode.h"
// #include "l8w8jwt/decode.h"
// #include "../../../../libs/libjwt/include/jwt.h"
// #include <curl/curl.h>
// #include <mongoc/mongoc.h>

typedef struct s_auth
{
	jws_t	*jws;
	jwk_t	*jwk_key_symmetric;
	char	*token;
}			t_auth;

typedef struct s_res
{
	int		status;
	char	message;
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
void	timerLogs(void *buffer) ;
void	generateLogs(const void *buf, size_t len, void *userdata);
// lib function
char	*ft_strdup(const char *str);
char	**ft_split(char const *s, char c);
void	error(char *type ,t_res *res ,char *message);
const char	*parseBodyContet(const char *buff,const char *camp);
int		parseHeaderForId(const char *buff);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif