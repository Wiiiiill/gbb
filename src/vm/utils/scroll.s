        .include "global.s"

        .area _CODE

_get_win_addr::
        ldh     a,(.LCDC)
        bit     LCDCF_B_WIN9C00,a
        jr      Z,.is98
        jr      .is9c

_get_bkg_addr::
        ldh     a,(.LCDC)
        bit     LCDCF_B_BG9C00,a
        jr      NZ,.is9c
.is98:
        ld      de,#0x9800      ; DE = origin.
        ret
.is9c:
        ld      de,#0x9C00      ; DE = origin.
        ret

        .area _CODE_255

        ; void scroll_up(UINT8 * base, UINT8 w, UINT8 h, UINT8 data) BANKED;
        .globl b_scroll_up
        b_scroll_up = 255

_scroll_up::
        ; Initialize parameters.
        ldhl    SP, #9
        ld      A, (HL-)        ; A = height.
        or      A
        ret     Z               ; Return if height is 0.

        ld      D, A            ; D = height.
        ld      A, (HL-)
        ld      E, A            ; E = width.
        ld      A, (HL-)
        ld      L, (HL)
        ld      H, A            ; HL = base address.

        ; Scroll and fill.
        push    BC

        dec     D               ; D = height - 1.
        jr      Z, setlast$     ; If height is 1, skip the copy loop.

2$:
        ; Iterate all lines to scroll.
        ld      B, H
        ld      C, L            ; BC = the start address of the current line.

        ld      A, #0x20        ; 32 tiles per line.
        add     L               ; L += 32.
        ld      L, A
        adc     H               ; H += carry.
        sub     L               ; Clear carry.
        ld      H, A            ; HL = the start address of the next line.

        ; Copy one line.
        push    HL
        push    DE
3$:
        WAIT_STAT
        ld      A, (HL+)        ; A = *HL++ (read source tile).
        ld      (BC), A         ; *BC = A (write to target).
        inc     BC              ; ++BC (next tile).
        dec     E               ; --width (count tiles).
        jr      NZ, 3$          ; Repeat until width is 0.

        pop     DE
        pop     HL

        dec     D               ; --height (count lines).
        jr      NZ, 2$          ; Repeat until height is 0.

setlast$:
        ; Prepare to fill in the bottom line.
        push    HL              ; Save the start address of the bottom line.
        ldhl    SP, #14
        ld      D, (HL)         ; D = data.
        pop     HL              ; Restore the start address of the bottom line.

1$:
        ; Fill in the bottom line.
        WAIT_STAT
        ld      A, D            ; A = data.
        ld      (HL+), A        ; *HL++ = A (write to target).
        dec     E               ; --width (count tiles).
        jr      NZ, 1$          ; Repeat until width is 0.

        ; Return.
        pop     BC
        ret

        ; void scroll_down(UINT8 * base, UINT8 w, UINT8 h, UINT8 data) BANKED;
        .globl b_scroll_down
        b_scroll_down = 255

_scroll_down::
        ; Initialize parameters.
        ldhl    SP, #9
        ld      A, (HL-)        ; A = height.
        or      A
        ret     Z               ; Return if height is 0.

        ld      D, A            ; D = height.
        ld      A, (HL-)
        ld      E, A            ; E = width.
        ld      A, (HL-)
        ld      L, (HL)
        ld      H, A            ; HL = base address.

        ; Scroll and fill.
        push    BC

        dec     D               ; D = height - 1.
        jr      Z, setlast$     ; If height is 1, skip the copy loop.

        ; Calculate the address of the bottom line: base + (height - 1) * 32.
        push    DE              ; Save the height/width.
        push    HL              ; Save the base address.
        ld      A, D            ; A = height.
        ld      L, A            ; HL = height.
        ld      H, #0
        add     HL, HL          ; HL = height * 2.
        add     HL, HL          ; HL = height * 4.
        add     HL, HL          ; HL = height * 8.
        add     HL, HL          ; HL = height * 16.
        add     HL, HL          ; HL = height * 32.
        pop     DE              ; DE = base address.
        add     HL, DE          ; HL = address of the bottom line.
        pop     DE              ; DE = height/width.

2$:
        ; Iterate all lines to scroll.
        ld      B, H
        ld      C, L            ; BC = the start address of the current line.

        push    DE              ; Save height/width.
        ld      D, #0x20        ; 32 tiles per line.
        ld      A, L
        sub     D               ; L -= 32.
        ld      L, A
        ld      A, H
        sbc     #0              ; H -= carry.
        ld      H, A            ; HL = the start address of the next line.
        pop     DE              ; DE = height/width.

        ; Copy one line.
        push    HL
        push    DE
3$:
        WAIT_STAT
        ld      A, (HL+)        ; A = *HL++ (read source tile).
        ld      (BC), A         ; *BC = A (write to target).
        inc     BC              ; ++BC (next tile).
        dec     E               ; --width (count tiles).
        jr      NZ, 3$          ; Repeat until width is 0.

        pop     DE
        pop     HL

        dec     D               ; --height (count lines).
        jr      NZ, 2$          ; Repeat until height is 0.

        jp      setlast$
