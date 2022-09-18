h53254
s 00065/00075/00204
d D 5.3 93/05/24 21:29:25 bostic 3 2
c revision 1.9 from Bob Corbett
e
s 00001/00011/00278
d D 5.2 90/06/01 16:13:05 bostic 2 1
c new copyright notice
e
s 00289/00000/00000
d D 5.1 89/12/25 14:24:26 bostic 1 0
c date and time created 89/12/25 14:24:26 by bostic
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

short *itemset;
short *itemsetend;
unsigned *ruleset;

static unsigned *first_derives;
static unsigned *EFF;


set_EFF()
{
    register unsigned *row;
    register int symbol;
    register short *sp;
    register int rowsize;
    register int i;
    register int rule;

    rowsize = WORDSIZE(nvars);
    EFF = NEW2(nvars * rowsize, unsigned);

    row = EFF;
    for (i = start_symbol; i < nsyms; i++)
    {
	sp = derives[i];
	for (rule = *sp; rule > 0; rule = *++sp)
	{
	    symbol = ritem[rrhs[rule]];
	    if (ISVAR(symbol))
	    {
		symbol -= start_symbol;
		SETBIT(row, symbol);
	    }
	}
	row += rowsize;
    }

    reflexive_transitive_closure(EFF, nvars);

#ifdef	DEBUG
    print_EFF();
#endif
}


set_first_derives()
{
D 3
  register unsigned *rrow;
  register unsigned *vrow;
  register int j;
  register unsigned mask;
  register unsigned cword;
  register short *rp;
E 3
I 3
    register unsigned *rrow;
    register unsigned *vrow;
    register int j;
    register unsigned k;
    register unsigned cword;
    register short *rp;
E 3

D 3
  int rule;
  int i;
  int rulesetsize;
  int varsetsize;
E 3
I 3
    int rule;
    int i;
    int rulesetsize;
    int varsetsize;
E 3

D 3
  rulesetsize = WORDSIZE(nrules);
  varsetsize = WORDSIZE(nvars);
  first_derives = NEW2(nvars * rulesetsize, unsigned) - ntokens * rulesetsize;
E 3
I 3
    rulesetsize = WORDSIZE(nrules);
    varsetsize = WORDSIZE(nvars);
    first_derives = NEW2(nvars * rulesetsize, unsigned) - ntokens * rulesetsize;
E 3

D 3
  set_EFF();
E 3
I 3
    set_EFF();
E 3

D 3
  rrow = first_derives + ntokens * rulesetsize;
  for (i = start_symbol; i < nsyms; i++)
E 3
I 3
    rrow = first_derives + ntokens * rulesetsize;
    for (i = start_symbol; i < nsyms; i++)
E 3
    {
D 3
      vrow = EFF + ((i - ntokens) * varsetsize);
      cword = *vrow++;
      mask = 1;
      for (j = start_symbol; j < nsyms; j++)
E 3
I 3
	vrow = EFF + ((i - ntokens) * varsetsize);
	k = BITS_PER_WORD;
	for (j = start_symbol; j < nsyms; k++, j++)
E 3
	{
D 3
	  if (cword & mask)
E 3
I 3
	    if (k >= BITS_PER_WORD)
E 3
	    {
D 3
	      rp = derives[j];
	      while ((rule = *rp++) >= 0)
		{
		  SETBIT(rrow, rule);
		}
E 3
I 3
		cword = *vrow++;
		k = 0;
E 3
	    }

D 3
	  mask <<= 1;
	  if (mask == 0)
E 3
I 3
	    if (cword & (1 << k))
E 3
	    {
D 3
	      cword = *vrow++;
	      mask = 1;
E 3
I 3
		rp = derives[j];
		while ((rule = *rp++) >= 0)
		{
		    SETBIT(rrow, rule);
		}
E 3
	    }
	}

D 3
      vrow += varsetsize;
      rrow += rulesetsize;
E 3
I 3
	vrow += varsetsize;
	rrow += rulesetsize;
E 3
    }

#ifdef	DEBUG
D 3
  print_first_derives();
E 3
I 3
    print_first_derives();
E 3
#endif

D 3
  FREE(EFF);
E 3
I 3
    FREE(EFF);
E 3
}


closure(nucleus, n)
short *nucleus;
int n;
{
    register int ruleno;
    register unsigned word;
D 3
    register unsigned mask;
E 3
I 3
    register unsigned i;
E 3
    register short *csp;
    register unsigned *dsp;
    register unsigned *rsp;
    register int rulesetsize;

    short *csend;
    unsigned *rsend;
    int symbol;
    int itemno;

    rulesetsize = WORDSIZE(nrules);
    rsp = ruleset;
    rsend = ruleset + rulesetsize;
    for (rsp = ruleset; rsp < rsend; rsp++)
	*rsp = 0;

    csend = nucleus + n;
    for (csp = nucleus; csp < csend; ++csp)
    {
	symbol = ritem[*csp];
	if (ISVAR(symbol))
	{
	    dsp = first_derives + symbol * rulesetsize;
	    rsp = ruleset;
	    while (rsp < rsend)
		*rsp++ |= *dsp++;
	}
    }

    ruleno = 0;
    itemsetend = itemset;
    csp = nucleus;
    for (rsp = ruleset; rsp < rsend; ++rsp)
    {
	word = *rsp;
D 3
	if (word == 0)
	    ruleno += BITS_PER_WORD;
	else
E 3
I 3
	if (word)
E 3
	{
D 3
	    mask = 1;
	    while (mask)
E 3
I 3
	    for (i = 0; i < BITS_PER_WORD; ++i)
E 3
	    {
D 3
		if (word & mask)
E 3
I 3
		if (word & (1 << i))
E 3
		{
D 3
		    itemno = rrhs[ruleno];
E 3
I 3
		    itemno = rrhs[ruleno+i];
E 3
		    while (csp < csend && *csp < itemno)
			*itemsetend++ = *csp++;
		    *itemsetend++ = itemno;
		    while (csp < csend && *csp == itemno)
			++csp;
		}
D 3

		    mask <<= 1;
		    ++ruleno;
E 3
	    }
	}
I 3
	ruleno += BITS_PER_WORD;
E 3
    }

    while (csp < csend)
	*itemsetend++ = *csp++;

#ifdef	DEBUG
  print_closure(n);
#endif
}



finalize_closure()
{
  FREE(itemset);
  FREE(ruleset);
  FREE(first_derives + ntokens * WORDSIZE(nrules));
}


#ifdef	DEBUG

print_closure(n)
int n;
{
  register short *isp;

  printf("\n\nn = %d\n\n", n);
  for (isp = itemset; isp < itemsetend; isp++)
    printf("   %d\n", *isp);
}


print_EFF()
{
D 3
    register int i, j, k;
E 3
I 3
    register int i, j;
E 3
    register unsigned *rowp;
    register unsigned word;
D 3
    register unsigned mask;
E 3
I 3
    register unsigned k;
E 3

    printf("\n\nEpsilon Free Firsts\n");

    for (i = start_symbol; i < nsyms; i++)
    {
	printf("\n%s", symbol_name[i]);
	rowp = EFF + ((i - start_symbol) * WORDSIZE(nvars));
	word = *rowp++;

D 3
	mask = 1;
	for (j = 0; j < nvars; j++)
E 3
I 3
	k = BITS_PER_WORD;
	for (j = 0; j < nvars; k++, j++)
E 3
	{
D 3
	    if (word & mask)
		printf("  %s", symbol_name[start_symbol + j]);

	    mask <<= 1;
	    if (mask == 0)
E 3
I 3
	    if (k >= BITS_PER_WORD)
E 3
	    {
		word = *rowp++;
D 3
		mask = 1;
E 3
I 3
		k = 0;
E 3
	    }
I 3

	    if (word & (1 << k))
		printf("  %s", symbol_name[start_symbol + j]);
E 3
	}
    }
}


print_first_derives()
{
D 3
  register int i;
  register int j;
  register unsigned *rp;
  register unsigned cword;
  register unsigned mask;
E 3
I 3
    register int i;
    register int j;
    register unsigned *rp;
    register unsigned cword;
    register unsigned k;
E 3

D 3
  printf("\n\n\nFirst Derives\n");
E 3
I 3
    printf("\n\n\nFirst Derives\n");
E 3

D 3
  for (i = start_symbol; i < nsyms; i++)
E 3
I 3
    for (i = start_symbol; i < nsyms; i++)
E 3
    {
D 3
      printf("\n%s derives\n", symbol_name[i]);
      rp = first_derives + i * WORDSIZE(nrules);
      cword = *rp++;
      mask = 1;
      for (j = 0; j <= nrules; j++)
E 3
I 3
	printf("\n%s derives\n", symbol_name[i]);
	rp = first_derives + i * WORDSIZE(nrules);
	k = BITS_PER_WORD;
	for (j = 0; j <= nrules; k++, j++)
E 3
        {
D 3
	  if (cword & mask)
	    printf("   %d\n", j);

	  mask <<= 1;
	  if (mask == 0)
	    {
E 3
I 3
	  if (k >= BITS_PER_WORD)
	  {
E 3
	      cword = *rp++;
D 3
	      mask = 1;
	    }
E 3
I 3
	      k = 0;
	  }

	  if (cword & (1 << k))
	    printf("   %d\n", j);
E 3
	}
    }

  fflush(stdout);
}

#endif
E 1
