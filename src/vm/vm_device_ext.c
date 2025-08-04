#pragma bank 255

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "utils/text.h"

#include "vm_device.h"

BANKREF(VM_DEVICE_EXT)

/**< Streaming. */

void vm_stream(SCRIPT_CTX * THIS, UINT8 status) OLDCALL BANKED {
    UINT8 * reg  = (UINT8 *)STREAMING_STATUS_REG;
    UINT8 * addr = (UINT8 *)STREAMING_ADDRESS;
    UINT16 val   = 0;

    if (status == STREAMING_STATUS_FILLED)
        val = (UINT16)*(--THIS->stack_ptr);

    if (!(device_type & DEVICE_TYPE_GBB)) // Ignore streaming if extension features are not supported.
        return;

    // Check for streaming status.
    if (*reg != STREAMING_STATUS_READY) {
        // Still busy, wait for ready.
        if (status == STREAMING_STATUS_FILLED)
            *(THIS->stack_ptr++) = val; // Push back the value.
        THIS->PC -= INSTRUCTION_SIZE + sizeof(status); // Wait.

        return;
    }

    if (status == STREAMING_STATUS_FILLED) { // Fill a byte.
        *reg = STREAMING_STATUS_BUSY;
        *addr = (UINT8)val;
        *reg = STREAMING_STATUS_FILLED;
    } else /* if (status == STREAMING_STATUS_EOS) */ { // Mark the status as end-of-stream.
        *reg = STREAMING_STATUS_EOS;
    }
}

/**< Shell. */

void vm_shell(SCRIPT_CTX * THIS, UINT8 nargs) OLDCALL BANKED {
    UINT8 * reg = (UINT8 *)TRANSFER_STATUS_REG;
    if (!(device_type & DEVICE_TYPE_GBB)) { // Ignore streaming if extension features are not supported.
        print(THIS, FALSE, nargs, TEXT_PRINT_MODE_NONE);

        return;
    }

    // Check for transfer status only on a device with extension support.
    if (*reg != TRANSFER_STATUS_READY) {
        // Still busy, wait for ready.
        THIS->PC -= INSTRUCTION_SIZE + sizeof(nargs);

        return;
    }

    *reg = TRANSFER_STATUS_BUSY;
    print(THIS, FALSE, nargs, TEXT_PRINT_MODE_SHELL); // Format to the shell buffer.
    *reg = TRANSFER_STATUS_FILLED;
}
