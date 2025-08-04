#ifndef __VM_MEMORY_H__
#define __VM_MEMORY_H__

#include "vm.h"

BANKREF_EXTERN(VM_MEMORY)

void vm_memcpy(SCRIPT_CTX * THIS, UINT8 src) OLDCALL BANKED;
void vm_memset(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_memadd(SCRIPT_CTX * THIS) OLDCALL BANKED;

#endif /* __VM_MEMORY_H__ */
