/* stf's custom
 * 
 * write current keyboard layout to a /tmp file */

#include "wkblayout.h"

#include <stdio.h>
#include <string.h>

char *
layoutcode(const char *name)
{
  if (strcmp(name, "English (US)") == 0)
    return "us";
  if (strcmp(name, "Spanish") == 0)
    return "es";

  return name;
}

void
wkblayout(struct xkb_state *state, struct xkb_keymap *keymap)
{
  xkb_layout_index_t layout = xkb_state_serialize_layout(
    state,
    XKB_STATE_LAYOUT_EFFECTIVE
  );

  const char *name = xkb_keymap_layout_get_name(
    keymap,
    layout
  );

  FILE *fp = fopen("/tmp/dwl-kb-layout", "w");

  if (!fp)
    return;

  fprintf(fp, "%s", layoutcode(name));
  fclose(fp);
}
