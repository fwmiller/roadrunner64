#ifndef __INTR_H
#define __INTR_H

#define INTRS 64
#define ISRS INTRS

/* PC ISA interrupt requests */
#define IRQ_TMR 0
#define IRQ_KBD 1
#define IRQ_SERALT 3
#define IRQ_SERPRI 4
#define IRQ_FD 6
#define IRQ_PARA 7
#define IRQ_RTC 8
#define IRQ_AUX 12
#define IRQ_MATHCOPRERR 13
#define IRQ_HD 14

#define IRQ2INTR(IRQ) (32 + IRQ)

/* x86 exceptions (0 - 31) */
#define INTR_DIVERR 0
#define INTR_DEBUG 1
#define INTR_NMI 2
#define INTR_BRKPNT 3
#define INTR_OVRFLW 4
#define INTR_BOUNDS 5
#define INTR_INVOP 6
#define INTR_NOCOPR 7
#define INTR_DOUBLE 8
#define INTR_INVTSS 10
#define INTR_NOSEG 11
#define INTR_STACK 12
#define INTR_GENPROT 13
#define INTR_PGFLT 14
#define INTR_COPRERR 16

/* PC ISA interrupts (32 - 47) */
#define INTR_TMR IRQ2INTR(IRQ_TMR)
#define INTR_KBD IRQ2INTR(IRQ_KBD)
#define INTR_SERALT IRQ2INTR(IRQ_SERALT)
#define INTR_SERPRI IRQ2INTR(IRQ_SERPRI)
#define INTR_FD IRQ2INTR(IRQ_FD)
#define INTR_PARA IRQ2INTR(IRQ_PARA)
#define INTR_RTC IRQ2INTR(IRQ_RTC)
#define INTR_AUX IRQ2INTR(IRQ_AUX)
#define INTR_MATHCOPRERR IRQ2INTR(IRQ_MATHCOPRERR)
#define INTR_HD IRQ2INTR(IRQ_HD)

/* Kernel interrupts (48 - 63) */
#define INTR_SYSCALL 48

#define disable __asm__ __volatile__("cli")
#define enable __asm__ __volatile__("sti");

typedef void (*isr_func_t)(void *params);

typedef struct isr {
    isr_func_t f;
    void *params;
    struct isr *next;
} * isr_t;

void intr_init();
int intr_mask(int intr);
int intr_unmask(int intr);
void intr_eoi(int intr);
void isrtab_init();
int isr_inst(int intr, isr_func_t f, void *params);
int isr_uninst(int intr, isr_func_t f);

#endif
