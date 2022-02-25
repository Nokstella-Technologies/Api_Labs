
#include "cli.h"

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
 	exit(1);
}

void	print_res(MYSQL *con)
{
	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
	{
			finish_with_error(con);
	}
	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	while ((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < num_fields; i++)
		{
			if (i == 0)
			{
				 while(field = mysql_fetch_field(result))
				{
					printf("%s ", field->name);
				}
				printf("\n");
			}
			printf("%s	", row[i] ? row[i] : "NULL");
		}
	}
	mysql_free_result(result);
}


void	print_normal(void)
{
	MYSQL *con = mysql_init(NULL);

	if (mysql_real_connect(con, HOST, USER, PASS, DB, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	if(mysql_query(con, "SELECT * FROM logs_api;"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	print_res(con);
	mysql_close(con);
}

// -route=/project
// -method=GET
// -data=20/10/2000
// -status=
// -list

void errorUnixArgv(void)
{
	printf("Invalid option use this:\n\n\t\t-route=/(...)\
			\n\n\t\t-method=GET or POST or PUT or DELETE\
			\n\n\t\t-data=yyyy-mm-dd\
			\n\n\t\t-status=ERROR or OK\
			\n\n\t\t-list (to list all logs without this they will count!)\n");
	exit(1);
}

void verify_argv(int argc, char **argv, t_unix *parse)
{
	for(int a = 1; a < argc; a++)
	{
		if (strncmp(argv[a],"-route=", 7) == 0)
			parse->routes = strstr(argv[a], "=") + 1;
		else if(strncmp(argv[a],"-method=", 8)  == 0)
			parse->method = strstr(argv[a], "=") + 1;
		else if(strncmp(argv[a],"-data=", 6)  == 0)
			parse->data = strstr(argv[a], "=") + 1;
		else if(strncmp(argv[a],"-status=", 8)  == 0){
			parse->status =  strstr(argv[a], "=") + 1;
			if (strcmp(parse->status,"OK")  != 0 &&
				strcmp(parse->status,"ERROR")  != 0)
				errorUnixArgv();
		}
		else if(strncmp(argv[a],"-list", 5)  == 0)
			parse->list = 1;
		else
			errorUnixArgv();
	}
}

void init_struct(t_unix *parse)
{
	parse->routes = NULL;
	parse->method = NULL;
	parse->data = NULL;
	parse->status = NULL;
	parse->list = 0;
}

int main (int argc, char **argv) {
	t_unix parse;

	if(argc == 1)
		print_normal();
	else
	{
		init_struct(&parse);
		verify_argv(argc, argv, &parse);
	}
}

// search all,
// select * from ~table~
// group by ~?