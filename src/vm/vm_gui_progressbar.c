#pragma bank 255

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "utils/utils.h"

#include "vm_device.h"
#include "vm_graphics.h"
#include "vm_gui.h"

BANKREF(VM_GUI_PROGRESSBAR)

static const UINT8 GUI_BLIT_INC_LEFT_PACK_MASKS[64] = {
    0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11111000, 0b11111100, 0b11111110, 0b11111111,
    0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11111000, 0b11111100, 0b11111110, 0b11111101,
    0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11111000, 0b11111100, 0b11111010, 0b11111001,
    0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11111000, 0b11110100, 0b11110010, 0b11110001,
    0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11101000, 0b11100100, 0b11100010, 0b11100001,
    0b10000000, 0b11000000, 0b11100000, 0b11010000, 0b11001000, 0b11000100, 0b11000010, 0b11000001,
    0b10000000, 0b11000000, 0b10100000, 0b10010000, 0b10001000, 0b10000100, 0b10000010, 0b10000001,
    0b10000000, 0b10000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001
};
static const UINT8 GUI_BLIT_INC_RIGHT_PACK_MASKS[64] = {
    0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111,
    0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111110,
    0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111110, 0b11111100,
    0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111110, 0b01111100, 0b11111000,
    0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011110, 0b00111100, 0b01111000, 0b11110000,
    0b00000001, 0b00000011, 0b00000111, 0b00001110, 0b00011100, 0b00111000, 0b01110000, 0b11100000,
    0b00000001, 0b00000011, 0b00000110, 0b00001100, 0b00011000, 0b00110000, 0b01100000, 0b11000000,
    0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000
};
#define GUI_BLIT_LEFT_PICK_MASKS    GUI_BLIT_INC_LEFT_PACK_MASKS  // Only takes the first 8 elements.
#define GUI_BLIT_RIGHT_PICK_MASKS   GUI_BLIT_INC_RIGHT_PACK_MASKS // Only takes the first 8 elements.

INLINE void gui_blit_progressbar_head(UINT8 val) {
    const UINT8 base = gui_base_tile;
    UINT8 * const base_addr = VRAM_BASE_TILE_ADDRESS(base);
    UINT8 * addr;
    UINT8 bits;
    const UINT8 p0 = GUI_PALETTE_FIRST(gui_progressbar_blit_palettes);
    const UINT8 p1 = GUI_PALETTE_SECOND(gui_progressbar_blit_palettes);

    const UINT8 margin_x = GUI_MARGIN_X(gui_margin);
    const UINT8 margin_y = GUI_MARGIN_Y(gui_margin);

    bits = GUI_BLIT_RIGHT_PICK_MASKS[7 - margin_x];
    addr = base_addr + MUL2(margin_y); // Left-top border.
    if (p0 & 0x02) set_vram_byte(addr,     bits);
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    addr = base_addr + MUL2(7 - margin_y); // Left-bottom border.
    if (p0 & 0x02) set_vram_byte(addr,     bits);
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    bits = GUI_BLIT_INC_RIGHT_PACK_MASKS[MUL8(7 - val) + (7 - margin_x)];

    const UINT8 edge = 0x80 >> margin_x;

    UINT8 bits0 = (p1 & 0x02) ? bits : 0x00;
    if (p0 & 0x02) bits0 |= edge; else bits0 &= ~edge;

    UINT8 bits1 = (p1 & 0x01) ? bits : 0x00;
    if (p0 & 0x01) bits1 |= edge; else bits1 &= ~edge;

    for (UINT8 by = margin_y + 1; by != 7 - margin_y; ++by) {
        addr = base_addr + MUL2(by);
        set_vram_byte(addr,     bits0); // Left content.
        set_vram_byte(addr + 1, bits1);
    }
}

INLINE void gui_blit_progressbar_body(UINT8 val) {
    const UINT8 base = gui_base_tile + 2;
    UINT8 * const base_addr = VRAM_BASE_TILE_ADDRESS(base);
    UINT8 * addr;
    UINT8 bits = 0b11111111;
    const UINT8 p0 = GUI_PALETTE_FIRST(gui_progressbar_blit_palettes);
    const UINT8 p1 = GUI_PALETTE_SECOND(gui_progressbar_blit_palettes);

    const UINT8 margin_y = GUI_MARGIN_Y(gui_margin);

    addr = base_addr + MUL2(margin_y);
    if (p0 & 0x02) set_vram_byte(addr,     bits); // Top border.
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    addr = base_addr + MUL2(7 - margin_y);
    if (p0 & 0x02) set_vram_byte(addr,     bits); // Bottom border.
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    bits = val == 0 ? 0b00000000 : GUI_BLIT_LEFT_PICK_MASKS[val - 1];
    for (UINT8 by = margin_y + 1; by != 7 - margin_y; ++by) {
        addr = base_addr + MUL2(by);
        if (p1 & 0x02) set_vram_byte(addr,     bits); // Center content.
        if (p1 & 0x01) set_vram_byte(addr + 1, bits);
    }
}

INLINE void gui_blit_progressbar_tail(UINT8 val) {
    const UINT8 base = gui_base_tile + 4;
    UINT8 * const base_addr = VRAM_BASE_TILE_ADDRESS(base);
    UINT8 * addr;
    UINT8 bits;
    const UINT8 p0 = GUI_PALETTE_FIRST(gui_progressbar_blit_palettes);
    const UINT8 p1 = GUI_PALETTE_SECOND(gui_progressbar_blit_palettes);

    const UINT8 margin_x = GUI_MARGIN_X(gui_margin);
    const UINT8 margin_y = GUI_MARGIN_Y(gui_margin);

    bits = GUI_BLIT_LEFT_PICK_MASKS[7 - margin_x];
    addr = base_addr + MUL2(margin_y);
    if (p0 & 0x02) set_vram_byte(addr,     bits); // Right-top border.
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    addr = base_addr + MUL2(7 - margin_y);
    if (p0 & 0x02) set_vram_byte(addr,     bits); // Right-bottom border.
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    bits = GUI_BLIT_INC_LEFT_PACK_MASKS[MUL8(7 - val) + (7 - margin_x)];

    const UINT8 edge = 0x01 << margin_x;

    UINT8 bits0 = (p1 & 0x02) ? bits : 0x00;
    if (p0 & 0x02) bits0 |= edge; else bits0 &= ~edge;

    UINT8 bits1 = (p1 & 0x01) ? bits : 0x00;
    if (p0 & 0x01) bits1 |= edge; else bits1 &= ~edge;

    for (UINT8 by = margin_y + 1; by != 7 - margin_y; ++by) {
        addr = base_addr + MUL2(by);
        set_vram_byte(addr,     bits0); // Right content.
        set_vram_byte(addr + 1, bits1);
    }
}

void gui_blit_progressbar_head_body_tail(UINT8 val0, UINT8 val1, UINT8 val2) BANKED {
    gui_blit_progressbar_head(val0);
    gui_blit_progressbar_body(val1);
    gui_blit_progressbar_tail(val2);
}

void gui_blit_progressbar_body_full(void) BANKED {
    const UINT8 base = gui_base_tile + 1;
    UINT8 * const base_addr = VRAM_BASE_TILE_ADDRESS(base);
    UINT8 * addr;
    UINT8 bits = 0b11111111;
    const UINT8 p0 = GUI_PALETTE_FIRST(gui_progressbar_blit_palettes);
    const UINT8 p1 = GUI_PALETTE_SECOND(gui_progressbar_blit_palettes);

    const UINT8 margin_y = GUI_MARGIN_Y(gui_margin);

    addr = base_addr + MUL2(margin_y);
    if (p0 & 0x02) set_vram_byte(addr,     bits); // Top border.
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    addr = base_addr + MUL2(7 - margin_y);
    if (p0 & 0x02) set_vram_byte(addr,     bits); // Bottom border.
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    for (UINT8 by = margin_y + 1; by != 7 - margin_y; ++by) {
        addr = base_addr + MUL2(by);
        if (p1 & 0x02) set_vram_byte(addr,     bits); // Center content.
        if (p1 & 0x01) set_vram_byte(addr + 1, bits);
    }
}

void gui_blit_progressbar_body_empty(void) BANKED {
    const UINT8 base = gui_base_tile + 3;
    UINT8 * const base_addr = VRAM_BASE_TILE_ADDRESS(base);
    UINT8 * addr;
    UINT8 bits = 0b11111111;
    const UINT8 p0 = GUI_PALETTE_FIRST(gui_progressbar_blit_palettes);
    const UINT8 p1 = GUI_PALETTE_SECOND(gui_progressbar_blit_palettes);

    const UINT8 margin_y = GUI_MARGIN_Y(gui_margin);

    addr = base_addr + MUL2(margin_y);
    if (p0 & 0x02) set_vram_byte(addr,     bits); // Top border.
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    addr = base_addr + MUL2(7 - margin_y);
    if (p0 & 0x02) set_vram_byte(addr,     bits); // Bottom border.
    if (p0 & 0x01) set_vram_byte(addr + 1, bits);

    bits = 0b00000000;
    for (UINT8 by = margin_y + 1; by != 7 - margin_y; ++by) {
        addr = base_addr + MUL2(by);
        if (p1 & 0x02) set_vram_byte(addr,     bits); // Center content.
        if (p1 & 0x01) set_vram_byte(addr + 1, bits);
    }
}

void vm_progressbar(SCRIPT_CTX * THIS, UINT8 nargs) OLDCALL BANKED {
    UINT16 val                        = (UINT16)*(--THIS->stack_ptr);
    UINT8 layer;
    if (nargs == 10) {
        const UINT8 type              = GUI_WIDGET_TYPE_PROGRESSBAR;
        gui_cursor_x                  = (UINT8)*(--THIS->stack_ptr);
        gui_cursor_y                  = (UINT8)*(--THIS->stack_ptr);
        gui_width                     = (UINT8)*(--THIS->stack_ptr);
        gui_height                    = 1;
        gui_base_tile                 = (UINT8)*(--THIS->stack_ptr);
        layer                         = (UINT8)*(--THIS->stack_ptr);
        UINT8 margin_x                = (UINT8)*(--THIS->stack_ptr);
        UINT8 margin_y                = (UINT8)*(--THIS->stack_ptr);
        const UINT8 palette_b         = (UINT8)*(--THIS->stack_ptr);
        const UINT8 palette_c         = (UINT8)*(--THIS->stack_ptr);
        gui_widget_category           = GUI_CATEGORY(type, layer);
        gui_width                     = MAX(gui_width, 3);
        margin_x                      = MIN(margin_x, 7);
        margin_y                      = MIN(margin_y, 3);
        gui_margin                    = GUI_MARGIN(margin_x, margin_y);
        gui_progressbar_blit_palettes = GUI_PALETTE(palette_b, palette_c);

        gui_clear(gui_base_tile, GUI_PROGRESSBAR_TILE_COUNT); // Takes `GUI_PROGRESSBAR_TILE_COUNT` tiles.

        if (layer == GRAPHICS_LAYER_WINDOW) {
            set_win_tile_xy(gui_cursor_x,                 gui_cursor_y, gui_base_tile);
            set_win_tile_xy(gui_cursor_x + gui_width - 1, gui_cursor_y, gui_base_tile + 4);
            for (UINT8 i = 1; i != gui_width - 1; ++i) {
                set_win_tile_xy(gui_cursor_x + i,         gui_cursor_y, gui_base_tile + 2);
            }
        } else /* if (layer == GRAPHICS_LAYER_MAP) */ {
            set_bkg_tile_xy(gui_cursor_x,                 gui_cursor_y, gui_base_tile);
            set_bkg_tile_xy(gui_cursor_x + gui_width - 1, gui_cursor_y, gui_base_tile + 4);
            for (UINT8 i = 1; i != gui_width - 1; ++i) {
                set_bkg_tile_xy(gui_cursor_x + i,         gui_cursor_y, gui_base_tile + 2);
            }
        }
    } else {
        layer = GUI_CATEGORY_LAYER(gui_widget_category);
    }

    val = MIN(val, 128);
    const UINT8 width = MUL8(gui_width) - MUL2(gui_cursor_x) - 2;
    val = MUL2(val);
    val = DIV128(val * width);
    val = DIV2(val);

    const UINT8 p = val;
    const UINT8 q = p - MIN(7 - gui_cursor_x, p);
    const UINT8 m = DIV8(q);
    const UINT8 n = MOD8(q);
    gui_blit_progressbar_head_body_tail(
        MIN(p, 7),
        n,
        MAX(7 - (width - p), 0)
    );

    if (layer == GRAPHICS_LAYER_WINDOW) {
        for (UINT8 i = 1; i != gui_width - 1; ++i) {
            UINT8 t;
            if         (i < m + 1)    t = 1;
            else if    (i == m + 1)   t = 2;
            else /* if (i > m + 1) */ t = 3;
            set_win_tile_xy(gui_cursor_x + i, gui_cursor_y, gui_base_tile + t);
        }
    } else /* if (layer == GRAPHICS_LAYER_MAP) */ {
        for (UINT8 i = 1; i != gui_width - 1; ++i) {
            UINT8 t;
            if         (i < m + 1)    t = 1;
            else if    (i == m + 1)   t = 2;
            else /* if (i > m + 1) */ t = 3;
            set_bkg_tile_xy(gui_cursor_x + i, gui_cursor_y, gui_base_tile + t);
        }
    }
}
