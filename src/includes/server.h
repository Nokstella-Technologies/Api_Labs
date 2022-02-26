#ifndef SERVER_H
# define SERVER_H

# define S200 "Ok"
# define S400 "Bad Request"
# define S404 "Not Found"
# define S405 "Method Not Allowed"
# define S406 "Not Acceptable"
# define S407 "Proxy Authentication Required"
# define S500 "Internal Server"
# define RESP "\"Message\":\"Welcome to the 42 portfolio API\",\"routes\":[{\"uri:\":\"/projects\", \"method\":[\"GET\",\"POST\",\"DELETE\",\"PUT\"]},{\"uri:\":\"/authentication\",\"method\":[\"POST\"]},{\"uri:\":\"/users\",\"method\":[\"POST\",\"DELETE\"]}]\n"

/**
 * @brief this a library for http https calls in C.
 */
# include "mongoose.h"
# include <time.h>
# include "utils.h"

typedef struct s_res
{
	int		status;
	char	*message;
}		t_res;

/**
 * @brief Each connection has an event handler function associated with it,  
 * this is a event handler.
 * 
 * @param c A connection that received an event.
 * @param ev An event number, defined in mongoose.h. For example, when data 
 * arrives on an inbound connection, ev would be MG_EV_READ.
 * @param ev_data Points to the event-specific data, and it has a different 
 * meaning for different events. For example, for an MG_EV_READ event, ev_data 
 * is an int * pointing to the number of bytes received from a remote peer and 
 * saved into the c->recv IO buffer. The exact meaning of ev_data is described 
 * for each event. Protocol-specific events usually have ev_data pointing to 
 * structures that hold protocol-specific information.
 * @param fn_data A user-defined pointer for the connection, which is a 
 * placeholder for application-specific data. This fn_data pointer is set 
 * during the *_listen() or *_connect() call, and it is stored in the 
 * c->fn_data. Listening connections copy the value of c->fn_data to the newly 
 * accepted connection, so all accepted connections initially share the same 
 * fn_data pointer. It is fine to update/replace that pointer for any 
 * connection at any time by setting c->fn_data = new_value;
 */
void	routes(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

/**
 * @brief Control the method and functionability to be aplied accordandly to 
 * the requisition.
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc. 
 * @param res struct that will save response (status, message)
 */
void	usersController(struct mg_http_message *hm, t_res *res);

/**
 * @brief Control the method and functionability to be aplied accordandly to 
 * the requisition.
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	projectsController(struct mg_http_message *hm, t_res *res);

/**
 * @brief Control the method and functionability to be aplied accordandly to 
 * the requisition.
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	authenticationController(struct mg_http_message *hm, t_res *res);

/**
 * @brief This function verify everthing that is needed to remove the project from db an then delete
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	projectsDeleteServices(struct mg_http_message *hm, t_res *res);

/**
 * @brief This function verify everthing that is needed to create the project in db
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	projectsCreateServices(struct mg_http_message *hm, t_res *res);

/**
 * @brief This function verify everthing that is needed to edit the project in db
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	projectsEditServices(struct mg_http_message *hm, t_res *res);

/**
 * @brief This function verify everthing that is needed to edit the project in db
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	projectsFindAllServices(struct mg_http_message *hm, t_res *res);

/**
 * @brief This function verify everthing that is needed to authenticate the user in db
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	authenticationService(struct mg_http_message *hm, t_res *res);

/**
 * @brief This function verify everthing that is needed to create user in db
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	userCreateService(struct mg_http_message *hm, t_res *res);

/**
 * @brief This function verify everthing that is needed to delete user in db
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	usersDeleteServices(struct mg_http_message *hm, t_res *res);

/**
 * @brief  This is a event handler function that is called everytime that we call a log function from the mongoose library.
 * 
 * @param buf This is a message that will be passed and will be printed in the logs.txt.
 * @param len It's the number of character of a string. 
 * @param userdata 
 */
void	generateLogs(const void *buf, size_t len, void *userdata);

/**
 * @brief 
 * 
 * @param type 
 * @param res 
 * @param message string that holds the error message. 
 * @param status int that holds the status of the error. 
 */
void	error(char *type ,t_res *res ,char *message,int status);

/**
 * @brief function that emulates a middleware in more modern languages, in this case is used to authenticate the user and give a JWT Token.
 * 
 * @param service the function that will be executed after the JWT token verification. 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 */
void	authenticated(void (service) (struct mg_http_message *, t_res *) ,
	struct mg_http_message *hm, t_res *res);

/**
 * @brief 
 * 
 * @param hm struct that holds all info from the request like: URI, METHOD, BODY, HEADER, etc.
 * @param res struct that will save response (status, message).
 * @param messageOk string that holds an ok message
 * @param messageError string that holds an error message
 */
void	send_log(struct mg_http_message *hm, t_res *res,
	const char *messageOk, const char *messageError);

#endif