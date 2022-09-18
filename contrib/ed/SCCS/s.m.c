h40237
s 00002/00002/00152
d D 8.1 93/05/31 14:29:40 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00028/00126
d D 5.4 93/03/08 18:31:56 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00012/00007/00142
d D 5.3 93/02/28 15:28:57 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00117/00122/00032
d D 5.2 93/01/23 15:47:49 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00154/00000/00000
d D 5.1 93/01/23 11:13:18 bostic 1 0
c date and time created 93/01/23 11:13:18 by bostic
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
 * Move the specified lines to the new location. It's quick 'cause
 * just a couple of pointers are redirected.
 */
D 2

E 2
void
m(inputt, errnum)
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
  LINE *l_dest, *l_old_top, *l_old_bottom;
E 2
I 2
D 3
	LINE *l_dest, *l_old_top, *l_old_bottom;
E 3
I 3
	LINE *l_dest=NULL, *l_old_top, *l_old_bottom;
E 3
E 2

D 2
  /* set l_dest here */
  if (((ss=getc(inputt)) != '\n') && (ss != EOF))
    {
      while (1)
           {
             if (ss != ' ')
               {
                 ungetc(ss, inputt);
                 break;
               }
             ss = getc(inputt);
           }
      l_dest = address_conv(NULL, inputt, errnum);
    }
  else
    (ungetc(ss, inputt), *errnum = -1);
  if (sigint_flag)
    SIGINT_ACTION;
  if (*errnum < 0)
    {
      strcpy(help_msg, "bad destination address");
      return;
    } /* end-if */
  *errnum = 0;
  if (rol(inputt, errnum))
    return;
E 2
I 2
	/* Set l_dest here. */
	if (((ss = getc(inputt)) != '\n') && (ss != EOF)) {
		for (;;) {
			if (ss != ' ') {
				ungetc(ss, inputt);
				break;
			}
			ss = getc(inputt);
		}
		l_dest = address_conv(NULL, inputt, errnum);
	} else
		(ungetc(ss, inputt), *errnum = -1);
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	if (*errnum < 0) {
		strcpy(help_msg, "bad destination address");
		return;
	}
	*errnum = 0;
	if (rol(inputt, errnum))
		return;
E 2

D 2
  if (start_default && End_default)
    start = End = current;
  else if (start_default)
    start = End;
  if (start == NULL)
    {
      strcpy(help_msg, "bad address");
      *errnum = -1;
      return;
    }
  start_default = End_default = 0;
  if (sigint_flag)
    SIGINT_ACTION;
E 2
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
D 3
		strcpy(help_msg, "bad address");
E 3
I 3
		strcpy(help_msg, "buffer empty");
E 3
		*errnum = -1;
		return;
	}
D 4
	start_default = End_default = 0;
E 4
I 4
	Start_default = End_default = 0;
E 4
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
E 2

D 2
  /* do some address checking */
  if ((l_dest) && ((l_dest == start) || (address_check(l_dest, start) == -1)) && (address_check(End, l_dest) == -1))
    {
      ungetc(ss, inputt);
      *errnum = -1;
      strcpy(help_msg, "destination address in address range");
      return;
    }
E 2
I 2
	/* Do some address checking. */
D 4
	if ((l_dest) && ((l_dest == start) ||
	    (address_check(l_dest, start) == -1)) &&
E 4
I 4
	if ((l_dest) && ((l_dest == Start) ||
	    (address_check(l_dest, Start) == -1)) &&
E 4
	    (address_check(End, l_dest) == -1)) {
		ungetc(ss, inputt);
		*errnum = -1;
		strcpy(help_msg, "destination address in address range");
		return;
	}
	change_flag = 1;
	if (g_flag == 0)
		u_clr_stk();
E 2

D 2
  change_flag = 1;
  if (g_flag == 0)
    u_clr_stk();
E 2
I 2
	/*
	 * Some more address checking. These are "legal" command constructions
	 * but are kind-a useless since the buffer doesn't change.
	 */
I 3
	*errnum = 1;
E 3
D 4
	if ((start == l_dest) || (End == l_dest))
E 4
I 4
	if ((Start == l_dest) || (End == l_dest))
E 4
		return;
D 4
	if ((start == top) && (End == bottom))
E 4
I 4
	if ((Start == top) && (End == bottom))
E 4
		return;
D 4
	if ((start == top) && (l_dest == NULL))
E 4
I 4
	if ((Start == top) && (l_dest == NULL))
E 4
		return;
I 3
	*errnum = 0;
E 3
E 2

D 2
  /* some more address checking. These are "legal" command constructions
   * but are kind-a useless since the buffer doesn't change */
  if ((start == l_dest) || (End == l_dest))
    return;
  if ((start == top) && (End == bottom))
    return;
  if ((start == top) && (l_dest == NULL))
    return;
E 2
I 2
	l_old_top = top;
	l_old_bottom = bottom;
E 2

I 3
	sigspecial++;

E 3
D 2
  l_old_top = top;
  l_old_bottom = bottom;
E 2
I 2
D 4
	if (start == top) {
E 4
I 4
	if (Start == top) {
E 4
		top = End->below;
		u_add_stk(&(End->below->above));
		top->above = NULL;
	} else
		if (End == bottom) {
D 4
			bottom = start->above;
			u_add_stk(&(start->above->below));
E 4
I 4
			bottom = Start->above;
			u_add_stk(&(Start->above->below));
E 4
			bottom->below = NULL;
		} else {
D 4
			u_add_stk(&(start->above->below));
			start->above->below = End->below;
E 4
I 4
			u_add_stk(&(Start->above->below));
			Start->above->below = End->below;
E 4
			u_add_stk(&(End->below->above));
D 4
			End->below->above = start->above;
E 4
I 4
			End->below->above = Start->above;
E 4
		}
E 2

D 2
  if (start == top)
    {
      top = End->below;
      u_add_stk(&(End->below->above));
      top->above = NULL;
    }
  else if (End == bottom)
    {
      bottom = start->above;
      u_add_stk(&(start->above->below));
      bottom->below = NULL;
    }
  else
    {
      u_add_stk(&(start->above->below));
      start->above->below = End->below;
      u_add_stk(&(End->below->above));
      End->below->above = start->above;
    }
E 2
I 2
	if (l_dest == NULL) {
D 4
		u_add_stk(&(start->above));
		start->above = NULL;
E 4
I 4
		u_add_stk(&(Start->above));
		Start->above = NULL;
E 4
		u_add_stk(&(End->below));
		End->below = l_old_top;
		u_add_stk(&(l_old_top->above));
		l_old_top->above = End;
D 4
		top = start;
E 4
I 4
		top = Start;
E 4
	} else
		if (l_dest == l_old_bottom) {
			u_add_stk(&(End->below));
			End->below = NULL;
D 4
			u_add_stk(&(start->above));
			start->above = l_dest;
E 4
I 4
			u_add_stk(&(Start->above));
			Start->above = l_dest;
E 4
			u_add_stk(&(l_dest->below));
D 4
			l_dest->below = start;
E 4
I 4
			l_dest->below = Start;
E 4
			bottom = End;
		} else {
D 4
			u_add_stk(&(start->above));
			start->above = l_dest;
E 4
I 4
			u_add_stk(&(Start->above));
			Start->above = l_dest;
E 4
			u_add_stk(&(End->below));
			End->below = l_dest->below;
			u_add_stk(&(l_dest->below->above));
			l_dest->below->above = End;
			u_add_stk(&(l_dest->below));
D 4
			l_dest->below = start;
E 4
I 4
			l_dest->below = Start;
E 4
		}
E 2

D 2
  if (l_dest == NULL)
    {
      u_add_stk(&(start->above));
      start->above = NULL;
      u_add_stk(&(End->below));
      End->below = l_old_top;
      u_add_stk(&(l_old_top->above));
      l_old_top->above = End;
      top = start;
    }
  else if (l_dest == l_old_bottom)
    {
      u_add_stk(&(End->below));
      End->below = NULL;
      u_add_stk(&(start->above));
      start->above = l_dest;
      u_add_stk(&(l_dest->below));
      l_dest->below = start;
      bottom = End;
    }
  else
    {
      u_add_stk(&(start->above));
      start->above = l_dest;
      u_add_stk(&(End->below));
      End->below = l_dest->below;
      u_add_stk(&(l_dest->below->above));
      l_dest->below->above = End;
      u_add_stk(&(l_dest->below));
      l_dest->below = start;
    }
E 2
I 2
	if (l_dest)
D 4
		l_dest->below = start;
	current = start;
E 4
I 4
		l_dest->below = Start;
	current = Start;
E 4
I 3

	sigspecial--;
E 3
E 2

D 2
  if (l_dest)
    l_dest->below = start;
  current = start;

  *errnum = 1;
} /* end-m */
E 2
I 2
	*errnum = 1;
}
E 2
E 1
