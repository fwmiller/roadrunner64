#include <stdint.h>
#include <sys/intr.h>

struct idt_desc {
    uint32_t seg_off;
    uint32_t off_type;
    uint32_t off;
    uint32_t rsvd;
} __attribute__((packed));

typedef struct idt_desc *idt_desc_t;

extern idt_desc_t idt64;
extern void (*__isr)();

static void
idt_desc_init(idt_desc_t idt_desc, uint64_t offset) {
    idt_desc->seg_off = (0x10 << 16) | (offset & 0xffff);
    idt_desc->off_type = (offset & 0xffff0000) | 0x8f00;  // Interrupt gate
    idt_desc->off = offset >> 32;
    idt_desc->rsvd = 0;
}

void
idt_init() {
    /* Setup the timer interrupt descriptor */
    idt_desc_init((idt_desc_t) (idt64 + 32 * 16), (uint64_t) __isr);
}
