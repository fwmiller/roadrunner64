#include <ctype.h>
#include <stdlib.h>
#include <sys/lex.h>

#define LEX_SINGLE_CHAR(TYPE)						\
    l->type = TYPE;							\
    *(s++) = ch;							\
    *s = '\0';								\
    (*pos)++

void
nextlex(char *ln, int *pos, lex_t l)
{
	char *s;
	char ch;
	int acc;

	ch = ln[*pos];
	while (isspace(ch))
		ch = ln[++(*pos)];

	s = l->s;

	if (isalpha(ch)) {
		l->type = LEX_ID;

		do {
			*(s++) = ch;
			ch = ln[++(*pos)];
		}
		while (isalpha(ch) || isdigit(ch));
		*s = '\0';
		return;
	}
	if (isdigit(ch)) {
		l->type = LEX_NUM;

		acc = 0;
		do {
			*(s++) = ch;
			acc = (acc * 10) + (ch - '0');
			ch = ln[++(*pos)];
		}
		while (isdigit(ch));
		*s = '\0';

		l->val = acc;
		return;
	}
	switch (ch) {
	case '\0':
		l->type = LEX_EOL;
		*s = '\0';
		break;

	case '\r':
		LEX_SINGLE_CHAR(LEX_CR);
		break;
	case '\n':
		LEX_SINGLE_CHAR(LEX_LF);
		break;
	case ':':
		LEX_SINGLE_CHAR(LEX_COLON);
		break;
	case '-':
		LEX_SINGLE_CHAR(LEX_DASH);
		break;
	case '?':
		LEX_SINGLE_CHAR(LEX_QUESTION);
		break;
	case '/':
		LEX_SINGLE_CHAR(LEX_SLASH);
		break;
	case '.':
		LEX_SINGLE_CHAR(LEX_PERIOD);
		break;
	default:
		l->type = LEX_NULL;
		*s = '\0';
		(*pos)++;
	}
}
