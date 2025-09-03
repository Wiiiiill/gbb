#ifndef __TOPDOWN_H__
#define __TOPDOWN_H__

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "../vm.h"
#include "../vm_actor.h"

enum TopDownBodyTypes {
    REGULAR,
    RIGID
};

BOOLEAN controller_behave_topdown_player(actor_t * actor) BANKED;
BOOLEAN controller_behave_topdown_player_arbitrary(actor_t * actor) BANKED;

BOOLEAN controller_behave_topdown_move(actor_t * actor, enum TopDownBodyTypes body_type) BANKED;
BOOLEAN controller_behave_topdown_move_arbitrary(actor_t * actor, enum TopDownBodyTypes body_type) BANKED;

BOOLEAN controller_behave_topdown_idle(actor_t * actor) BANKED;

#endif /* __TOPDOWN_H__ */
