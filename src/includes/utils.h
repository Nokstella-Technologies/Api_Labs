
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
 * @brief Function that comapares the hash to see if it's equal and valid, or  * if the they do not match and is invalid.
 * 
 * @param Pass string that contains the key given by the user.
 * @param EncryptedPass encrypted by sha256 algorithym.
 * @return int 0 for OK and -1 for error.
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
 * @brief Funcion that encrypt a string with the sha256 alghoritym 
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