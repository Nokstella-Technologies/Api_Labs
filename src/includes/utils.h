
#ifndef UTILS_H
#define UTILS_H

# include <jansson.h>
# include <rhonabwy.h>
# include <string.h> 

char			*ft_strdup(const char *str);
char			**ft_split(char const *s, char c);
int				parseHeaderForId(const char *buff);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				compareHash(unsigned char *Pass, unsigned char *EncryptedPass);
const char		*parseBodyContet(const char *buff,const char *camp);
unsigned char	*encrypt(unsigned char *password, int passlen);
char			*createJWT(void);
char			*parseToken(const char *buff);

#endif