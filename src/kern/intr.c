#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/i8259.h>
#include <sys/intr.h>
#include <sys/io.h>

#define INTR_STR_LEN 32

/*
 * This table holds isr function pointers that can be chained together
 * to support multiple isrs per interrupt
 */
static struct isr isrfunctab[ISRS];

/*
 * This table maintains the lists of isrs that are called when an
 * interrupt occurs.  The elements of each list are elements of the
 * isr function table.
 */
static isr_t isrtab[INTRS];

void
intr_init() {
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

static __inline void
isr_init(isr_t isr) {
    isr->f = NULL;
    isr->params = NULL;
    isr->next = NULL;
}

void
isrtab_init() {
    int i;

    for (i = 0; i < ISRS; i++)
        isr_init(&(isrfunctab[i]));
    for (i = 0; i < INTRS; i++)
        isrtab[i] = NULL;
}

static int
fatal(int intr) {
    if (intr == INTR_PGFLT || intr == INTR_DIVERR || intr == INTR_OVRFLW ||
        intr == INTR_BOUNDS || intr == INTR_INVOP || intr == INTR_NOCOPR ||
        intr == INTR_DOUBLE || intr == INTR_INVTSS || intr == INTR_NOSEG ||
        intr == INTR_STACK || intr == INTR_GENPROT || intr == INTR_PGFLT ||
        intr == INTR_COPRERR)
        return 1;
    return 0;
}

void
handl(int intr) {
    for (isr_t isr = isrtab[intr]; isr != NULL; isr = isr->next)
        (*(isr->f))(isr->params);

    if (fatal(intr))
        // TODO halt();
        for (;;)
            ;
}

int
isr_inst(int intr, isr_func_t f, void *params) {
    isr_t isr;
    int i;

    if (intr < 0 || intr >= INTRS || f == NULL)
        return EINVAL;

    disable;

    /* Get a free slot in the isr function table */
    for (i = 0; i < ISRS; i++)
        if (isrfunctab[i].f == NULL)
            break;
    if (i == ISRS) {
        enable;
        return EAGAIN;
    }
    isrfunctab[i].f = f;
    isrfunctab[i].params = params;

    if (isrtab[intr] == NULL) {
        isrtab[intr] = &(isrfunctab[i]);
        enable;
        return 0;
    }
    for (isr = isrtab[intr]; isr->next != NULL; isr = isr->next)
        ;
    isr->next = &(isrfunctab[i]);

    enable;
    return 0;
}
