#ifndef __SHELL_H
#define __SHELL_H

#define PROMPT "> "
#define CMD_LINE_LEN 80

#define NC "\033[0m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

int get_cmdline(char *cmdline, int len);
void nextarg(char *ln, int *pos, char *sep, char *arg);

void cmd_cat(char *pwd, char *cmdline, int *pos);
void cmd_help();
void cmd_hexdump(char *pwd, char *cmdline, int *pos);
void cmd_ls(char *pwd, char *cmdline, int *pos);
void cmd_cd(char *pwd, int pwdlen, char *cmdline, int *pos);
void cmd_ft();
void cmd_stack();
void cmd_pci();

void set_color(char *color);

#endif
