#include <inet/arptab.h>
#include <inet/stats.h>
#include <inet/udptab.h>
#include <stdio.h>
#include <string.h>
#include <sys/sh.h>

void
set_color(char *color) {
    if (color != NULL)
        printf("%s", color);
}

static void
cmd_stats() {
    printf("frames   %u\r\n", stats.get_frame_count());
    printf("ethernet %u\r\n", stats.get_eth_count());
    printf("802.2    %u\r\n", stats.get_ieee802_2_count());
    printf("arp      %u\r\n", stats.get_arp_count());
    printf("rarp     %u\r\n", stats.get_rarp_count());
    printf("ipv4     %u\r\n", stats.get_ipv4_count());
    printf("ipv6     %u\r\n", stats.get_ipv6_count());
    printf("icmp     %u\r\n", stats.get_icmp_count());
    printf("udp      %u\r\n", stats.get_udp_count());
    printf("tcp      %u\r\n", stats.get_tcp_count());
}

void
sh() {
    char pwd[CMD_LINE_LEN];
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

        else if (strcmp(arg, "stack") == 0)
            cmd_stack();

        else if (strcmp(arg, "pci") == 0)
            cmd_pci();

        else if (strcmp(arg, "time") == 0)
            cmd_time();

        else if (strcmp(arg, "tsc") == 0)
            cmd_tsc();

        else if (strcmp(arg, "st") == 0)
            cmd_stats();

        else if (strcmp(arg, "bp") == 0)
            cmd_bp();

        else if (strcmp(arg, "arp") == 0)
            at->dump();

        else if (strcmp(arg, "udp") == 0)
            ut->dump();

        else if (strcmp(arg, "help") == 0 || strcmp(arg, "?") == 0)
            cmd_help();
    }
}
