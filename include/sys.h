#ifndef __SYS_H
#define __SYS_H

void kprintf(const char *fmt, ...);

void halt();
void reboot();
int load(char *path, char **prog, uint32_t * size, char **start);

#endif
