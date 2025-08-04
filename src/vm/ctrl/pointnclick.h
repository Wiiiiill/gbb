#ifndef __POINTNCLICK_H__
#define __POINTNCLICK_H__

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "../vm.h"
#include "../vm_actor.h"

BOOLEAN controller_behave_pointnclick_player(actor_t * actor, UINT8 pointing) BANKED;

#endif /* __POINTNCLICK_H__ */
