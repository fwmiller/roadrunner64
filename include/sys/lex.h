#ifndef __LEX_H
#define __LEX_H

typedef struct lex {
#define LEX_NULL	0
#define LEX_CR		1
#define LEX_LF		2
#define LEX_EOL		3
#define LEX_ID		4
#define LEX_NUM		5
#define LEX_COLON	6
#define LEX_SEMICOLON	7
#define LEX_DASH	8
#define LEX_QUESTION	9
#define LEX_SLASH	10
#define LEX_PERIOD	11
	int type;
	int val;
	char s[80];
} *lex_t;

void nextarg(char *ln, int *pos, char *arg);
void nextlex(const char *ln, int *pos, lex_t l);

#endif
