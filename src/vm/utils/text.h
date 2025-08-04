#ifndef __TEXT_H__
#define __TEXT_H__

#include "../vm.h"

#define TEXT_PRINT_MODE_NONE       0
#define TEXT_PRINT_MODE_TEXT       1
#define TEXT_PRINT_MODE_GRAPHICS   2
#define TEXT_PRINT_MODE_SHELL      3

UINT8 int16_to_str(INT16 n, unsigned char * s) BANKED;
UINT8 uint16_to_hex(UINT16 n, unsigned char * s) BANKED;
UINT8 uint16_to_hex_full(UINT16 n, unsigned char * s) BANKED;
void print_banked(unsigned char * begin, unsigned char * end, BOOLEAN new_line, UINT8 mode) BANKED;

void print(SCRIPT_CTX * THIS, BOOLEAN new_line, UINT8 nargs, UINT8 mode) NONBANKED;

#endif /* __TEXT_H__ */
