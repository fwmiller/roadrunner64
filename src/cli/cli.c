#include <stdio.h>
#include <string.h>
#include <sys/cli.h>

static char pwd[CMD_LINE_LEN];

void
cli() {
    char cmdline[CMD_LINE_LEN];
    char arg[CMD_LINE_LEN];
    int pos;

    memset(pwd, 0, CMD_LINE_LEN);
    strcpy(pwd, "/");

    for (;;) {
        printf(pwd);
        printf(PROMPT);

        get_cmdline(cmdline, CMD_LINE_LEN);
        if (strlen(cmdline) == 0)
            continue;
#if 0
        if (cmdline[0] == '/') {
            /*
             * A full path has been specified as the first
             * argument.   Try to load and run the named
             * executable
             */
            int fd = open(cmdline, 0);

            for (char ch = 0;;) {
                int len = read(fd, &ch, 1);
                if (len <= 0)
                    break;

                printf("%c", ch);
            }
        }
#endif
        pos = 0;
        memset(arg, 0, CMD_LINE_LEN);
        nextarg(cmdline, &pos, " ", arg);

        if (strcmp(arg, "cat") == 0)
            cmd_cat(pwd, cmdline, &pos);

        else if (strcmp(arg, "hexdump") == 0)
            cmd_hexdump(pwd, cmdline, &pos);

        else if (strcmp(arg, "ls") == 0)
            cmd_ls(pwd, cmdline, &pos);

        else if (strcmp(arg, "pwd") == 0)
            printf("%s\r\n", pwd);

        else if (strcmp(arg, "cd") == 0)
            cmd_cd(pwd, CMD_LINE_LEN, cmdline, &pos);

        else if (strcmp(arg, "ft") == 0)
            cmd_ft();

        else if (strcmp(arg, "help") == 0)
            cmd_help();
    }
}
