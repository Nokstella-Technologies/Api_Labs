
#include "cli.h"

static void filter_project (t_project *add, t_data *data, int *others)
{
	if (strstr(data->n_line, "GET") != NULL){
		add->get += 1;
	}
	else if (strstr(data->n_line, "POST") != NULL){
		add->post += 1;
	}
	else if (strstr(data->n_line, "DELETE") != NULL){
		add->delete += 1;
	}
	else if (strstr(data->n_line, "PUT") != NULL){
		add->put += 1;
	}
	else {
		*others += 1;
	}
}

static void filter_users (t_users *add, t_data *data, int *others)
{
	if (strstr(data->n_line, "POST") != NULL){
		add->post += 1;
	}
	else if (strstr(data->n_line, "DELETE") != NULL){
		add->delete += 1;
	}
	else {
		*others += 1;
	}
}

static void filter(t_data *data, t_routes *routes)
{
	if (strstr(data->n_line, "/project") != NULL ){
		filter_project(&routes->project, data, &routes->other);
	}
	else if (strstr(data->n_line, "/users")  != NULL ){
		filter_users(&routes->users, data, &routes->other);
	}
	else if (strstr(data->n_line, "/authenticated")  != NULL ){
		if (strstr(data->n_line, "POST")  != NULL )
			routes->autheticated += 1;
	}
	else {
		routes->other += 1;
	}
}

static void init_routes(t_routes *routes)
{
	routes->project.get = 0;
	routes->project.post = 0;
	routes->project.put = 0;
	routes->project.delete = 0;
	routes->users.delete = 0;
	routes->users.post = 0;
	routes->autheticated = 0;
	routes->other = 0;
}

int main(int argc, char **argv)
{
	FILE *logs = fopen(FileLog, "r");
	t_data data;
	t_routes routes;

	if (argc < 2)
	{
		data.type = 0;
		printf("-------------------------------------------------------------------------------------------------\n|\t%-10s\t|\t%-10s\t|\t%-10s\t|\t%-10s\t|\n-------------------------------------------------------------------------------------------------\n","Total Request","HTTP Method","Path", "Status Exit");
		init_routes(&routes);
		while(!feof(logs)){
			fgets(data.n_line, 124, logs);
			filter(&data, &routes);
			memset(data.n_line, 0, 124);
		}
		printf("|\t%-10d\t|\t%-10s\t|\t%-10s\t|\tStatus Exit\t|\n-------------------------------------------------------------------------------------------------\n", routes.autheticated, "POST", "/authentication");
		printf("|\t%-10d\t|\t%-10s\t|\t%-10s\t|\tStatus Exit\t|\n-------------------------------------------------------------------------------------------------\n", routes.project.get, "GET", "/projects");
		printf("|\t%-10d\t|\t%-10s\t|\t%-10s\t|\tStatus Exit\t|\n-------------------------------------------------------------------------------------------------\n", routes.project.post, "POST", "/projects");
		printf("|\t%-10d\t|\t%-10s\t|\t%-10s\t|\tStatus Exit\t|\n-------------------------------------------------------------------------------------------------\n", routes.project.delete, "DELETE", "/projects");
		printf("|\t%-10d\t|\t%-10s\t|\t%-10s\t|\tStatus Exit\t|\n-------------------------------------------------------------------------------------------------\n", routes.project.put, "PUT", "/projects");
		printf("|\t%-10d\t|\t%-10s\t|\t%-10s\t|\tStatus Exit\t|\n-------------------------------------------------------------------------------------------------\n", routes.users.post, "POST", "/users");
		printf("|\t%-10d\t|\t%-10s\t|\t%-10s\t|\tStatus Exit\t|\n-------------------------------------------------------------------------------------------------\n", routes.users.delete, "DELETE", "/users");
		printf("|\t%-10d\t|\t%-10s\t|\t%-10s\t|\tStatus Exit\t|\n-------------------------------------------------------------------------------------------------\n", routes.other, "Not allowed", "not allowed");
	}
	return(0);
}