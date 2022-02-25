
#include "utils.h"

int	compareHash(unsigned char *Pass, unsigned char *EncryptedPass)
{
	unsigned char *comp = encrypt(Pass, strlen(Pass));

	if(strcmp(comp, (char *)EncryptedPass) == 0) {
		free(comp);
		return(0);
	}
	free(comp);
	return(-1);
}

