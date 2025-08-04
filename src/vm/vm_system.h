#ifndef __VM_SYSTEM_H__
#define __VM_SYSTEM_H__

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "vm.h"

BANKREF_EXTERN(VM_SYSTEM)

void vm_sys_time(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED;
void vm_sleep(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED;
void vm_raise(SCRIPT_CTX * THIS, UINT8 code, UINT8 size) OLDCALL BANKED;
void vm_reset(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_dbginfo(SCRIPT_CTX * THIS) OLDCALL BANKED;

#endif /* __VM_SYSTEM_H__ */
