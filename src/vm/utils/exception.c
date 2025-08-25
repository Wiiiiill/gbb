#pragma bank 255

#if defined __SDCC
#   include <gbdk/console.h>
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "utils/text.h"
#include "utils/utils.h"

#if VM_EXCEPTION_ENABLED
BOOLEAN exception_handle_vm_raised(void) BANKED {
    switch (vm_exception_code) {
    case EXCEPTION_UNKNOWN_PARAMETER: {
            const unsigned char prompt[] = "UNKNOWN PARAM: ";
            unsigned char display_text[8];
            UINT8 n = uint16_to_hex_full(vm_exception_data, display_text);
            unsigned char* d = display_text + n;

            const UINT8 m = get_mode();
            if ((m & 0x07) == M_DRAWING) // Was graphics mode.
                mode(M_TEXT_OUT); // Uninstall VBL and LCD ISRs of the graphics mode.

            SHOW_BKG;
            WX_REG = 0, HIDE_WIN;
            move_bkg(0, 0);
            cls();
            print_banked(prompt, prompt + 15, FALSE, TEXT_PRINT_MODE_TEXT);
            print_banked(display_text, d, TRUE, TEXT_PRINT_MODE_TEXT);

            vm_exception_source = 0;
            vm_exception_data   = 0;
        }

        return TRUE;
    default:
        return FALSE;
    }
}
#endif /* VM_EXCEPTION_ENABLED */
