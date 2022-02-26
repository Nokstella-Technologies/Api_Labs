
#include "utils.h"

char	*parseBodyContet(const char *buff,const char *camp)
{
	json_t *parsed_json;
	json_t *name;
	json_error_t error;
	parsed_json = json_loads(buff, 0, &error);
	name = json_object_get(parsed_json, camp);
	return((char *)json_string_value(name));
}

int		parseHeaderForId(const char *buff, const char *search){
	const char *tmp;
	
	tmp = strstr(buff, search);
	if(tmp == NULL)
		return(-1);
	return(atoi(tmp + strlen(search)));
}

char	*parseToken(const char *buff)
{
	char *token_position;

	token_position = strstr(buff, "Bearer");
	if(token_position == NULL)
		return(NULL);
	return(strtok(token_position + 7, " \r"));
}
