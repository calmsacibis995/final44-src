h01277
s 00001/00001/00032
d D 1.2 92/06/03 16:46:57 elan 2 1
c fixed copyright.
e
s 00033/00000/00000
d D 1.1 92/06/03 16:37:34 elan 1 0
c date and time created 92/06/03 16:37:34 by elan
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
E 2
I 2
static char copyright[] =
E 2
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>
#include <stdlib.h>

void *
stalloc(nbytes) 
	int nbytes;
{
      register void *p;

      if ((p = malloc(nbytes)) == NULL)
	    error("Out of space");
      return p;
}
E 1
