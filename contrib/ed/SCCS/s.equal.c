h35365
s 00002/00002/00046
d D 8.1 93/05/31 14:28:59 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00044
d D 5.4 93/03/08 18:31:48 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00004/00001/00044
d D 5.3 93/02/28 15:28:45 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00020/00015/00025
d D 5.2 93/01/23 15:47:39 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00040/00000/00000
d D 5.1 93/01/23 11:13:06 bostic 1 0
c date and time created 93/01/23 11:13:06 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Rodney Ruddock of the University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 2
#include <sys/types.h>

D 3
#include <db.h>
E 3
#include <regex.h>
#include <setjmp.h>
#include <stdio.h>
I 3

#ifdef DBI
#include <db.h>
#endif
E 3

E 2
#include "ed.h"
I 2
#include "extern.h"
E 2

/*
 * Print out what the line number of the address given is; default to
 * end-of-buffer ($).
 */
D 2
 
E 2
void
equal(inputt, errnum)
D 2

FILE *inputt;
int *errnum;

E 2
I 2
	FILE *inputt;
	int *errnum;
E 2
{
D 2
  if (End_default)
    start = bottom;
  else
    start = End;
  start_default = End_default = 0;
E 2
I 2
	if (End_default)
D 4
		start = bottom;
E 4
I 4
		Start = bottom;
E 4
	else
D 4
		start = End;
	start_default = End_default = 0;
E 4
I 4
		Start = End;
	Start_default = End_default = 0;
E 4
E 2

D 2
  if (rol(inputt, errnum))
    return;
E 2
I 2
	if (rol(inputt, errnum))
		return;
E 2

D 2
  printf("%d\n", line_number(start));
  *errnum = 1;
} /* end-equal */
E 2
I 2
D 4
	(void)printf("%d\n", line_number(start));
E 4
I 4
	(void)printf("%d\n", line_number(Start));
E 4
	*errnum = 1;
}
E 2
E 1
