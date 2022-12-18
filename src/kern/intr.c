#include <stdint.h>
#include <stdio.h>
#include <sys/i8259.h>
#include <sys/io.h>

void
__handl(int intr) {
    printf("intr %d", intr);
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
    uint8_t mask = inb(I8259_MSTR_MASK);
    mask &= ~(0x01);
    outb(I8259_MSTR_MASK, mask);
}
