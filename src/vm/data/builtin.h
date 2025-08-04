#ifndef __BUILTIN_H__
#define __BUILTIN_H__

#if defined __SDCC
#   include <gbdk/platform.h>
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

BANKREF_EXTERN(BUILTIN)

/**< Header. */

// Version.

extern const unsigned char VERSION;

#endif /* __BUILTIN_H__ */
