#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#if defined __SDCC
#   include <gbdk/platform.h>
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "../vm.h"

#if VM_EXCEPTION_ENABLED
BOOLEAN exception_handle_vm_raised(void) BANKED;
#endif /* VM_EXCEPTION_ENABLED */

#endif /* __EXCEPTION_H__ */
