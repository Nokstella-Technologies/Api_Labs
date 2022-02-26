
#include "utils.h"

int	compareHash(unsigned char *Pass, unsigned char *EncryptedPass)
{
	unsigned char *comp = encrypt(Pass, strlen((char *)Pass));

	if(strcmp((char *)comp, (char *)EncryptedPass) == 0) {
		free(comp);
		return(0);
	}
	free(comp);
	return(-1);
}

