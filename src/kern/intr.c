#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/i8259.h>
#include <sys/intr.h>
#include <sys/io.h>
#include <sys/rtl8139.h>
#include <sys/time.h>

void
__handl(int intr) {
    intr_eoi(intr);

    if (intr == INTR_TMR)
        tick++;

    if (intr == IRQ2INTR(rtl8139_priv.f->irq))
        rtl8139_isr();
}

int
intr_unmask(int intr) {
    uint8_t mask;

    if (intr >= 32 && intr < 40) {
        mask = inb(I8259_MSTR_MASK);
        mask &= ~(0x01 << (intr - 32));
        outb(I8259_MSTR_MASK, mask);
        return 0;

    } else if (intr >= 40 && intr < 48) {
        mask = inb(I8259_SLV_MASK);
        mask &= ~(0x01 << (intr - 40));
        outb(I8259_SLV_MASK, mask);
        return 0;
    }
    return EINVAL;
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
#if 0
    uint8_t mask = inb(I8259_MSTR_MASK);
    mask &= ~(0x01);
    outb(I8259_MSTR_MASK, mask);
#endif
    printf("intr_init: unmask intr %d\r\n", INTR_TMR);

    intr_unmask(INTR_TMR);
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
