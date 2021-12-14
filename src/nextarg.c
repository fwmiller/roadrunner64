#include <ctype.h>
#include <string.h>

void
nextarg(char *ln, int *pos, char *arg)
{
	char *s;
	char ch;

	s = arg;

	ch = ln[*pos];
	while (isspace(ch))
		ch = ln[++(*pos)];

	s[0] = '\0';
	while (ch != '\0' && !isspace(ch)) {
		*(s++) = ch;
		ch = ln[++(*pos)];
	};
	*s = '\0';
}
