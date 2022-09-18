h00540
s 00002/00002/00179
d D 8.1 93/05/31 14:28:47 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00178
d D 5.5 93/05/31 13:57:38 bostic 5 4
c use btree access method, not recno access method, so garbage collection
c works -- from Rodney for 4.4BSD
e
s 00014/00014/00164
d D 5.4 93/03/08 18:31:45 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00028/00017/00150
d D 5.3 93/02/28 15:28:31 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00110/00127/00057
d D 5.2 93/01/23 15:47:35 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00184/00000/00000
d D 5.1 93/01/23 11:13:02 bostic 1 0
c date and time created 93/01/23 11:13:02 by bostic
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
#include <stdlib.h>
#include <string.h>

E 2
#include "ed.h"
I 2
#include "extern.h"
E 2

I 2
static void d_add __P((LINE *, LINE *));

E 2
/*
 * This removes lines in the buffer from user access. The specified
 * lines are not really deleted yet(!) as they might be called back
D 4
 * by an undo. So the pointers from start, End, and neighbours are placed
E 4
I 4
 * by an undo. So the pointers from Start, End, and neighbours are placed
E 4
 * in a stack for deletion later when no undo can be performed on these lines.
 * The lines in the buffer are freed then as well.
 */
D 2

E 2
void
d(inputt, errnum)
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
  LINE *l_temp1, *l_temp2;
E 2
I 2
	LINE *l_temp1, *l_temp2;
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
E 2

D 2
  if (rol(inputt, errnum))
    return;
E 2
I 2
D 3
	if (rol(inputt, errnum))
		return;
E 3
I 3
	if (join_flag == 0) {
		if (rol(inputt, errnum))
			return;
	}
	else
		ss = getc(inputt); /* fed back from join */
E 3
E 2

D 2
  if ((u_set == 0) && (g_flag == 0))
    u_clr_stk();  /* for undo */
E 2
I 2
	if ((u_set == 0) && (g_flag == 0))
		u_clr_stk();	/* for undo */
E 2

D 2
  if ((start == NULL) && (End == NULL)) /* nothing to do... */
    {
      *errnum = 1;
      return;
    }
E 2
I 2
D 4
	if ((start == NULL) && (End == NULL)) {	/* nothing to do... */
E 4
I 4
	if ((Start == NULL) && (End == NULL)) {	/* nothing to do... */
E 4
		*errnum = 1;
		return;
	}
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
E 2

D 2
  if (sigint_flag)
    SIGINT_ACTION;
E 2
I 2
D 4
	d_add(start, End);	/* for buffer clearing later(!) */
E 4
I 4
	d_add(Start, End);	/* for buffer clearing later(!) */
E 4
E 2

D 2
  d_add(start, End); /* for buffer clearing later(!) */
E 2
I 2
	/*
D 3
	 * Now change preserve the pointers in case of undo and then adjust
E 3
I 3
	 * Now change & preserve the pointers in case of undo and then adjust
E 3
	 * them.
	 */
I 3
	sigspecial++;
E 3
D 4
	if (start == top) {
E 4
I 4
	if (Start == top) {
E 4
		top = End->below;
		if (top != NULL) {
			u_add_stk(&(top->above));
			(top->above) = NULL;
		}
	} else {
D 4
		l_temp1 = start->above;
E 4
I 4
		l_temp1 = Start->above;
E 4
		u_add_stk(&(l_temp1->below));
		(l_temp1->below) = End->below;
	}
E 2

D 2
  /* now change preserve the pointers in case of undo and then adjust
   * them.
   */
  if (start == top)
    {
      top = End->below;
      if (top != NULL)
        {
          u_add_stk(&(top->above));
          (top->above) = NULL;
        }
    }
  else
    {
      l_temp1 = start->above;
      u_add_stk(&(l_temp1->below));
      (l_temp1->below) = End->below;
    }
E 2
I 2
	if (End == bottom) {
D 4
		bottom = start->above;
E 4
I 4
		bottom = Start->above;
E 4
		current = bottom;
	} else {
		l_temp2 = End->below;
		u_add_stk(&(l_temp2->above));
D 4
		(l_temp2->above) = start->above;
E 4
I 4
		(l_temp2->above) = Start->above;
E 4
		current = l_temp2;
	}
E 2

D 2
  if (End == bottom)
    {
      bottom = start->above;
      current = bottom;
    }
  else
    {
      l_temp2 = End->below;
      u_add_stk(&(l_temp2->above));
      (l_temp2->above) = start->above;
      current = l_temp2;
    }
E 2
I 2
	/* To keep track of the marks. */
D 4
	ku_chk(start, End, NULL);
E 4
I 4
	ku_chk(Start, End, NULL);
E 4
	change_flag = 1L;
E 2

D 2
  /* to keep track of the marks */
  ku_chk(start, End, NULL);
  change_flag = 1L;
E 2
I 2
D 3
	if (sigint_flag)	/* next stable spot */
		SIGINT_ACTION;
E 2

D 2
  if (sigint_flag) /* next stable spot */
    SIGINT_ACTION;
E 2
I 2
	if (start == End) {
		*errnum = 1;
		return;
	}
E 3
	*errnum = 1;
I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))	/* next stable spot */
		SIGINT_ACTION;
E 3
}
E 2

D 2
  if (start == End)
    {
      *errnum = 1;
      return;
    }
E 2

D 2
  *errnum = 1;
} /* end-d */


E 2
/*
 * This keeps a stack of the start and end lines deleted for clean-up
 * later (in d_do()). A stack is used because of the global commands.
 */
D 2

void
E 2
I 2
static void
E 2
d_add(top_d, bottom_d)
D 2

LINE *top_d, *bottom_d;

E 2
I 2
	LINE *top_d, *bottom_d;
E 2
{
D 2
  struct d_layer *l_temp;
E 2
I 2
	struct d_layer *l_temp;
E 2

D 2
  l_temp = (struct d_layer *)malloc(sizeof(struct d_layer));
  (l_temp->begin) = top_d;
  (l_temp->end) = bottom_d;
  (l_temp->next) = d_stk;
  d_stk = l_temp;
E 2
I 2
	l_temp = malloc(sizeof(struct d_layer));
	(l_temp->begin) = top_d;
	(l_temp->end) = bottom_d;
	(l_temp->next) = d_stk;
	d_stk = l_temp;
E 2

D 2
} /* end-d_add */
E 2
I 2
}
E 2

D 2

E 2
/*
 * This cleans up the LINE structures deleted and no longer accessible
 * to undo. It performs garbage clean-up on the now non-referenced
D 2
 * text in the buffer. All three buffer methods here #ifdef'd
E 2
I 2
 * text in the buffer.
E 2
 */
D 2

E 2
void
d_do()
D 2

E 2
{
D 2
  struct d_layer *l_temp;
  LINE *l_temp2, *l_temp3;
  int l_flag;
#ifdef DBI
  DBT l_db_key;
#endif
E 2
I 2
	struct d_layer *l_temp;
I 3
#ifdef DBI
E 3
	DBT l_db_key;
I 3
#endif
E 3
	LINE *l_temp2, *l_temp3;
	int l_flag;
E 2

D 2
  l_temp = d_stk;
E 2
I 2
	l_temp = d_stk;
I 3
	sigspecial++;
E 3
	do {
		l_flag = 0;
		l_temp2 = l_temp->begin;
		do {
			l_temp3 = l_temp2;
D 3
			/*
			 * We do it, but db(3) says it doesn't really do it
			 * yet.
			 */
E 3
I 3
#ifdef STDIO
			/* no garbage collection done currently */
#endif
#ifdef DBI
I 5
			/* garbage collection should be done iff the
			 * open was done as btree, not recno.
			 */
E 5
E 3
			l_db_key.size = sizeof(recno_t);
			l_db_key.data = &(l_temp2->handle);
			(dbhtmp->del) (dbhtmp, &l_db_key, (u_int) 0);
I 3
#endif
#ifdef MEMORY
			free(l_temp2->handle);
#endif
E 3
			if ((l_temp->end) == l_temp2)
				l_flag = 1;
			l_temp2 = l_temp3->below;
			free(l_temp3);
		} while (l_flag == 0);
E 2

D 2
  do
    {
      l_flag = 0;
      l_temp2 = l_temp->begin;
      do
        {
          l_temp3 = l_temp2;
#ifdef STDIO
          /* no garbage collection done currently */
#endif
#ifdef DBI
          /* we do it, but db(3) says it doesn't really do it yet */
          l_db_key.size = sizeof(recno_t);
          l_db_key.data = &(l_temp2->handle);
          (dbhtmp->del)(dbhtmp, &l_db_key, (u_int)0);
#endif
#ifdef MEMORY
          free(l_temp2->handle);
#endif
          if ((l_temp->end) == l_temp2)
            l_flag = 1;
          l_temp2 = l_temp3->below;
          free(l_temp3);
        } while (l_flag == 0);
E 2
I 2
		d_stk = d_stk->next;
		free(l_temp);
		l_temp = d_stk;
	} while (d_stk);
E 2

D 2
        d_stk = d_stk->next;
        free(l_temp);
        l_temp = d_stk;
      } while (d_stk);

  d_stk = NULL; /* just to be sure */
} /* end-d_do */
E 2
I 2
	d_stk = NULL;		/* just to be sure */
I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))
		SIGINT_ACTION;
E 3
}
E 2
E 1
