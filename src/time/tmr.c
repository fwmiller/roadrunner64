#include <sys/config.h>
#include <sys/i8254.h>
#include <sys/io.h>
#include <sys/tmr.h>

#define DIV16(val) ((val >> 16) > 0 ? 0xffff : val)
#define TICK (1000000 / CLOCK)

unsigned
tmrcount(unsigned freq) {
    if (freq == 0)
        return (unsigned) (I8254_CLK / CLOCK);
    return (unsigned) DIV16(I8254_CLK / freq);
}

unsigned
tmrtick() {
    return TICK;
}

void
tmrstart(unsigned count) {
    outb(I8254_CTRL, I8254_CNTR_0_START);
    outb(I8254_CNTR_0, count);
    outb(I8254_CNTR_0, count >> 8);
}

unsigned
tmrread() {
    unsigned count = 0;

    outb(I8254_CTRL, I8254_CNTR_0_LATCH);
    count = inb(I8254_CNTR_0);
    count <<= 8;
    count = inb(I8254_CNTR_0);
    return count;
}
