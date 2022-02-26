#include "server.h"
#include "database.h"
#include <time.h>

static void log_message(const char *filename, const char *message) {
	FILE *fp = fopen(filename, "a");

	if (fp != NULL) {
		fprintf(fp, "%s", message);
		fclose(fp);
	}
}

void send_log(struct mg_http_message *hm, t_res *res, const char *messageOk,
const char *messageError)
{
	time_t t = time(&t);
	if(res->status >= 400)
		MG_ERROR((":%d:%s:/%s:%s:%s:",res->status, strtok((char *)hm->method.ptr, " ") ,strtok((char *)hm->uri.ptr, " /"), messageError, ctime(&t)));
	else
		MG_INFO((":%d:%s:/%s:%s:%s",res->status, strtok((char *)hm->method.ptr, " ") , strtok((char *)hm->uri.ptr, " /"), messageOk, ctime(&t)));
}

static int addLogsDB(char **buf)
{
	MYSQL *con = mysql_init(NULL);
	char query[200];

	if (connect_mysql(con) < 0)
		return(-1);
	sprintf(query,"INSERT INTO `logs_api` VALUES(NULL, '%s', '%s','%s','%s', NOW());",buf[1],buf[2], buf[0], buf[4]);
	if(mysql_query(con, query)){
		mysql_close(con);
		return(-1);
	}
	mysql_close(con);
	return (0);
}

void generateLogs(const void *buf, size_t len, void *userdata)
{
	(void) userdata;
	char *buf2 = (char *)buf;
	if(*buf2 == ':')
	{
		if(addLogsDB(ft_split(buf2, ':')) < 0)
			printf("error %ld\n", len);
	}

	log_message("./logs/logs.txt", buf);
}
