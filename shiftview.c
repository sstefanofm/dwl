/* stf's shiftwidth implementation */
void
shiftview(const Arg *arg)
{
  Arg a;
  unsigned int tag = selmon->tagset[selmon->seltags];
  int current = 0;

  /* find first selected tag */
  while (!(tag & (1 << current)) && current < TAGCOUNT)
    ++current;

  if (current >= TAGCOUNT)
    return;

  current = (current + arg->i + TAGCOUNT) % TAGCOUNT;

  a.ui = 1 << current;
  view(&a);
}


// "arg->i" stores the number of tags to shift right (positive value)
//          or left (negative value)
void
shiftview_only_sel(const Arg *arg)
{
  Arg a;
  Client *c;
  bool visible = false;
  int i = arg->i;
  int count = 0;
  int nextseltags, curseltags = selmon->tagset[selmon->seltags];

  do {
    if (i > 0) // left circular shift
      nextseltags = (curseltags << i) | (curseltags >> (TAGCOUNT - i));
    else // right circular shift
      nextseltags = curseltags >> (-i) | (curseltags << (TAGCOUNT + i));

    // Check if the tag is visible
    wl_list_for_each(c, &clients, link) {
      if (c->mon == selmon && nextseltags & c->tags) {
        visible = true;
        break;
      }
    }

    i += arg->i;
  } while (!visible && ++count <= TAGCOUNT);

  if (count <= TAGCOUNT) {
    a.i = nextseltags;
    view(&a);
  }
}
