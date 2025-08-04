#ifndef __CONTROLLING_H__
#define __CONTROLLING_H__

#if defined __SDCC
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#include "../utils/utils.h"

#include "../vm.h"
#include "../vm_actor.h"
#include "../vm_scene.h"

#define CONTROLLER_BLOCKING_ENDPOINT_NONE    0
#define CONTROLLER_BLOCKING_ENDPOINT_START   1
#define CONTROLLER_BLOCKING_ENDPOINT_END     2

INLINE UINT8 controller_get_blocking_up(actor_t * actor, INT16 dy) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 x0          = DIV8(pos_x + actor->bounds.left);
    const UINT8 x1    = DIV8(pos_x + actor->bounds.right) + 1;
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.top);
    while (x0 != x1) {
        const UINT8 prop = scene_get_prop(x0, y);
        if (prop & SCENE_PROPERTY_BLOCKING_UP) {
            return prop;
        }

        ++x0;
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_blocking_down(actor_t * actor, INT16 dy) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 x0          = DIV8(pos_x + actor->bounds.left);
    const UINT8 x1    = DIV8(pos_x + actor->bounds.right) + 1;
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.bottom);
    while (x0 != x1) {
        const UINT8 prop = scene_get_prop(x0, y);
        if (prop & SCENE_PROPERTY_BLOCKING_DOWN) {
            return prop;
        }

        ++x0;
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_blocking_left(actor_t * actor, INT16 dx) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const INT16 new_x = pos_x + dx;
    const UINT8 x     = DIV8(new_x + actor->bounds.left);
    UINT8 y0          = DIV8(pos_y + actor->bounds.top);
    const UINT8 y1    = DIV8(pos_y + actor->bounds.bottom) + 1;
    while (y0 != y1) {
        const UINT8 prop = scene_get_prop(x, y0);
        if (prop & SCENE_PROPERTY_BLOCKING_LEFT) {
            return prop;
        }

        ++y0;
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_blocking_right(actor_t * actor, INT16 dx) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const INT16 new_x = pos_x + dx;
    const UINT8 x     = DIV8(new_x + actor->bounds.right);
    UINT8 y0          = DIV8(pos_y + actor->bounds.top);
    const UINT8 y1    = DIV8(pos_y + actor->bounds.bottom) + 1;
    while (y0 != y1) {
        const UINT8 prop = scene_get_prop(x, y0);
        if (prop & SCENE_PROPERTY_BLOCKING_RIGHT) {
            return prop;
        }

        ++y0;
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}

INLINE UINT8 controller_get_blocking_up_endpoint(actor_t * actor, INT16 dy) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 x0          = DIV8(pos_x + actor->bounds.left);
    const UINT8 x1    = DIV8(pos_x + actor->bounds.right) + 1;
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.top);
    while (x0 != x1) {
        if (scene_get_prop(x0, y) & SCENE_PROPERTY_BLOCKING_UP) {
            if (x0 + 1 == x1)
                return CONTROLLER_BLOCKING_ENDPOINT_END;

            return CONTROLLER_BLOCKING_ENDPOINT_START;
        }

        ++x0;
    }

    return CONTROLLER_BLOCKING_ENDPOINT_NONE;
}
INLINE UINT8 controller_get_blocking_down_endpoint(actor_t * actor, INT16 dy) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 x0          = DIV8(pos_x + actor->bounds.left);
    const UINT8 x1    = DIV8(pos_x + actor->bounds.right) + 1;
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.bottom);
    while (x0 != x1) {
        if (scene_get_prop(x0, y) & SCENE_PROPERTY_BLOCKING_DOWN) {
            if (x0 + 1 == x1)
                return CONTROLLER_BLOCKING_ENDPOINT_END;

            return CONTROLLER_BLOCKING_ENDPOINT_START;
        }

        ++x0;
    }

    return CONTROLLER_BLOCKING_ENDPOINT_NONE;
}
INLINE UINT8 controller_get_blocking_left_endpoint(actor_t * actor, INT16 dx) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const INT16 new_x = pos_x + dx;
    const UINT8 x     = DIV8(new_x + actor->bounds.left);
    UINT8 y0          = DIV8(pos_y + actor->bounds.top);
    const UINT8 y1    = DIV8(pos_y + actor->bounds.bottom) + 1;
    while (y0 != y1) {
        if (scene_get_prop(x, y0) & SCENE_PROPERTY_BLOCKING_LEFT) {
            if (y0 + 1 == y1)
                return CONTROLLER_BLOCKING_ENDPOINT_END;

            return CONTROLLER_BLOCKING_ENDPOINT_START;
        }

        ++y0;
    }

    return CONTROLLER_BLOCKING_ENDPOINT_NONE;
}
INLINE UINT8 controller_get_blocking_right_endpoint(actor_t * actor, INT16 dx) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const INT16 new_x = pos_x + dx;
    const UINT8 x     = DIV8(new_x + actor->bounds.right);
    UINT8 y0          = DIV8(pos_y + actor->bounds.top);
    const UINT8 y1    = DIV8(pos_y + actor->bounds.bottom) + 1;
    while (y0 != y1) {
        if (scene_get_prop(x, y0) & SCENE_PROPERTY_BLOCKING_RIGHT) {
            if (y0 + 1 == y1)
                return CONTROLLER_BLOCKING_ENDPOINT_END;

            return CONTROLLER_BLOCKING_ENDPOINT_START;
        }

        ++y0;
    }

    return CONTROLLER_BLOCKING_ENDPOINT_NONE;
}

INLINE UINT8 controller_get_blocking_up_pos(actor_t * actor, INT16 dy, UINT16 * out_y) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 x0          = DIV8(pos_x + actor->bounds.left);
    const UINT8 x1    = DIV8(pos_x + actor->bounds.right) + 1;
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.top);
    while (x0 != x1) {
        const UINT8 prop = scene_get_prop(x0, y);
        if (prop & SCENE_PROPERTY_BLOCKING_UP) {
            *out_y = (MUL8(y + 1) - actor->bounds.top);

            return prop;
        }

        ++x0;
    }
    *out_y = new_y;

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_blocking_down_pos(actor_t * actor, INT16 dy, UINT16 * out_y) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 x0          = DIV8(pos_x + actor->bounds.left);
    const UINT8 x1    = DIV8(pos_x + actor->bounds.right) + 1;
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.bottom);
    while (x0 != x1) {
        const UINT8 prop = scene_get_prop(x0, y);
        if (prop & SCENE_PROPERTY_BLOCKING_DOWN) {
            *out_y = (MUL8(y) - actor->bounds.bottom) - 1;

            return prop;
        }

        ++x0;
    }
    *out_y = new_y;

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_blocking_fall_pos(actor_t * actor, INT16 dy, UINT16 * out_y) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 x0          = DIV8(pos_x + actor->bounds.left);
    const UINT8 x1    = DIV8(pos_x + actor->bounds.right) + 1;
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.bottom);
    while (x0 != x1) {
        const UINT8 prop = scene_get_prop(x0, y);
        if ((prop & SCENE_PROPERTY_BLOCKING_DOWN) && (y > DIV8(pos_y + actor->bounds.bottom))) {
            *out_y = (MUL8(y) - actor->bounds.bottom) - 1;

            return prop;
        }

        ++x0;
    }
    *out_y = new_y;

    return SCENE_PROPERTY_EMPTY_GRID;
}

INLINE UINT8 controller_find_ladder_up(actor_t * actor, UINT8 actor_half_width, UINT16 * out_x) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const UINT8 x_mid = DIV8(pos_x + actor->bounds.left + actor_half_width);
    const UINT8 y     = DIV8(pos_y + actor->bounds.bottom);
    const UINT8 ldr   = scene_get_prop(x_mid, y) & SCENE_PROPERTY_LADDER;
    if (ldr) {
        *out_x = MUL8(x_mid) + 3 - (actor->bounds.left + actor_half_width);

        return ldr;
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_find_ladder_down(actor_t * actor, UINT8 actor_half_width, UINT16 * out_x) {
    const INT16 pos_x = TO_SCREEN(actor->position.x);
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const UINT8 x_mid = DIV8(pos_x + actor->bounds.left + actor_half_width);
    const UINT8 y     = DIV8(pos_y + actor->bounds.bottom) + 1;
    const UINT8 ldr   = scene_get_prop(x_mid, y) & SCENE_PROPERTY_LADDER;
    if (ldr) {
        *out_x = MUL8(x_mid) + 3 - (actor->bounds.left + actor_half_width);

        return ldr;
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_ladder_up(actor_t * actor, UINT8 x_mid) {
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const INT16 y     = DIV8(pos_y + actor->bounds.bottom);
    const UINT8 prop  = scene_get_prop(x_mid, y);
    const UINT8 ldr   = prop & SCENE_PROPERTY_LADDER;
    if (ldr) {
        if (!(prop & SCENE_PROPERTY_BLOCKING_UP)) {
            return ldr;
        }
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_ladder_down(actor_t * actor, UINT8 x_mid) {
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const INT16 y     = DIV8(pos_y + actor->bounds.bottom + 1);
    const UINT8 prop  = scene_get_prop(x_mid, y);
    const UINT8 ldr   = prop & SCENE_PROPERTY_LADDER;
    if (ldr) {
        if (!(prop & SCENE_PROPERTY_BLOCKING_DOWN)) {
            return ldr;
        }
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_ladder_blocking_left(actor_t * actor, UINT8 x_mid) {
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 y0          = DIV8(pos_y + actor->bounds.top);
    const UINT8 y1    = DIV8(pos_y + actor->bounds.bottom) + 1;
    while (y0 != y1) {
        const UINT8 prop = scene_get_prop(x_mid - 1, y0);
        if (prop & SCENE_PROPERTY_BLOCKING_LEFT) {
            return prop;
        }

        ++y0;
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_ladder_blocking_right(actor_t * actor, UINT8 x_mid) {
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    UINT8 y0          = DIV8(pos_y + actor->bounds.top);
    const UINT8 y1    = DIV8(pos_y + actor->bounds.bottom) + 1;
    while (y0 != y1) {
        const UINT8 prop = scene_get_prop(x_mid + 1, y0);
        if (prop & SCENE_PROPERTY_BLOCKING_RIGHT) {
            return prop;
        }

        ++y0;
    }

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_ladder_blocking_up_pos(actor_t * actor, UINT8 x_mid, INT16 dy, UINT16 * out_y) {
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.top);
    const UINT8 prop  = scene_get_prop(x_mid, y);
    if (prop & SCENE_PROPERTY_BLOCKING_UP) {
        *out_y = (MUL8(y + 1) - actor->bounds.top);

        return prop;
    }
    *out_y = new_y;

    return SCENE_PROPERTY_EMPTY_GRID;
}
INLINE UINT8 controller_get_ladder_blocking_down_pos(actor_t * actor, UINT8 x_mid, INT16 dy, UINT16 * out_y) {
    const INT16 pos_y = TO_SCREEN(actor->position.y);
    const INT16 new_y = pos_y + dy;
    const UINT8 y     = DIV8(new_y + actor->bounds.bottom);
    const UINT8 prop  = scene_get_prop(x_mid, y);
    if (prop & SCENE_PROPERTY_BLOCKING_DOWN) {
        *out_y = (MUL8(y) - actor->bounds.bottom) - 1;

        return prop;
    }
    *out_y = new_y;

    return SCENE_PROPERTY_EMPTY_GRID;
}

#endif /* __CONTROLLING_H__ */
