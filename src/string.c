#include <string.h>

size_t
strlen(const char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (size_t) i;
}

void *
memset(void *b, int c, size_t len)
{
	int i;

	for (i = 0; i < (int)len; i++)
		((char *)b)[i] = c;
	return b;
}
