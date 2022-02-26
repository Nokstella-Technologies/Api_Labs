#include "database.h"

char *get_host()
{
	char	hostbuffer[256];
	char	*IPbuffer;
	struct	hostent *host_entry;

	gethostname(hostbuffer, sizeof(hostbuffer));
	host_entry = gethostbyname(hostbuffer);
	IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
	return(IPbuffer);
}

int connect_mysql(MYSQL *con)
{
	if (mysql_real_connect(con, HOST, USER, PASS, DB, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		mysql_close(con);
		return(-1);
	}
	return(0);
}
