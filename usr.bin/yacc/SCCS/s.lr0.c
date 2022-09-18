h29679
s 00214/00222/00397
d D 5.3 91/01/20 19:56:29 corbett 3 2
c I changed the formatting to make it more consistent with the rest of Berkeley Yacc.  -rpc
e
s 00001/00011/00618
d D 5.2 90/06/01 16:13:27 bostic 2 1
c new copyright notice
e
s 00629/00000/00000
d D 5.1 89/12/25 14:24:32 bostic 1 0
c date and time created 89/12/25 14:24:32 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Robert Paul Corbett.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "defs.h"

extern short *itemset;
extern short *itemsetend;
extern unsigned *ruleset;

int nstates;
core *first_state;
shifts *first_shift;
reductions *first_reduction;

int get_state();
core *new_state();

I 3
static core **state_set;
E 3
static core *this_state;
static core *last_state;
static shifts *last_shift;
static reductions *last_reduction;

static int nshifts;
static short *shift_symbol;

static short *redset;
static short *shiftset;

static short **kernel_base;
static short **kernel_end;
static short *kernel_items;

D 3
static core **state_table;
E 3

D 3

E 3
allocate_itemsets()
{
D 3
  register short *itemp;
  register short *item_end;
  register int symbol;
  register int i;
  register int count;
  register int max;
  register short *symbol_count;
E 3
I 3
    register short *itemp;
    register short *item_end;
    register int symbol;
    register int i;
    register int count;
    register int max;
    register short *symbol_count;
E 3

D 3
  count = 0;
  symbol_count = NEW2(nsyms, short);
E 3
I 3
    count = 0;
    symbol_count = NEW2(nsyms, short);
E 3

D 3
  item_end = ritem + nitems;
  for (itemp = ritem; itemp < item_end; itemp++)
E 3
I 3
    item_end = ritem + nitems;
    for (itemp = ritem; itemp < item_end; itemp++)
E 3
    {
D 3
      symbol = *itemp;
      if (symbol >= 0)
E 3
I 3
	symbol = *itemp;
	if (symbol >= 0)
E 3
	{
D 3
	  count++;
	  symbol_count[symbol]++;
E 3
I 3
	    count++;
	    symbol_count[symbol]++;
E 3
	}
    }

D 3
  kernel_base = NEW2(nsyms, short *);
  kernel_items = NEW2(count, short);
E 3
I 3
    kernel_base = NEW2(nsyms, short *);
    kernel_items = NEW2(count, short);
E 3

D 3
  count = 0;
  max = 0;
  for (i = 0; i < nsyms; i++)
E 3
I 3
    count = 0;
    max = 0;
    for (i = 0; i < nsyms; i++)
E 3
    {
D 3
      kernel_base[i] = kernel_items + count;
      count += symbol_count[i];
      if (max < symbol_count[i])
	max = symbol_count[i];
E 3
I 3
	kernel_base[i] = kernel_items + count;
	count += symbol_count[i];
	if (max < symbol_count[i])
	    max = symbol_count[i];
E 3
    }

D 3
  shift_symbol = symbol_count;
  kernel_end = NEW2(nsyms, short *);
E 3
I 3
    shift_symbol = symbol_count;
    kernel_end = NEW2(nsyms, short *);
E 3
}


D 3

E 3
allocate_storage()
{
D 3
  allocate_itemsets();

  shiftset = NEW2(nsyms, short);
  redset = NEW2(nrules + 1, short);
  state_table = NEW2(nitems, core *);
E 3
I 3
    allocate_itemsets();
    shiftset = NEW2(nsyms, short);
    redset = NEW2(nrules + 1, short);
    state_set = NEW2(nitems, core *);
E 3
}


D 3

E 3
append_states()
{
D 3
  register int i;
  register int j;
  register int symbol;
E 3
I 3
    register int i;
    register int j;
    register int symbol;
E 3

#ifdef	TRACE
D 3
  fprintf(stderr, "Entering append_states\n");
E 3
I 3
    fprintf(stderr, "Entering append_states()\n");
E 3
#endif
D 3

  for (i = 1; i < nshifts; i++)
E 3
I 3
    for (i = 1; i < nshifts; i++)
E 3
    {
D 3
      symbol = shift_symbol[i];
      j = i;
      while (j > 0 && shift_symbol[j - 1] > symbol)
E 3
I 3
	symbol = shift_symbol[i];
	j = i;
	while (j > 0 && shift_symbol[j - 1] > symbol)
E 3
	{
D 3
	  shift_symbol[j] = shift_symbol[j - 1];
	  j--;
E 3
I 3
	    shift_symbol[j] = shift_symbol[j - 1];
	    j--;
E 3
	}
D 3
      shift_symbol[j] = symbol;
E 3
I 3
	shift_symbol[j] = symbol;
E 3
    }

D 3
  for (i = 0; i < nshifts; i++)
E 3
I 3
    for (i = 0; i < nshifts; i++)
E 3
    {
D 3
      symbol = shift_symbol[i];
      shiftset[i] = get_state(symbol);
E 3
I 3
	symbol = shift_symbol[i];
	shiftset[i] = get_state(symbol);
E 3
    }
}


free_storage()
{
D 3
  FREE(shift_symbol);
  FREE(redset);
  FREE(shiftset);
  FREE(kernel_base);
  FREE(kernel_end);
  FREE(kernel_items);
  FREE(state_table);
E 3
I 3
    FREE(shift_symbol);
    FREE(redset);
    FREE(shiftset);
    FREE(kernel_base);
    FREE(kernel_end);
    FREE(kernel_items);
    FREE(state_set);
E 3
}



generate_states()
{
D 3
  allocate_storage();
  itemset = NEW2(nitems, short);
  ruleset = NEW2(WORDSIZE(nrules), unsigned);
  set_first_derives();
  initialize_states();
E 3
I 3
    allocate_storage();
    itemset = NEW2(nitems, short);
    ruleset = NEW2(WORDSIZE(nrules), unsigned);
    set_first_derives();
    initialize_states();
E 3

D 3
  while (this_state)
E 3
I 3
    while (this_state)
E 3
    {
D 3
      closure(this_state->items, this_state->nitems);
      save_reductions();
      new_itemsets();
      append_states();
E 3
I 3
	closure(this_state->items, this_state->nitems);
	save_reductions();
	new_itemsets();
	append_states();
E 3

D 3
      if (nshifts > 0)
        save_shifts();
E 3
I 3
	if (nshifts > 0)
	    save_shifts();
E 3

D 3
      this_state = this_state->next;
E 3
I 3
	this_state = this_state->next;
E 3
    }

D 3
  finalize_closure();
  free_storage();
E 3
I 3
    finalize_closure();
    free_storage();
E 3
}



int
get_state(symbol)
int symbol;
{
D 3
  register int key;
  register short *isp1;
  register short *isp2;
  register short *iend;
  register core *sp;
  register int found;
E 3
I 3
    register int key;
    register short *isp1;
    register short *isp2;
    register short *iend;
    register core *sp;
    register int found;
    register int n;
E 3

D 3
  int n;

E 3
#ifdef	TRACE
D 3
  fprintf(stderr, "Entering get_state, symbol = %d\n", symbol);
E 3
I 3
    fprintf(stderr, "Entering get_state(%d)\n", symbol);
E 3
#endif

D 3
  isp1 = kernel_base[symbol];
  iend = kernel_end[symbol];
  n = iend - isp1;
E 3
I 3
    isp1 = kernel_base[symbol];
    iend = kernel_end[symbol];
    n = iend - isp1;
E 3

D 3
  key = *isp1;
  assert(0 <= key && key < nitems);
  sp = state_table[key];
  if (sp)
E 3
I 3
    key = *isp1;
    assert(0 <= key && key < nitems);
    sp = state_set[key];
    if (sp)
E 3
    {
D 3
      found = 0;
      while (!found)
E 3
I 3
	found = 0;
	while (!found)
E 3
	{
D 3
	  if (sp->nitems == n)
E 3
I 3
	    if (sp->nitems == n)
E 3
	    {
D 3
	      found = 1;
	      isp1 = kernel_base[symbol];
	      isp2 = sp->items;
E 3
I 3
		found = 1;
		isp1 = kernel_base[symbol];
		isp2 = sp->items;
E 3

D 3
	      while (found && isp1 < iend)
E 3
I 3
		while (found && isp1 < iend)
E 3
		{
D 3
		  if (*isp1++ != *isp2++)
		    found = 0;
E 3
I 3
		    if (*isp1++ != *isp2++)
			found = 0;
E 3
		}
	    }

D 3
	  if (!found)
E 3
I 3
	    if (!found)
E 3
	    {
D 3
	      if (sp->link)
E 3
I 3
		if (sp->link)
E 3
		{
D 3
		  sp = sp->link;
E 3
I 3
		    sp = sp->link;
E 3
		}
D 3
	      else
E 3
I 3
		else
E 3
		{
D 3
		  sp = sp->link = new_state(symbol);
		  found = 1;
E 3
I 3
		    sp = sp->link = new_state(symbol);
		    found = 1;
E 3
		}
	    }
	}
    }
D 3
  else
E 3
I 3
    else
E 3
    {
D 3
      state_table[key] = sp = new_state(symbol);
E 3
I 3
	state_set[key] = sp = new_state(symbol);
E 3
    }

D 3
  return (sp->number);
E 3
I 3
    return (sp->number);
E 3
}



initialize_states()
{
    register int i;
    register short *start_derives;
    register core *p;

    start_derives = derives[start_symbol];
    for (i = 0; start_derives[i] >= 0; ++i)
	continue;

    p = (core *) MALLOC(sizeof(core) + i*sizeof(short));
    if (p == 0) no_space();

    p->next = 0;
    p->link = 0;
    p->number = 0;
    p->accessing_symbol = 0;
    p->nitems = i;

    for (i = 0;  start_derives[i] >= 0; ++i)
	p->items[i] = rrhs[start_derives[i]];

    first_state = last_state = this_state = p;
    nstates = 1;
}


new_itemsets()
{
D 3
  register int i;
  register int shiftcount;
  register short *isp;
  register short *ksp;
  register int symbol;
E 3
I 3
    register int i;
    register int shiftcount;
    register short *isp;
    register short *ksp;
    register int symbol;
E 3

D 3
  for (i = 0; i < nsyms; i++)
    kernel_end[i] = 0;
E 3
I 3
    for (i = 0; i < nsyms; i++)
	kernel_end[i] = 0;
E 3

D 3
  shiftcount = 0;
  isp = itemset;
  while (isp < itemsetend)
E 3
I 3
    shiftcount = 0;
    isp = itemset;
    while (isp < itemsetend)
E 3
    {
D 3
      i = *isp++;
      symbol = ritem[i];
      if (symbol > 0)
E 3
I 3
	i = *isp++;
	symbol = ritem[i];
	if (symbol > 0)
E 3
	{
D 3
          ksp = kernel_end[symbol];

          if (!ksp)
E 3
I 3
	    ksp = kernel_end[symbol];
	    if (!ksp)
E 3
	    {
D 3
	      shift_symbol[shiftcount++] = symbol;
	      ksp = kernel_base[symbol];
E 3
I 3
		shift_symbol[shiftcount++] = symbol;
		ksp = kernel_base[symbol];
E 3
	    }

D 3
          *ksp++ = i + 1;
          kernel_end[symbol] = ksp;
E 3
I 3
	    *ksp++ = i + 1;
	    kernel_end[symbol] = ksp;
E 3
	}
    }

D 3
  nshifts = shiftcount;
E 3
I 3
    nshifts = shiftcount;
E 3
}



core *
new_state(symbol)
int symbol;
{
D 3
  register int n;
  register core *p;
  register short *isp1;
  register short *isp2;
  register short *iend;
E 3
I 3
    register int n;
    register core *p;
    register short *isp1;
    register short *isp2;
    register short *iend;
E 3

#ifdef	TRACE
D 3
  fprintf(stderr, "Entering new_state, symbol = %d\n", symbol);
E 3
I 3
    fprintf(stderr, "Entering new_state(%d)\n", symbol);
E 3
#endif

D 3
  if (nstates >= MAXSHORT)
    fatal("too many states");
E 3
I 3
    if (nstates >= MAXSHORT)
	fatal("too many states");
E 3

D 3
  isp1 = kernel_base[symbol];
  iend = kernel_end[symbol];
  n = iend - isp1;
E 3
I 3
    isp1 = kernel_base[symbol];
    iend = kernel_end[symbol];
    n = iend - isp1;
E 3

D 3
  p = (core *) allocate((unsigned) (sizeof(core) + (n - 1) * sizeof(short)));
  p->accessing_symbol = symbol;
  p->number = nstates;
  p->nitems = n;
E 3
I 3
    p = (core *) allocate((unsigned) (sizeof(core) + (n - 1) * sizeof(short)));
    p->accessing_symbol = symbol;
    p->number = nstates;
    p->nitems = n;
E 3

D 3
  isp2 = p->items;
  while (isp1 < iend)
    *isp2++ = *isp1++;
E 3
I 3
    isp2 = p->items;
    while (isp1 < iend)
	*isp2++ = *isp1++;
E 3

D 3
  last_state->next = p;
  last_state = p;
E 3
I 3
    last_state->next = p;
    last_state = p;
E 3

D 3
  nstates++;
E 3
I 3
    nstates++;
E 3

D 3
  return (p);
E 3
I 3
    return (p);
E 3
}


/* show_cores is used for debugging */

show_cores()
{
    core *p;
    int i, j, k, n;
    int itemno;

    k = 0;
    for (p = first_state; p; ++k, p = p->next)
    {
	if (k) printf("\n");
	printf("state %d, number = %d, accessing symbol = %s\n",
		k, p->number, symbol_name[p->accessing_symbol]);
	n = p->nitems;
	for (i = 0; i < n; ++i)
	{
	    itemno = p->items[i];
	    printf("%4d  ", itemno);
	    j = itemno;
	    while (ritem[j] >= 0) ++j;
	    printf("%s :", symbol_name[rlhs[-ritem[j]]]);
	    j = rrhs[-ritem[j]];
	    while (j < itemno)
		printf(" %s", symbol_name[ritem[j++]]);
	    printf(" .");
	    while (ritem[j] >= 0)
		printf(" %s", symbol_name[ritem[j++]]);
	    printf("\n");
	    fflush(stdout);
	}
    }
}


/* show_ritems is used for debugging */

show_ritems()
{
    int i;

    for (i = 0; i < nitems; ++i)
	printf("ritem[%d] = %d\n", i, ritem[i]);
}


/* show_rrhs is used for debugging */
show_rrhs()
{
    int i;

    for (i = 0; i < nrules; ++i)
	printf("rrhs[%d] = %d\n", i, rrhs[i]);
}


/* show_shifts is used for debugging */

show_shifts()
{
    shifts *p;
    int i, j, k;

    k = 0;
    for (p = first_shift; p; ++k, p = p->next)
    {
	if (k) printf("\n");
	printf("shift %d, number = %d, nshifts = %d\n", k, p->number,
		p->nshifts);
	j = p->nshifts;
	for (i = 0; i < j; ++i)
	    printf("\t%d\n", p->shift[i]);
    }
}


save_shifts()
{
D 3
  register shifts *p;
  register short *sp1;
  register short *sp2;
  register short *send;
E 3
I 3
    register shifts *p;
    register short *sp1;
    register short *sp2;
    register short *send;
E 3

D 3
  p = (shifts *) allocate((unsigned) (sizeof(shifts) +
E 3
I 3
    p = (shifts *) allocate((unsigned) (sizeof(shifts) +
E 3
			(nshifts - 1) * sizeof(short)));

D 3
  p->number = this_state->number;
  p->nshifts = nshifts;
E 3
I 3
    p->number = this_state->number;
    p->nshifts = nshifts;
E 3

D 3
  sp1 = shiftset;
  sp2 = p->shift;
  send = shiftset + nshifts;
E 3
I 3
    sp1 = shiftset;
    sp2 = p->shift;
    send = shiftset + nshifts;
E 3

D 3
  while (sp1 < send)
    *sp2++ = *sp1++;
E 3
I 3
    while (sp1 < send)
	*sp2++ = *sp1++;
E 3

D 3
  if (last_shift)
E 3
I 3
    if (last_shift)
E 3
    {
D 3
      last_shift->next = p;
      last_shift = p;
E 3
I 3
	last_shift->next = p;
	last_shift = p;
E 3
    }
D 3
  else
E 3
I 3
    else
E 3
    {
D 3
      first_shift = p;
      last_shift = p;
E 3
I 3
	first_shift = p;
	last_shift = p;
E 3
    }
}



save_reductions()
{
D 3
  register short *isp;
  register short *rp1;
  register short *rp2;
  register int item;
  register int count;
  register reductions *p;
E 3
I 3
    register short *isp;
    register short *rp1;
    register short *rp2;
    register int item;
    register int count;
    register reductions *p;
    register short *rend;
E 3

D 3
  short *rend;

  count = 0;
  for (isp = itemset; isp < itemsetend; isp++)
E 3
I 3
    count = 0;
    for (isp = itemset; isp < itemsetend; isp++)
E 3
    {
D 3
      item = ritem[*isp];
      if (item < 0)
E 3
I 3
	item = ritem[*isp];
	if (item < 0)
E 3
	{
D 3
	  redset[count++] = -item;
E 3
I 3
	    redset[count++] = -item;
E 3
	}
    }

D 3
  if (count)
E 3
I 3
    if (count)
E 3
    {
D 3
      p = (reductions *) allocate((unsigned) (sizeof(reductions) +
E 3
I 3
	p = (reductions *) allocate((unsigned) (sizeof(reductions) +
E 3
					(count - 1) * sizeof(short)));

D 3
      p->number = this_state->number;
      p->nreds = count;
E 3
I 3
	p->number = this_state->number;
	p->nreds = count;
E 3

D 3
      rp1 = redset;
      rp2 = p->rules;
      rend = rp1 + count;
E 3
I 3
	rp1 = redset;
	rp2 = p->rules;
	rend = rp1 + count;
E 3

D 3
      while (rp1 < rend)
	*rp2++ = *rp1++;
E 3
I 3
	while (rp1 < rend)
	    *rp2++ = *rp1++;
E 3

D 3
      if (last_reduction)
E 3
I 3
	if (last_reduction)
E 3
	{
D 3
	  last_reduction->next = p;
	  last_reduction = p;
E 3
I 3
	    last_reduction->next = p;
	    last_reduction = p;
E 3
	}
D 3
      else
E 3
I 3
	else
E 3
	{
D 3
	  first_reduction = p;
	  last_reduction = p;
E 3
I 3
	    first_reduction = p;
	    last_reduction = p;
E 3
	}
    }
}


set_derives()
{
D 3
  register int i, k;
  register int lhs;
  register short *rules;
E 3
I 3
    register int i, k;
    register int lhs;
    register short *rules;
E 3

D 3
  derives = NEW2(nsyms, short *);
  rules = NEW2(nvars + nrules, short);
E 3
I 3
    derives = NEW2(nsyms, short *);
    rules = NEW2(nvars + nrules, short);
E 3

D 3
  k = 0;
  for (lhs = start_symbol; lhs < nsyms; lhs++)
E 3
I 3
    k = 0;
    for (lhs = start_symbol; lhs < nsyms; lhs++)
E 3
    {
D 3
      derives[lhs] = rules + k;
      for (i = 0; i < nrules; i++)
E 3
I 3
	derives[lhs] = rules + k;
	for (i = 0; i < nrules; i++)
E 3
	{
D 3
	  if (rlhs[i] == lhs)
E 3
I 3
	    if (rlhs[i] == lhs)
E 3
	    {
D 3
	      rules[k] = i;
	      k++;
E 3
I 3
		rules[k] = i;
		k++;
E 3
	    }
	}
D 3
      rules[k] = -1;
      k++;
E 3
I 3
	rules[k] = -1;
	k++;
E 3
    }

#ifdef	DEBUG
D 3
  print_derives();
E 3
I 3
    print_derives();
E 3
#endif
}

free_derives()
{
D 3
  FREE(derives[start_symbol]);
  FREE(derives);
E 3
I 3
    FREE(derives[start_symbol]);
    FREE(derives);
E 3
}

#ifdef	DEBUG
print_derives()
{
D 3
  register int i;
  register short *sp;
E 3
I 3
    register int i;
    register short *sp;
E 3

D 3
  printf("\nDERIVES\n\n");
E 3
I 3
    printf("\nDERIVES\n\n");
E 3

D 3
  for (i = start_symbol; i < nsyms; i++)
E 3
I 3
    for (i = start_symbol; i < nsyms; i++)
E 3
    {
D 3
      printf("%s derives ", symbol_name[i]);
      for (sp = derives[i]; *sp >= 0; sp++)
E 3
I 3
	printf("%s derives ", symbol_name[i]);
	for (sp = derives[i]; *sp >= 0; sp++)
E 3
	{
D 3
	  printf("  %d", *sp);
E 3
I 3
	    printf("  %d", *sp);
E 3
	}
D 3
      putchar('\n');
E 3
I 3
	putchar('\n');
E 3
    }

D 3
  putchar('\n');
E 3
I 3
    putchar('\n');
E 3
}
#endif


set_nullable()
{
    register int i, j;
    register int empty;
    int done;

    nullable = MALLOC(nsyms);
    if (nullable == 0) no_space();

    for (i = 0; i < nsyms; ++i)
	nullable[i] = 0;

    done = 0;
    while (!done)
    {
	done = 1;
	for (i = 1; i < nitems; i++)
	{
	    empty = 1;
	    while ((j = ritem[i]) >= 0)
	    {
		if (!nullable[j])
		    empty = 0;
		++i;
	    }
	    if (empty)
	    {
		j = rlhs[-j];
		if (!nullable[j])
		{
		    nullable[j] = 1;
		    done = 0;
		}
	    }
	}
    }

#ifdef DEBUG
    for (i = 0; i < nsyms; i++)
    {
	if (nullable[i])
	    printf("%s is nullable\n", symbol_name[i]);
	else
	    printf("%s is not nullable\n", symbol_name[i]);
    }
#endif
}


free_nullable()
{
D 3
  FREE(nullable);
E 3
I 3
    FREE(nullable);
E 3
}


lr0()
{
    set_derives();
    set_nullable();
    generate_states();
}
E 1
