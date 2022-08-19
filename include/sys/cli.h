#ifndef __CLI_H
#define __CLI_H

#define PROMPT "> "
#define CMD_LINE_LEN 80

int get_cmdline(char *cmdline, int len);
void nextarg(char *ln, int *pos, char *sep, char *arg);

void cmd_cat(char *pwd, char *cmdline, int *pos);
void cmd_help();
void cmd_hexdump(char *pwd, char *cmdline, int *pos);
void cmd_ls(char *pwd, char *cmdline, int *pos);
void cmd_cd(char *pwd, int pwdlen, char *cmdline, int *pos);
void cmd_ft();

#endif
