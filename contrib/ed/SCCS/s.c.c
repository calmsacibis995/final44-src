h50082
s 00002/00002/00065
d D 8.1 93/05/31 14:28:42 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00001/00061
d D 5.5 93/05/11 12:07:30 bostic 5 4
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00007/00007/00055
d D 5.4 93/03/08 18:31:44 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00004/00003/00058
d D 5.3 93/02/28 15:28:30 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00035/00030/00026
d D 5.2 93/01/23 15:47:34 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00056/00000/00000
d D 5.1 93/01/23 11:13:01 bostic 1 0
c date and time created 93/01/23 11:13:01 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
 * This deletes the range of lines specified and then sets up things
 * for the central input routine.
 */

void
c(inputt, errnum)
D 2

FILE *inputt;
int *errnum;

E 2
I 2
	FILE *inputt;
	int *errnum;
E 2
{
I 5
	int l_flag=1;

E 5
I 2
D 4
	if (start_default && End_default)
		start = End = current;
E 4
I 4
	if (Start_default && End_default)
		Start = End = current;
E 4
	else
D 4
		if (start_default)
			start = End;
	if (start == NULL) {
E 4
I 4
		if (Start_default)
			Start = End;
	if (Start == NULL) {
E 4
		*errnum = -1;
		return;
	}
D 4
	start_default = End_default = 0;
E 4
I 4
	Start_default = End_default = 0;
I 5
	if (End == bottom)
		l_flag = 0;
E 5
E 4
E 2

D 2
  if (start_default && End_default)
    start = End = current;
  else if (start_default)
    start = End;
  if (start == NULL)
    {
      *errnum = -1;
      return;
    }
  start_default = End_default = 0;
E 2
I 2
	/* first delete the lines */
	d(inputt, errnum);
	if (*errnum < 0)
		return;
	*errnum = 0;
E 2

D 2
  /* first delete the lines */
  d(inputt, errnum);
  if (*errnum < 0)
      return;
  *errnum = 0;

  if ((current != NULL) && (current != bottom))
    current = current->above;
  if (sigint_flag)
    SIGINT_ACTION;
  add_flag = 1;
  start_default = End_default = 1;
  /* now get the "change" lines */
  input_lines(inputt, errnum);
  add_flag = 0;
} /* end-c */
E 2
I 2
D 5
	if ((current != NULL) && (current != bottom))
E 5
I 5
	/*if ((current != NULL) && (current != bottom)) RMSR */
	if ((current != NULL) && l_flag)
E 5
		current = current->above;
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	add_flag = 1;
D 4
	start_default = End_default = 1;
E 4
I 4
	Start_default = End_default = 1;
E 4
	/* now get the "change" lines */
	input_lines(inputt, errnum);
	add_flag = 0;
}
E 2
E 1
