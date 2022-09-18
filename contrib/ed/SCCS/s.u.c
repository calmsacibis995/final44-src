h03366
s 00002/00002/00182
d D 8.1 93/05/31 14:30:11 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00000/00175
d D 5.5 93/05/11 12:08:12 bostic 5 4
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00029/00007/00146
d D 5.4 93/04/28 18:07:17 bostic 4 3
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00016/00001/00137
d D 5.3 93/02/28 15:29:06 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00079/00084/00059
d D 5.2 93/01/23 15:47:58 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00143/00000/00000
d D 5.1 93/01/23 11:13:26 bostic 1 0
c date and time created 93/01/23 11:13:26 by bostic
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
#include <stdlib.h>
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

I 5
struct d_layer *old_d_stk=NULL;


E 5
/*
 * This restores the buffer to the state it was in just before the
 * last buffer modifying command - the global commands (with command
 * list) are looked at as one buffer modifying command. Note: this
 * just manipulates the undo stack (u_stk); x-ref u_add_stk(),
 * u_clr_stk(), d_add(), and d_do().
 */
D 2

E 2
void
u(inputt, errnum)
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
D 4

D 2
  if (u_stk == NULL)
    {
      *errnum = 1;
      return;
    }
  undo();
  *errnum = 1;
} /* end-u */
E 2
I 2
	if (u_stk == NULL) {
		*errnum = 1;
		return;
	}
	undo();
E 4
I 4
	undo(); /* call even when u_stk==nil */
E 4
	*errnum = 1;
}
E 2


D 4
/* This function does the "real work" of the undo. */
E 4
I 4
/* This function does the "real work" of the undo.
 * It is separated out from u() so that the SIGHUP handling
 * routine can call it without dealing with rol(), in turn so that
 * the buffer is in a "good" state when saved to the 'ed.hup' file.
 */
E 4
D 2

E 2
void
undo()
D 2

E 2
{
D 2
  LINE *l_current, *l_bottom, *l_top;
  struct u_layer *l_old_u_stk, *l_temp;
E 2
I 2
	LINE *l_current, *l_bottom, *l_top;
	struct u_layer *l_old_u_stk, *l_temp;
I 5
	struct d_layer *l_d_temp;
E 5
E 2

I 3
	sigspecial++;
E 3
D 2
  /* this is done because undo can be undone */
  l_current = u_current;
  l_top = u_top;
  l_bottom = u_bottom;
E 2
I 2
	/* This is done because undo can be undone. */
	l_current = u_current;
	l_top = u_top;
	l_bottom = u_bottom;
E 2

D 2
  u_current = current;
  u_top = top;
  u_bottom = bottom;
E 2
I 2
	u_current = current;
	u_top = top;
	u_bottom = bottom;
E 2

I 5
	l_d_temp = old_d_stk;
	old_d_stk = d_stk;
	d_stk = l_d_temp;

E 5
D 2
  l_old_u_stk = u_stk;
  u_stk = NULL;
E 2
I 2
	l_old_u_stk = u_stk;
	u_stk = NULL;
E 2

D 2
  while (l_old_u_stk != NULL)
       {
         u_add_stk(l_old_u_stk->cell);
         (*(l_old_u_stk->cell)) = (l_old_u_stk->val);
         l_temp = l_old_u_stk;
         l_old_u_stk = l_old_u_stk->below;
         free(l_temp);
       } /* end-while */
E 2
I 2
	while (l_old_u_stk != NULL) {
		u_add_stk(l_old_u_stk->cell);
		(*(l_old_u_stk->cell)) = (l_old_u_stk->val);
		l_temp = l_old_u_stk;
		l_old_u_stk = l_old_u_stk->below;
		free(l_temp);
	}
E 2

D 2
  current = l_current;
  top = l_top;
  bottom = l_bottom;
} /* end-undo */
E 2
I 2
	current = l_current;
	top = l_top;
	bottom = l_bottom;
I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))
		SIGINT_ACTION;
E 3
}
E 2

I 4

E 4
D 2

/* this function should be called before u_add_stk is in each command
E 2
I 2
/*
 * This function should be called before u_add_stk is in each command
E 2
 * function, _except_ when the global flag is high (>0) -- otherwise,
 * we couldn't undo all of the global commands, only the last iteration
 * of the last command -- and the u command.
 * This is where we begin to dispose of ed's undo knowledge of a line.
 * The call to d_do() gets rid of the rest.
 */
D 2

E 2
void
u_clr_stk()
D 2

E 2
{
D 2
  register struct u_layer *l_temp;
E 2
I 2
	register struct u_layer *l_temp;
E 2

D 2
  u_current = current;
  u_top = top;
  u_bottom = bottom;
E 2
I 2
	u_current = current;
	u_top = top;
	u_bottom = bottom;
E 2

I 3
	sigspecial++;
E 3
D 2
  if ((u_stk) && (d_stk)) /* only if there is something to delete in the buffer */
    d_do();
E 2
I 2
	/* Only if there is something to delete in the buffer. */
	if ((u_stk) && (d_stk))
		d_do();
E 2

D 2
  while (u_stk != NULL)
       {
         l_temp = u_stk;
         u_stk = u_stk->below;
         free(l_temp);
       }
  u_stk = NULL;  /* just to sure */
} /* end-u_clr_stk */
E 2
I 2
	while (u_stk != NULL) {
		l_temp = u_stk;
		u_stk = u_stk->below;
		free(l_temp);
	}
	u_stk = NULL;		/* Just to sure. */
I 5
	old_d_stk = NULL; 	/* so something in use isn't freed! */
E 5
I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))
		SIGINT_ACTION;
E 3
}
E 2

D 2

E 2
/*
 * Place the addresses of and the pointer values of the LINE structures
D 2
 * that are being changed on the undo stack.
 * This is a quick, simple, and effective way to preserve what could be
 * be brought back on request without keeping a copy of every bleep'n
 * thing.
E 2
I 2
 * that are being changed on the undo stack.  This is a quick, simple,
 * and effective way to preserve what could be be brought back on request
 * without keeping a copy of every bleep'n thing.
E 2
 */
D 2

E 2
void
u_add_stk(in)
D 2

LINE **in;

E 2
I 2
	LINE **in;
E 2
{
D 2
  register struct u_layer *l_now;
E 2
I 2
	register struct u_layer *l_now;
E 2

D 2
  if (in == NULL)
    return;
  l_now = (struct u_layer *)malloc(sizeof(struct u_layer));
  if (l_now == NULL)
    {
      strcpy(help_msg, "undo: out of memory error");
      return;
    }
  if (u_stk == NULL)
    (l_now->below) = NULL;
  else
    (l_now->below) = u_stk;
  u_stk = l_now;
  (u_stk->cell) = in;
  (u_stk->val) = (*(u_stk->cell));
} /* end-u_add_stk */
E 2
I 2
	if (in == NULL)
		return;
	l_now = malloc(sizeof(struct u_layer));
	if (l_now == NULL) {
		strcpy(help_msg, "undo: out of memory error");
		return;
	}
I 3
	sigspecial++;
E 3
	if (u_stk == NULL)
		(l_now->below) = NULL;
	else
		(l_now->below) = u_stk;
	u_stk = l_now;
I 4
	(u_stk->cell) = in;
	(u_stk->val) = (*(u_stk->cell));
	sigspecial--;
	if (sigint_flag && (!sigspecial))
		SIGINT_ACTION;
}


/* This 'u' function is just for when 's' notices that a series
 * of adjacent lines are changing. It reduces the undo stack height
 * and lowers the number of (costly) malloc's with reuse. For
 * the environmentally aware the third 'R' is with the 'g' code.
 */

void
u_pop_n_swap(in)
	LINE **in;
{
	sigspecial++;
	/* put the old value back */
	(*(u_stk->cell)) = (u_stk->val);
	/* put the new values */
E 4
	(u_stk->cell) = in;
	(u_stk->val) = (*(u_stk->cell));
I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))
		SIGINT_ACTION;
E 3
}
E 2
E 1
