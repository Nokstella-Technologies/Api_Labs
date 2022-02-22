
#include "server.h"

t_res projectsController(struct mg_http_message *hm)
{
    t_res res;

    if(strncmp(hm->method.ptr, "GET", 3) == 0) {
        projectsFindAllServices(hm, &res);
        return (res);
    }
    else if(strncmp(hm->method.ptr, "POST", 4) == 0) {
        projectsCreateServices(hm, &res);
        return (res);
    }
    else if(strncmp(hm->method.ptr, "PUT", 3) == 0) {
        projectsEditServices(hm, &res);
        return (res);
    }
    else if(strncmp(hm->method.ptr, "DELETE", 6) == 0) {
        projectsDeleteServices(hm, &res);
        return (res);
    }
    else {
        res.status = 500;
        res.message = strdup("error message send a valid method!");
        return (res);
    }
}