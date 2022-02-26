#ifndef USERS_H
# define USERS_H

#include "database.h"
#include "server.h"

typedef struct s_users{
	char *id;
	char *name;
	char *password;
}			t_users;

/**
 * @brief This function emulates repository functions in modern languages, make the connection with database and add a new user data. 
 * 
 * @param name the new user name to be add to db.
 * @param password the new user password to be add to db.
 * @param users struct that saves our response.
 * @return int 0 for OK and -1 for error.
 */
int addUsers(char *name, unsigned char *password, t_users *users);

/**
 * @brief This function emulates repository functions in modern languages, make the connection with database and find a new user data. 
 * 
 * @param name user name to be found in the db.
 * @param users list where the function will look for the user to be found.
 * @return int 0 for OK and -1 for error.
 */
int findUser(char *name, t_users *users);

/**
 * @brief This function emulates repository functions in modern languages, make the connection with database and delete a new user data. 
 * 
 * @param id user id to be deleted in the db.
 * @return int 0 for OK and -1 for error.
 */
int delUsers(int id);

#endif