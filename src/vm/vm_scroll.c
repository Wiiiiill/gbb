#pragma bank 255

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "utils/scroll.h"
#include "utils/utils.h"

#include "vm_device.h"
#include "vm_graphics.h"
#include "vm_scroll.h"

BANKREF(VM_SCROLL)

void vm_scroll(SCRIPT_CTX * THIS) OLDCALL BANKED {
    const UINT8 x     = (UINT8)*(--THIS->stack_ptr);
    const UINT8 y     = (UINT8)*(--THIS->stack_ptr);
    const UINT8 w     = (UINT8)*(--THIS->stack_ptr);
    const UINT8 h     = (UINT8)*(--THIS->stack_ptr);
    const UINT8 layer = (UINT8)*(--THIS->stack_ptr);
    const UINT8 tile  = (UINT8)*(--THIS->stack_ptr);
    const UINT8 attr  = (UINT8)*(--THIS->stack_ptr);
    const UINT8 dir   = (UINT8)*(--THIS->stack_ptr);
    UINT8 * base;

    if (layer == GRAPHICS_LAYER_WINDOW)         base = get_win_addr();
    else /* if (layer == GRAPHICS_LAYER_MAP) */ base = get_bkg_addr();
    base += x + MUL32(y);

    if (device_type & DEVICE_TYPE_CGB) {
        VBK_REG = VBK_ATTRIBUTES;
        if (dir == DIRECTION_UP)                scroll_up  (base, w, h, attr);
        else /* if (dir == DIRECTION_DOWN) */   scroll_down(base, w, h, attr);
        VBK_REG = VBK_TILES;
    }
    if (dir == DIRECTION_UP)                    scroll_up  (base, w, h, tile);
    else /* if (dir == DIRECTION_DOWN) */       scroll_down(base, w, h, tile);
}
