#ifndef __VM_SCROLL_H__
#define __VM_SCROLL_H__

#if defined __SDCC
#   include <gb/metasprites.h>
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "vm.h"

BANKREF_EXTERN(VM_SCROLL)

void vm_scroll(SCRIPT_CTX * THIS) OLDCALL BANKED;

#endif /* __VM_SCROLL_H__ */
