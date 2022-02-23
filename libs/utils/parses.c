
#include "server.h"

const char	*parseBodyContet(const char *buff, char *camp)
{
	struct json_object *parsed_json;
	struct json_object *name;

	parsed_json = json_tokener_parse(buff);
	json_object_object_get_ex(parsed_json, camp, &name);
	return(json_object_get_string(name));
}

int		parseHeaderForId(const char *buff){
	if(strstr(buff, "id=") == NULL)
		return(-1);
	return(atoi(strstr(buff, "id=") + 3));
}