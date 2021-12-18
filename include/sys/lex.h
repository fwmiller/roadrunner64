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
#define LEX_DASH	7
#define LEX_QUESTION	8
#define LEX_SLASH	9
#define LEX_PERIOD	10
	int type;
	int val;
	char s[80];
} *lex_t;

void nextlex(char *ln, int *pos, lex_t l);

#endif
