#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#if defined __SDCC
#   include <gbdk/platform.h>
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

BOOLEAN exception_handle_vm_raised(void) BANKED;

#endif /* __EXCEPTION_H__ */
