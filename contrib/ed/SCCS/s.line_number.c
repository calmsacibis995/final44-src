h42669
s 00002/00002/00048
d D 8.1 93/05/31 14:29:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00049
d D 5.4 93/04/30 00:10:05 bostic 4 3
c update from Rodney Ruddock for 4.4BSD; bug fixes, plus reworking
c of the bang command to permit sh scripts from within ed, a la SunOS
e
s 00004/00003/00046
d D 5.3 93/02/28 15:28:56 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00024/00020/00025
d D 5.2 93/01/23 15:47:48 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00045/00000/00000
d D 5.1 93/01/23 11:13:17 bostic 1 0
c date and time created 93/01/23 11:13:17 by bostic
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
 * Converts a LINE to a line number (int) that can be printed to
D 4
 * the device the user is at. Used by n.
E 4
I 4
 * the device the user is at. Used by n and =.
E 4
 */
D 2

E 2
int
line_number(line_addr)
D 2

LINE *line_addr;

E 2
I 2
	LINE *line_addr;
E 2
{
D 2
  int l_cnt=1; /* yes! =1 */
  LINE *l_temp1;
E 2
I 2
	LINE *l_temp1;
	int l_cnt = 1;		/* yes! =1 */
E 2

D 2
  l_temp1 = top;
  if ((line_addr == NULL) && (top == NULL))
    return(0);
E 2
I 2
	l_temp1 = top;
	if ((line_addr == NULL) && (top == NULL))
		return (0);
E 2

D 2
  while (1)
       {
         if (sigint_flag)
           SIGINT_ACTION;
         if (line_addr == l_temp1)
           break;
         l_temp1 = l_temp1->below;
         l_cnt++;
       } /* end-while */
  return(l_cnt);
} /* end-line_number */
E 2
I 2
	for (;;) {
D 3
		if (sigint_flag)
			SIGINT_ACTION;
E 3
		if (line_addr == l_temp1)
			break;
		l_temp1 = l_temp1->below;
		l_cnt++;
	}
	return (l_cnt);
}
E 2
E 1
