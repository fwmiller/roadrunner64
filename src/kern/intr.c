#include <stdint.h>
#include <sys/i8259.h>
#include <sys/intr.h>
#include <sys/io.h>

struct idt_desc {
    uint32_t seg_off;
    uint32_t off_type;
    uint32_t off;
    uint32_t rsvd;
} __attribute__((packed));

typedef struct idt_desc *idt_desc_t;

extern idt_desc_t idt64;

static void
idt_desc_init(idt_desc_t idt_desc, uint64_t offset) {
    idt_desc->seg_off = (0x10 << 16) | (offset & 0xffff);
    idt_desc->off_type = (offset & 0xffff0000) | 0x8f00;  // Interrupt gate
    idt_desc->off = offset >> 32;
    idt_desc->rsvd = 0;
}

void
__gp_excp() {
    return;
}

void
__tmr_isr() {
    return;
}

void
idt_init() {
    /* Setup the general protection fault excpetion descriptor */
    idt_desc_init((idt_desc_t) (idt64 + 13 * 16), (uint64_t) __gp_excp);

    /* Setup the timer interrupt descriptor */
    idt_desc_init((idt_desc_t) (idt64 + 32 * 16), (uint64_t) __tmr_isr);
}

void
intr_init() {
    /* Everything masked */
    outb(I8259_MSTR_CTRL, I8259_MSTR_ICW1);
    outb(I8259_SLV_CTRL, I8259_SLV_ICW1);
    outb(I8259_MSTR_MASK, I8259_MSTR_ICW2);
    outb(I8259_SLV_MASK, I8259_SLV_ICW2);
    outb(I8259_MSTR_MASK, I8259_MSTR_ICW3);
    outb(I8259_SLV_MASK, I8259_SLV_ICW3);
    outb(I8259_MSTR_MASK, I8259_MSTR_ICW4);
    outb(I8259_SLV_MASK, I8259_SLV_ICW4);
    outb(I8259_MSTR_MASK, I8259_MSTR_DISABLE);
    outb(I8259_SLV_MASK, I8259_SLV_DISABLE);

    /* Unmask timer interrupt */
#if 1
    uint8_t mask = inb(I8259_MSTR_MASK);
    mask &= ~(0x01);
    outb(I8259_MSTR_MASK, mask);
#endif
}
