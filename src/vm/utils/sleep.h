#ifndef __SLEEP_H__
#define __SLEEP_H__

#if defined __SDCC
#   include <gbdk/platform.h>
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

/**
 * Sleeps for the specific number of milliseconds.
 * Uses no timers or interrupts, and can be called with
 * interrupts disabled.
 */
void sleep(UINT16 ms) BANKED PRESERVES_REGS(h, l);

#endif /* __SLEEP_H__ */
