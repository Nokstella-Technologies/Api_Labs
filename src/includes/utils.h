
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
 * @brief Recovers an especific query of the uri.  
 * 
 * @param buff all content of the header of the request.
 * @param search the content to be searched.
 * @return int id of the query.
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
 * @brief Recovers an especific content from the body of the request. 
 * 
 * @param buff all content of the body of the request.
 * @param camp the name of the field that will be recovered. 
 * @return char* value of the camp. 
 */
char			*parseBodyContet(const char *buff,const char *camp);

/**
 * @brief Funcion that encrypt a string with the sha256 algorithm.
 * 
 * @param password password given by the user.
 * @param passlen password lenght.
 * @return unsigned char* encypted password.
 */
unsigned char	*encrypt(unsigned char *password, int passlen);

/**
 * @brief Create a JWT token that is given to the user so he can login in next time without give a password.
 * 
 * @return char* return encrypted token.
 */
char			*createJWT(void);

/**
 * @brief Recovers the token from the requisition, so he can return it back.
 * 
 * @param buff token passed by. 
 * @return char* parsed token. 
 */
char			*parseToken(const char *buff);

#endif