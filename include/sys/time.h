#ifndef __REAL_TIME_H
#define __REAL_TIME_H

#include <stdint.h>

typedef uint64_t tick_t;

tick_t get_current_tick();

#endif
