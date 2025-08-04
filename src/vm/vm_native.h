#ifndef __VM_NATIVE_H__
#define __VM_NATIVE_H__

#if defined __SDCC
#   include <gbdk/platform.h>
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "vm.h"

BANKREF_EXTERN(VM_NATIVE)

BOOLEAN wait_for(POINTER THIS, BOOLEAN start, UINT16 * stack_frame) OLDCALL BANKED; // INVOKABLE.
BOOLEAN wait_until_confirm(POINTER THIS, BOOLEAN start, UINT16 * stack_frame) OLDCALL BANKED; // INVOKABLE.

BOOLEAN error(POINTER THIS, BOOLEAN start, UINT16 * stack_frame) OLDCALL BANKED; // INVOKABLE.

#endif /* __VM_NATIVE_H__ */
