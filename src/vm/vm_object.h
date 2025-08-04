#ifndef __VM_OBJECT_H__
#define __VM_OBJECT_H__

#include "vm.h"

BANKREF_EXTERN(VM_OBJECT)

void vm_object_is(SCRIPT_CTX * THIS, UINT8 type) OLDCALL BANKED;

#endif /* __VM_OBJECT_H__ */
