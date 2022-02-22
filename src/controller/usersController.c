

#include "server.h"

t_res usersController(struct mg_http_message *hm)
{
    t_res res;

    if(strncmp(hm->method.ptr, "GET", 3) == 0)
    {

    }
    else if(strncmp(hm->method.ptr, "POST", 4) == 0)
    {

    }
    else if(strncmp(hm->method.ptr, "PUT", 3) == 0)
    {

    }
    else if(strncmp(hm->method.ptr, "DELETE", 6) == 0)
    {

    }
    else
    {
        
    }
}