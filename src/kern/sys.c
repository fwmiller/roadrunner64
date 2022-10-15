#include <stdio.h>
#include <sys/sys.h>

void
word_widths() {
    if (sizeof(uint8_t) != 1) {
        printf("sizeof(uint8_t) = %u bytes\r\n", sizeof(uint8_t));
        halt();
    }
    if (sizeof(uint16_t) != 2) {
        printf("sizeof(uint16_t) = %u bytes\r\n", sizeof(uint16_t));
        halt();
    }
    if (sizeof(uint32_t) != 4) {
        printf("sizeof(uint32_t) = %u bytes\r\n", sizeof(uint32_t));
        halt();
    }
    if (sizeof(uint64_t) != 8) {
        printf("sizeof(uint64_t) = %u bytes\r\n", sizeof(uint64_t));
        halt();
    }
    if (sizeof(void *) != 8) {
        printf("sizeof(void *) = %u bytes\r\n", sizeof(void *));
        halt();
    }
}

void
halt() {
    __asm__("hlt");
}
