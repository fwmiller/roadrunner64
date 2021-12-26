#ifndef __SYS_H
#define __SYS_H

#include <stdint.h>

void word_widths();
void halt();
void reboot();
int load(char *path, char **prog, uint32_t * size, char **start);

#endif
