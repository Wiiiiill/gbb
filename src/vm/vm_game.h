#ifndef __VM_GAME_H__
#define __VM_GAME_H__

#include "vm.h"

BANKREF_EXTERN(VM_GAME)

extern UINT8 game_has_input;

void game_init(void) BANKED;
void game_update(void) BANKED;

void vm_update(SCRIPT_CTX * THIS) OLDCALL BANKED; // UPDATE.

#endif /* __VM_GAME_H__ */
