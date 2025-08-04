#ifndef __PLATFORMER_H__
#define __PLATFORMER_H__

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "../vm.h"
#include "../vm_actor.h"

BOOLEAN controller_behave_platformer_player(actor_t * actor) BANKED;

BOOLEAN controller_behave_platformer_move(actor_t * actor) BANKED;

BOOLEAN controller_behave_platformer_idle(actor_t * actor) BANKED;

#endif /* __PLATFORMER_H__ */
