#ifndef USERS_H
# define USERS_H

#include "database.h"
#include "server.h"

typedef struct s_users{
	char *id;
	char *name;
	char *password;
}			t_users;

int addUsers(char *name, unsigned char *password, t_users *users);
int findUser(char *name, t_users *users);
int delUsers(int id);

#endif