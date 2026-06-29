/* stf's custom
 * 
 * write current keyboard layout to a /tmp file */

#pragma once

#include <xkbcommon/xkbcommon.h>

void wkblayout(struct xkb_state *state, struct xkb_keymap *keymap);
