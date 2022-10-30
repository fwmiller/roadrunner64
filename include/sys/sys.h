#ifndef __SYS_H
#define __SYS_H

#include <stdarg.h>
#include <stdint.h>

void print(char *string, int *pos, const char *fmt, va_list args);

void bufdump(char *buf, int size);

void word_widths();
void halt();
void reboot();
int load(char *path, char **prog, uint32_t *size, char **start);

#endif
