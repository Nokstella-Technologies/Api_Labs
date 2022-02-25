
#include "server.h"
#include <rhonabwy.h>

int	authenticated(char *token)
{
	jwk_t *key = NULL;
	jwt_t *jwt = NULL;
	const char jwk_key_str[] = "{\"kty\":\"oct\",\"k\":\"2960fb18828e621b7d627568f106c3ba\"}";
	if(token == NULL)
		return(-1);
	jwt	= r_jwt_quick_parse(token,R_PARSE_ALL,R_FLAG_IGNORE_SERVER_CERTIFICATE);
	r_jwk_init(&key);
	if (r_jwk_import_from_json_str(key, jwk_key_str)== RHN_OK && r_jwt_verify_signature(jwt, key,R_FLAG_IGNORE_SERVER_CERTIFICATE) == RHN_OK)
		return 0;
	return(-1);
}
