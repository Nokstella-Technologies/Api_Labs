
#include "cli.h"

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
 	exit(1);
}

void	print_res(MYSQL *con, int arg)
{

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
	{
			finish_with_error(con);
	}
	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	char *tmp = calloc((arg * 23 )+ 1 ,sizeof(char));
	printf("\n/%s\\\n", (char *)memset(tmp, '-', arg * 23));
	while(field = mysql_fetch_field(result))
	{
			printf("| %20s ", field->name);
	}
	printf("\n\\%s/\n", tmp);
	while ((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < num_fields; i++)
		{
			if (i == 0)
			{
				//inicio da linha
				//printf("\n");
			}
			if(strlen(row[i]) > 20 )
			{
				row[i][19] = '*';
				row[i][20] = 0;
			}
			printf("| %20s ", row[i] ? row[i] : "NULL");
			//10+strlen(s)/2,s,10-strlen(s)/2,""
			//printf("\n");
		}
	printf(" |\n");
	}
	printf("\\%s/\n", tmp);
	free(tmp);
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
	if(mysql_query(con, "SELECT COUNT(method), method, uri, status, date \
	FROM logs_api \
	GROUP BY method, status, uri;"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	print_res(con,5);
	mysql_close(con);
}

char *addQuery(char *query, char *message, char *search ,char *type)
{
	char *tmp = "";

	tmp = query;
	query = calloc( strlen(tmp) + 50 , sizeof(char));
	sprintf(query, "%s %s %s like '%%%s%%'", tmp, message,type, search);
	free(tmp);
	return (query);
}


void makeQuery(t_unix *parse)
{
	MYSQL *con = mysql_init(NULL);
	char query[300];
	char *complement;

	if (mysql_real_connect(con, HOST, USER, PASS, DB, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	if(parse->list == 1)
	{
		complement = calloc(50 , sizeof(char));
		if (parse->routes)
			sprintf(complement, "WHERE uri like '%%%s%%'", parse->routes);
		if (parse->method)
			complement = addQuery(complement, parse->routes ? "AND" : "WHERE", parse->method, "method");
		if (parse->status)
			complement = addQuery(complement, parse->routes || parse->method ? "AND" : "WHERE", parse->status, "status");
		if (parse->data)
			complement = addQuery(complement, parse->routes || parse->method || parse->status ? "AND" : "WHERE", parse->data, "data");
		sprintf(query, "SELECT method ,uri, status, date \
		FROM logs_api %s;",complement);
		printf("%s\n", query);
		free(complement);
	}
	else
	{
		complement = calloc(50 , sizeof(char));
		if (parse->routes)
			sprintf(complement, "WHERE uri like '%%%s%%'", parse->routes);
		if (parse->method)
			complement = addQuery(complement, parse->routes ? "AND" : "WHERE", parse->method, "method");
		if (parse->status)
			complement = addQuery(complement, parse->routes || parse->method ? "AND" : "WHERE", parse->status, "status");
		if (parse->data)
			complement = addQuery(complement, parse->routes || parse->method || parse->status ? "AND" : "WHERE", parse->data, "data");
		sprintf(query, "SELECT COUNT(method) , uri, status, date \
		FROM logs_api %s GROUP BY method, uri;",complement);
		printf("%s\n", query);
	}
	if(mysql_query(con, query))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	print_res(con, 4);
}

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
			parse->status = strstr(argv[a], "=") + 1;
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
		makeQuery(&parse);
	}
}

// search all,
// select * from ~table~
// group by ~?