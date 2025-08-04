        .include "global.s"

        .globl     _audio_update

        .area      _HEADER_TIMER(ABS)
        .org       0x50            ; TIM isr
        ei
        jp         .TIM_isr

        .area      _HOME
.TIM_isr::
        push       af
        push       hl
        push       bc
        push       de
        call       _audio_update
        pop        de
        pop        bc
        pop        hl
        WAIT_STAT
        pop        af
        reti
