#ifndef CLI_H
# define CLI_H

# define FileLog "./src/logs/logs.txt"
# define Error 1
# define Sucess 2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_data {
	char	n_line[124];
	int		type;
}			t_data;

typedef struct s_project
{
	int	get;
	int	post;
	int	delete;
	int	put;
}		t_project;

typedef struct s_users
{
	int	post;
	int	delete;
}		t_users;

typedef struct s_routes {
	t_project project;
	t_users users;
	int	autheticated;
	int	other;
}			t_routes;

#endif