#pragma bank 255

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "utils/utils.h"

#include "vm_physics.h"

BANKREF(VM_PHYSICS)

#define SHAPES_BOX_BOX     1
#define SHAPES_BOX_POINT   2

void vm_hits(SCRIPT_CTX * THIS, UINT8 shapes) OLDCALL BANKED {
    switch (shapes) {
    case SHAPES_BOX_BOX: {
            UINT16 ax0 = (UINT16)*(--THIS->stack_ptr);
            UINT16 ay0 = (UINT16)*(--THIS->stack_ptr);
            UINT16 ax1 = (UINT16)*(--THIS->stack_ptr);
            UINT16 ay1 = (UINT16)*(--THIS->stack_ptr);
            if (ax0 > ax1) SWAP_UINT16(ax0, ax1);
            if (ay0 > ay1) SWAP_UINT16(ay0, ay1);
            UINT16 bx0 = (UINT16)*(--THIS->stack_ptr);
            UINT16 by0 = (UINT16)*(--THIS->stack_ptr);
            UINT16 bx1 = (UINT16)*(--THIS->stack_ptr);
            UINT16 by1 = (UINT16)*(--THIS->stack_ptr);
            if (bx0 > bx1) SWAP_UINT16(bx0, bx1);
            if (by0 > by1) SWAP_UINT16(by0, by1);
            *(THIS->stack_ptr++) = (bx0 > ax1) || (bx1 < ax0) || (by0 > ay1) || (by1 < ay0) ?
                FALSE : TRUE;
        }

        break;
    case SHAPES_BOX_POINT: {
            UINT16 ax0 = (UINT16)*(--THIS->stack_ptr);
            UINT16 ay0 = (UINT16)*(--THIS->stack_ptr);
            UINT16 ax1 = (UINT16)*(--THIS->stack_ptr);
            UINT16 ay1 = (UINT16)*(--THIS->stack_ptr);
            if (ax0 > ax1) SWAP_UINT16(ax0, ax1);
            if (ay0 > ay1) SWAP_UINT16(ay0, ay1);
            UINT16 bx0 = (UINT16)*(--THIS->stack_ptr);
            UINT16 by0 = (UINT16)*(--THIS->stack_ptr);
            *(THIS->stack_ptr++) = (bx0 < ax0) || (bx0 > ax1) || (by0 < ay0) || (by0 > ay1) ?
                FALSE : TRUE;
        }

        break;
    }
}
