
#ifndef UTILS_H
#define UTILS_H

# include <jansson.h>
# include <rhonabwy.h>
# include <string.h> 

/**
 * @brief Copy the STR to a new pointer.
 * 
 * @param str the string to be copy
 * @return a new address with the same string of str.
 */
char			*ft_strdup(const char *str);

/**
 * @brief Function separe the string S in a Matrix with the separator C
 * 
 * @param s string to be splited
 * @param c the caracter that will be used to separate the string
 * @return a pointer to the other pointer that have all the parters of the
 * splited string S
 */
char			**ft_split(char const *s, char c);

/**
 * @brief Copy the from the (S + START) to (LEN).
 * 
 * @param s the address of the start of the string
 * @param start start the copy from here.
 * @param len number of the bytes to be copy.
 * @return a new address to with the copy.
 */
char			*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief 
 * 
 * @param buff 
 * @param search 
 * @return int 
 */
int				parseHeaderForId(const char *buff, const char *search);

/**
 * @brief 
 * 
 * @param Pass 
 * @param EncryptedPass 
 * @return int 
 */
int				compareHash(unsigned char *Pass, unsigned char *EncryptedPass);

/**
 * @brief 
 * 
 * @param buff 
 * @param camp 
 * @return char* 
 */
char			*parseBodyContet(const char *buff,const char *camp);

/**
 * @brief 
 * 
 * @param password 
 * @param passlen 
 * @return unsigned char* 
 */
unsigned char	*encrypt(unsigned char *password, int passlen);

/**
 * @brief 
 * 
 * @return char* 
 */
char			*createJWT(void);

/**
 * @brief 
 * 
 * @param buff 
 * @return char* 
 */
char			*parseToken(const char *buff);

#endif