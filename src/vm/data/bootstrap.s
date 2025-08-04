        .include "vm.i"

        .area _CODE_9

        ___bank_BOOTSTRAP = 9
        .globl ___bank_BOOTSTRAP

_BOOTSTRAP::
; 1$:
        VM_PRINT        1, 0
                .asciz "No program"
        ; VM_JUMP         1$              ; Loop.
        VM_HALT
