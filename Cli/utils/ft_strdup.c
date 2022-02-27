#include "cli.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*s;

	len = strlen(str) + 1;
	s = (char *)malloc(sizeof(char) * len);
	if (s == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		s[i] = str[i];
	return (s);
}