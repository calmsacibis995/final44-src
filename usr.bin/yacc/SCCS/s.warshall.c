h02406
s 00010/00012/00086
d D 5.4 93/05/24 21:29:31 bostic 4 3
c revision 1.9 from Bob Corbett
e
s 00001/00011/00097
d D 5.3 90/06/01 16:14:36 bostic 3 2
c new copyright notice
e
s 00047/00050/00061
d D 5.2 90/03/11 22:28:46 corbett 2 1
c I fixed a portability problem.  The code used to assume the conversion 
c unsigned* -> unsigned -> unsigned* was safe.  -rpc
e
s 00111/00000/00000
d D 5.1 89/12/25 14:24:44 bostic 1 0
c date and time created 89/12/25 14:24:44 by bostic
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
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "defs.h"

transitive_closure(R, n)
unsigned *R;
int n;
{
D 2
  register int rowsize;
  register unsigned mask;
  register unsigned *rowj;
  register unsigned *rp;
  register unsigned *rend;
  register unsigned *ccol;
E 2
I 2
    register int rowsize;
D 4
    register unsigned mask;
E 4
I 4
    register unsigned i;
E 4
    register unsigned *rowj;
    register unsigned *rp;
    register unsigned *rend;
    register unsigned *ccol;
    register unsigned *relend;
    register unsigned *cword;
    register unsigned *rowi;
E 2

D 2
  unsigned *relend;
  unsigned *cword;
  unsigned *rowi;
E 2
I 2
    rowsize = WORDSIZE(n);
    relend = R + n*rowsize;
E 2

D 2
  rowsize = ROWSIZE(n);
  relend = (unsigned *) ((unsigned) R + n*rowsize);

  cword = R;
  mask = 1;
  rowi = R;
  while (rowi < relend)
E 2
I 2
    cword = R;
D 4
    mask = 1;
E 4
I 4
    i = 0;
E 4
    rowi = R;
    while (rowi < relend)
E 2
    {
D 2
      ccol = cword;
      rowj = R;
E 2
I 2
	ccol = cword;
	rowj = R;
E 2

D 2
      while (rowj < relend)
E 2
I 2
	while (rowj < relend)
E 2
	{
D 2
	  if (*ccol & mask)
E 2
I 2
D 4
	    if (*ccol & mask)
E 4
I 4
	    if (*ccol & (1 << i))
E 4
E 2
	    {
D 2
	      rp = rowi;
	      rend = (unsigned *) ((unsigned) rowj + rowsize);

	      while (rowj < rend)
		*rowj++ |= *rp++;
E 2
I 2
		rp = rowi;
		rend = rowj + rowsize;
		while (rowj < rend)
		    *rowj++ |= *rp++;
E 2
	    }
D 2
	  else
E 2
I 2
	    else
E 2
	    {
D 2
	      rowj = (unsigned *) ((unsigned) rowj + rowsize);
E 2
I 2
		rowj += rowsize;
E 2
	    }

D 2
	  ccol = (unsigned *) ((unsigned) ccol + rowsize);
E 2
I 2
	    ccol += rowsize;
E 2
	}

D 2
      mask <<= 1;
      if (mask == 0)
E 2
I 2
D 4
	mask <<= 1;
	if (mask == 0)
E 4
I 4
	if (++i >= BITS_PER_WORD)
E 4
E 2
	{
D 2
	  mask = 1;
	  cword++;
E 2
I 2
D 4
	    mask = 1;
E 4
I 4
	    i = 0;
E 4
	    cword++;
E 2
	}

D 2
      rowi = (unsigned *) ((unsigned) rowi + rowsize);
E 2
I 2
	rowi += rowsize;
E 2
    }
}

reflexive_transitive_closure(R, n)
unsigned *R;
int n;
{
D 2
  register int rowsize;
  register unsigned mask;
  register unsigned *rp;
  register unsigned *relend;
E 2
I 2
    register int rowsize;
D 4
    register unsigned mask;
E 4
I 4
    register unsigned i;
E 4
    register unsigned *rp;
    register unsigned *relend;
E 2

D 2
  transitive_closure(R, n);
E 2
I 2
    transitive_closure(R, n);
E 2

D 2
  rowsize = ROWSIZE(n);
  relend = (unsigned *) ((unsigned) R + n*rowsize);
E 2
I 2
    rowsize = WORDSIZE(n);
    relend = R + n*rowsize;
E 2

D 2
  mask = 1;
  rp = R;
  while (rp < relend)
E 2
I 2
D 4
    mask = 1;
E 4
I 4
    i = 0;
E 4
    rp = R;
    while (rp < relend)
E 2
    {
D 2
      *rp |= mask;

      mask <<= 1;
      if (mask == 0)
E 2
I 2
D 4
	*rp |= mask;
	mask <<= 1;
	if (mask == 0)
E 4
I 4
	*rp |= (1 << i);
	if (++i >= BITS_PER_WORD)
E 4
E 2
	{
D 2
	  mask = 1;
	  rp++;
E 2
I 2
D 4
	    mask = 1;
E 4
I 4
	    i = 0;
E 4
	    rp++;
E 2
	}

D 2
      rp = (unsigned *) ((unsigned) rp + rowsize);
E 2
I 2
	rp += rowsize;
E 2
    }
}
E 1
