h33330
s 00002/00002/00064
d D 8.1 93/05/31 14:29:23 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00064
d D 5.4 93/03/08 18:31:50 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00004/00003/00062
d D 5.3 93/02/28 15:28:52 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00034/00030/00031
d D 5.2 93/01/23 15:47:44 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00061/00000/00000
d D 5.1 93/01/23 11:13:12 bostic 1 0
c date and time created 93/01/23 11:13:12 by bostic
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
#include <string.h>

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
 * Set things up for the central input routine to correctly place
 * the text as per the insert command.
 */
D 2

E 2
void
i(inputt, errnum)
D 2

FILE *inputt;
int *errnum;

E 2
I 2
	FILE *inputt;
	int *errnum;
E 2
{
#ifdef POSIX
D 2
  LINE *l_address;
E 2
I 2
	LINE *l_address;
E 2
#endif

D 2
  if ((End_default == 1) && (current != NULL))
    start = End = current->above;
  else
    {
      if (End == NULL)
        {
          strcpy(help_msg, "illegal address for command i");
          *errnum = -1;
          return;
        }
      else
        End = End->above;
    }
  start_default = End_default = 0;
E 2
I 2
	if ((End_default == 1) && (current != NULL))
D 4
		start = End = current->above;
E 4
I 4
		Start = End = current->above;
E 4
	else {
		if (End == NULL) {
			strcpy(help_msg, "illegal address for command i");
			*errnum = -1;
			return;
		} else
			End = End->above;
	}
D 4
	start_default = End_default = 0;
E 4
I 4
	Start_default = End_default = 0;
E 4
E 2
#ifdef POSIX
D 2
  l_address = End;
E 2
I 2
	l_address = End;
E 2
#endif

D 2
  if (sigint_flag)
    SIGINT_ACTION;
  /* 'i' is just a variation on 'a': completely true with BSD; with POSIX we
   * have to fake the location of "current" in a special case.
   */
  a(inputt, errnum);
E 2
I 2
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	/*
	 * 'i' is just a variation on 'a': completely true with BSD; with
	 * POSIX we have to fake the location of "current" in a special case.
	 */
	a(inputt, errnum);
E 2
#ifdef POSIX
D 2
  if (l_address->above)
    current = l_address->below;
E 2
I 2
	if (l_address->above)
		current = l_address->below;
E 2
#endif
D 2
} /* end-i */
E 2
I 2
}
E 2
E 1
