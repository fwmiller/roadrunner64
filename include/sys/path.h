#ifndef __PATH_H
#define __PATH_H

char *path_prepend(char *pre, char *path, int pathbufsize);
char *path_eval(char *path, int pathbufsize);

#endif
