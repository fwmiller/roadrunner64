#include <stdint.h>
#include <stdio.h>
#include <sys/i8259.h>
#include <sys/intr.h>
#include <sys/io.h>
#include <sys/time.h>

void
__handl(int intr) {
    intr_eoi(intr);

    if (intr == INTR_TMR)
        tick++;
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

void
intr_eoi(int intr) {
    if (intr < 32 || intr > 47)
        return;

    if (intr >= 32 || intr < 40)
        outb(I8259_MSTR_CTRL, (intr - 32) + I8259_EOI_TMR);
    else {
        outb(I8259_SLV_CTRL, (intr - 40) + I8259_EOI_TMR);
        outb(I8259_MSTR_CTRL, I8259_EOI_CAS);
    }
}
