
#include "utils.h"

char *createJWT(void)
{
	jwt_t * jwt = NULL;
	jwk_t * jwk_key = NULL;
	const char payload[] = "{\"exp\":172800}",
			jwk_key_str[] = "{\"kty\":\"oct\",\"k\":\"2960fb18828e621b7d627568f106c3ba\"}";
	char * token = NULL;
	
	if (r_jwk_init(&jwk_key) == RHN_OK && 
		r_jwt_init(&jwt) == RHN_OK &&
		r_jwk_import_from_json_str(jwk_key, jwk_key_str) == RHN_OK && 
		r_jwt_set_sign_alg(jwt, R_JWA_ALG_HS256) == RHN_OK &&
		r_jwt_set_full_claims_json_str(jwt, payload) == RHN_OK) {
		token = r_jwt_serialize_signed(jwt, jwk_key, 0);
	}
	r_jwt_free(jwt);
	r_jwk_free(jwk_key);
	return (token);
}