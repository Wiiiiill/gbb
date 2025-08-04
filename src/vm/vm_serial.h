#ifndef __VM_SERIAL_H__
#define __VM_SERIAL_H__

#include "vm.h"

BANKREF_EXTERN(VM_SERIAL)

#define SERIAL_ERROR   0xFFFF
#define SERIAL_BUSY    0xFFFE
#define SERIAL_IDLE    0xFFFD

void vm_sread(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_swrite(SCRIPT_CTX * THIS) OLDCALL BANKED;

#endif /* __VM_SERIAL_H__ */
