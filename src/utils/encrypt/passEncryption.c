#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char hex[16] = "0123456789abcdef";

unsigned char	*encrypt(unsigned char *password, int passlen)
{
	unsigned char	md[SHA256_DIGEST_LENGTH];
	SHA256_CTX		context;
	unsigned char	*res = NULL;
	int				a = 0;

	SHA256_Init(&context);
	SHA256_Update(&context, password, passlen);
	SHA256_Final(md, &context);
	res = calloc(68 , sizeof(unsigned char));
	for(long unsigned int i = 0; i < sizeof(md); i++){
		res[a] = hex[md[i] / 16];
		res[a + 1] = hex[md[i] % 16];
		a +=2;
	}
	return(res);
}
