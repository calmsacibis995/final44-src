h02102
s 00002/00002/00042
d D 8.1 93/05/31 14:28:28 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00042
d D 5.3 93/02/28 14:59:18 bostic 3 2
c add multiple access method code back in; signal fix
c from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00020/00015/00024
d D 5.2 93/01/23 15:47:31 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00039/00000/00000
d D 5.1 93/01/23 11:12:57 bostic 1 0
c date and time created 93/01/23 11:12:57 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

I 3
#ifdef DBI
E 3
#include <db.h>
I 3
#endif
E 3
#include <regex.h>
#include <setjmp.h>
#include <stdio.h>

E 2
#include "ed.h"
I 2
#include "extern.h"
E 2

/*
 * This sets things up for the central input routine to place the text
 * at the proper location for an append.
 */
D 2

E 2
void
a(inputt, errnum)
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
  if (rol(inputt, errnum))
    return;
E 2
I 2
	if (rol(inputt, errnum))
		return;
E 2

D 2
  if (g_flag == 0)
    u_clr_stk();
  if (sigint_flag)
    SIGINT_ACTION;
  add_flag = 1;
  input_lines(inputt, errnum);
  add_flag = 0;
} /* end-a */
E 2
I 2
	if (g_flag == 0)
		u_clr_stk();
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	add_flag = 1;
	input_lines(inputt, errnum);
	add_flag = 0;
}
E 2
E 1
