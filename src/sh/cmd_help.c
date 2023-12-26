#include <stdio.h>

void
cmd_help() {
    printf("\r\n");
    printf("cat <filename>\r\n");
    printf("  Print file contents as text\r\n");
    printf("\r\n");
    printf("hexdump <filename>\r\n");
    printf("  Print file contents as hexadecimal values\r\n");
    printf("\r\n");
    printf("ls <directory>\r\n");
    printf("  List the contents of a directory\r\n");
    printf("\r\n");
    printf("pwd\r\n");
    printf("  Print the current/working directory.  pwd is also \r\n");
    printf("  displayed with the command prompt\r\n");
    printf("\r\n");
    printf("cd <directory>\r\n");
    printf("  Change the current/working directory\r\n");
    printf("\r\n");
    printf("ft\r\n");
    printf("  Print the open file table\r\n");
    printf("\r\n");
    printf("stack\r\n");
    printf("  Print execution stack state\r\n");
    printf("\r\n");
    printf("pci\r\n");
    printf("  Print PCI bus devices\r\n");
    printf("\r\n");
    printf("time\r\n");
    printf("  Print time\r\n");
    printf("\r\n");
    printf("tsc\r\n");
    printf("  Print current Pentium timestamp counter value\r\n");
    printf("\r\n");
}
