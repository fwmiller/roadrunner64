#ifndef __TMR_H
#define __TMR_H

#include <sys/types.h>

/* Routines for managing the i8254 counter 0 periodic timer */

/* Compute a count value for a specified frequency */
unsigned tmrcount(unsigned freq);

/* Get the number of microseconds per counter 0 expiration */
unsigned tmrtick();

/* Start the i8254 counter 0 periodic timer */
void tmrstart(unsigned count);

/* Read the current value of counter 0 */
unsigned tmrread();

#endif
