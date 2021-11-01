#include <stdlib.h>

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys.h>
#include <sys/config.h>
#include <sys/intr.h>
#include <sys/i8259.h>
#include <sys/intr.h>
#include <sys/mc146818.h>
#include <sys/queue.h>
#include <sys/time.h>
#include <sys/timer.h>
#include <sys/tmr.h>

#define EPOCH_YEAR	1970
#endif
#include <config.h>
#include <stdint.h>
#include <time.h>

/* Duration added to current time of day for each timer interrupt */
ulong_t tick = 1000000 / CLOCK;

static struct timeval systemclock = { 0, 0 };

#if 0
static int timerclock = 0;

static void clock_isr(void *params)
{
	proc_t proc;
	int preempt = 0;

	disable;

	/* Increment system time */
	systemclock.tv_usec += tick;
	timernormalize(&systemclock);

	/* Increment timer clock */
	timerclock += tick;
	if (timerclock >= TIMER_ISR_PERIOD) {
		timer_isr();
		timerclock = 0;
		preempt = 1;
	}

	/* Issue timer 0 eoi */
	outb(I8259_MSTR_CTRL, I8259_EOI_TMR);

	if (preempt) {
		proc = firstq(&ready);
		if (proc != NULL) {
			current->state = PS_READY;
			insq(current, &ready);
			proc_transfer();	/* enables interrupts */
		} else
			enable;
	}
}

void time_init()
{
	char buf[sizeof(struct tm)];
	struct tm *tm;

	isr_inst(INTR_TMR, clock_isr, NULL);

	/* A tmr frequency of zero causes the default CLOCK to be used */
	tmrstart(tmrcount(0));

	intr_unmask(INTR_TMR);

	tm = (struct tm *)buf;
	tm->tm_sec = bcd2int(loadcmosbyte(MC146818_SEC));
	tm->tm_min = bcd2int(loadcmosbyte(MC146818_MIN));
	tm->tm_hour = bcd2int(loadcmosbyte(MC146818_HOUR));
	tm->tm_mday = bcd2int(loadcmosbyte(MC146818_MDAY));
	tm->tm_mon = bcd2int(loadcmosbyte(MC146818_MON)) - 1;
	tm->tm_year = bcd2int(loadcmosbyte(MC146818_YEAR));

	/* Y2K */
	if (tm->tm_year < EPOCH_YEAR % 100)
		tm->tm_year += 100;

	tm->tm_wday = 0;
	tm->tm_yday = 0;
	tm->tm_isdst = 0;

	systemclock.tv_sec = tm2time(tm);
}
#endif

time_t time()
{
	return systemclock.tv_sec;
}

void utime(long *tv_sec, long *tv_usec)
{
	/* The caller must disable/enable interrupts */

	if (tv_sec == NULL || tv_usec == NULL)
		return;

	*tv_sec = systemclock.tv_sec;
	*tv_usec = systemclock.tv_usec;
}
