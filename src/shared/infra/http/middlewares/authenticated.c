
#include "server.h"


int encodeJWT(void)
{	
	t_auth	*auth;
	auth->jws = NULL;
	auth->jwk_key_symmetric = NULL;
	auth->token = NULL;
	const unsigned char payload[] = "zxgas";
	const char jwk_key_symmetric_str[] = "{\"kty\":\"oct\",\"alg\":\"HS256\",	\"k\":\"c2VjcmV0\",\"kid\":\"1\"}";
	
	// if (r_jwk_init(&auth->jwk_key_symmetric) == RHN_OK && 
	// 	r_jws_init(&authjws) == RHN_OK &&
	// 	r_jwk_import_from_json_str(jwk_key_symmetric, jwk_key_symmetric_str) == 	RHN_OK && 
	// 	r_jws_set_alg(jws, R_JWA_ALG_HS256) == RHN_OK &&
	// 	r_jws_set_payload(jws, payload, sizeof(payload)) == RHN_OK) {
	// 	token = r_jws_serialize(jws, jwk_key_symmetric, 0); // token will store the 	signed token
	// }
 
	// r_free(token);
	// r_jws_free(jws);
	// r_jwk_free(jwk_key_symmetric);

}

int	authenticated(struct mg_http_message *hm, t_res *res)
{
	return 0;
}
