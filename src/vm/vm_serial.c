#pragma bank 255

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "vm_device.h"
#include "vm_serial.h"

BANKREF(VM_SERIAL)

void vm_sread(SCRIPT_CTX * THIS) OLDCALL BANKED {
    const BOOLEAN wait = (BOOLEAN)*(--THIS->stack_ptr);
    receive_byte();
    if (wait) {
        while (_io_status == IO_RECEIVING) { /* Wait until received. */ }
        if (_io_status == IO_IDLE)
            *(THIS->stack_ptr++) = _io_in;
        else
            *(THIS->stack_ptr++) = SERIAL_ERROR;
    } else {
        if      (_io_status == IO_IDLE)      *(THIS->stack_ptr++) = _io_in;
        else if (_io_status == IO_RECEIVING) *(THIS->stack_ptr++) = SERIAL_BUSY;
        else                                 *(THIS->stack_ptr++) = SERIAL_ERROR;
    }
}

void vm_swrite(SCRIPT_CTX * THIS) OLDCALL BANKED {
    _io_out            = (UINT8)*(--THIS->stack_ptr);
    const BOOLEAN wait = (BOOLEAN)*(--THIS->stack_ptr);
    send_byte();
    if (wait) {
        while (_io_status == IO_SENDING) { /* Wait until sent. */ }
        if (_io_status == IO_IDLE)
            *(THIS->stack_ptr++) = _io_out;
        else
            *(THIS->stack_ptr++) = SERIAL_ERROR;
    } else {
        if      (_io_status == IO_IDLE)    *(THIS->stack_ptr++) = _io_out;
        else if (_io_status == IO_SENDING) *(THIS->stack_ptr++) = SERIAL_BUSY;
        else                               *(THIS->stack_ptr++) = SERIAL_ERROR;
    }
}
