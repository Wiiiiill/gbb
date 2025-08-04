#ifndef __VM_GRAPHICS_H__
#define __VM_GRAPHICS_H__

#include "vm.h"

BANKREF_EXTERN(VM_GRAPHICS)

#define GRAPHICS_LAYER_MAP      0
#define GRAPHICS_LAYER_WINDOW   1
#define GRAPHICS_LAYER_SPRITE   2

extern INT16 graphics_map_x;
extern INT16 graphics_map_y;

void graphics_init(void) BANKED;

void graphics_put_map(void) BANKED;

void vm_color(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_palette(SCRIPT_CTX * THIS, UINT8 nsargs) OLDCALL BANKED;
void vm_rgb(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_plot(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_point(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_line(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_rect(SCRIPT_CTX * THIS, BOOLEAN fill) OLDCALL BANKED;
void vm_gotoxy(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_text(SCRIPT_CTX * THIS, BOOLEAN new_line, UINT8 nargs) OLDCALL BANKED;

void vm_image(SCRIPT_CTX * THIS, UINT8 src) OLDCALL BANKED;

void vm_fill_tile(SCRIPT_CTX * THIS, UINT8 src, UINT8 layer) OLDCALL BANKED;

void vm_def_map(SCRIPT_CTX * THIS, UINT8 src) OLDCALL BANKED;
void vm_map(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_mget(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_mset(SCRIPT_CTX * THIS) OLDCALL BANKED;

void vm_def_window(SCRIPT_CTX * THIS, UINT8 src) OLDCALL BANKED;
void vm_window(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_wget(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_wset(SCRIPT_CTX * THIS) OLDCALL BANKED;

void vm_def_sprite(SCRIPT_CTX * THIS, UINT8 src) OLDCALL BANKED;
void vm_sprite(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_sget(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_sset(SCRIPT_CTX * THIS) OLDCALL BANKED;
void vm_get_sprite_prop(SCRIPT_CTX * THIS) OLDCALL BANKED; // Get sprite property.
void vm_set_sprite_prop(SCRIPT_CTX * THIS) OLDCALL BANKED; // Set sprite property.

#endif /* __VM_GRAPHICS_H__ */
