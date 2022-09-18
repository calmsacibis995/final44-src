h38669
s 00002/00002/00139
d D 8.1 93/05/31 14:30:08 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00134
d D 5.4 93/03/08 18:31:59 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00012/00009/00129
d D 5.3 93/02/28 15:29:05 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00102/00111/00036
d D 5.2 93/01/23 15:47:57 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00147/00000/00000
d D 5.1 93/01/23 11:13:25 bostic 1 0
c date and time created 93/01/23 11:13:25 by bostic
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

/*
 * The transcribe function. POSIX calls it copy, but 't' for transcribe
 * is more mneumonic and that's what I've always called it. Transcribes
 * the spec'd lines into the buffer at the spec'd location.
 */

void
t(inputt, errnum)
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
  LINE *l_ptr, *l_tb, *l_te, *l_temp1, *l_temp2, *l_dest;
E 2
I 2
D 3
	LINE *l_ptr, *l_tb, *l_te, *l_temp1, *l_temp2, *l_dest;
E 3
I 3
	LINE *l_ptr, *l_tb, *l_te, *l_temp1, *l_temp2, *l_dest=NULL;
E 3
E 2

D 2
  l_tb = NULL;
  l_te = NULL;
E 2
I 2
	l_tb = NULL;
	l_te = NULL;
E 2

D 2
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
E 2
I 2
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
E 2

D 2
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
		strcpy(help_msg, "empty buffer");
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
  if (sigint_flag)
    SIGINT_ACTION;
E 2
I 2
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 2

E 3
D 2
  if (g_flag == 0)
    u_clr_stk();
E 2
I 2
	if (g_flag == 0)
		u_clr_stk();
E 2

I 3
	sigspecial++;

E 3
D 2
  for (l_ptr=start; l_ptr!=(End->below); l_ptr=(l_ptr->below) )
     {
       get_line(l_ptr->handle, l_ptr->len);
       l_temp1 = (LINE *)malloc(sizeof(LINE));
       if (l_temp1 == NULL)
         {
           *errnum = -1;
           strcpy(help_msg, "out of memory error");
           return;
         }
       if (l_tb == NULL)
         {
           l_tb = l_temp1;
           (l_temp1->above) = NULL;
           (l_temp1->below) = NULL;
         }
       else
         {
           (l_temp1->above) = l_te;
           (l_temp1->below) = NULL;
           (l_te->below) = l_temp1;
         }
       l_te = l_temp1;
       (l_temp1->len) = l_ptr->len;
       /* add it into the buffer at the spec'd location */
       (l_temp1->handle) = add_line(text, l_ptr->len);
       if (sigint_flag)
         break;
     } /* end-for */
E 2
I 2
D 4
	for (l_ptr = start; l_ptr != (End->below); l_ptr = (l_ptr->below)) {
E 4
I 4
	for (l_ptr = Start; l_ptr != (End->below); l_ptr = (l_ptr->below)) {
E 4
		get_line(l_ptr->handle, l_ptr->len);
I 3
		if (sigint_flag && (!sigspecial))
			break;
E 3
		l_temp1 = (LINE *) malloc(sizeof(LINE));
		if (l_temp1 == NULL) {
			*errnum = -1;
			strcpy(help_msg, "out of memory error");
			return;
		}
		if (l_tb == NULL) {
			l_tb = l_temp1;
			(l_temp1->above) = NULL;
			(l_temp1->below) = NULL;
		} else {
			(l_temp1->above) = l_te;
			(l_temp1->below) = NULL;
			(l_te->below) = l_temp1;
		}
		l_te = l_temp1;
		(l_temp1->len) = l_ptr->len;
		/* add it into the buffer at the spec'd location */
		(l_temp1->handle) = add_line(text, l_ptr->len);
D 3
		if (sigint_flag)
E 3
I 3
		if (sigint_flag && (!sigspecial))
E 3
			break;
	}
E 2

D 2
  if (l_dest == NULL)
    l_temp2 = top;
  else
    {
      u_add_stk(&(l_dest->below));
      l_temp2 = l_dest->below;
    }
E 2
I 2
	if (l_dest == NULL)
		l_temp2 = top;
	else {
		u_add_stk(&(l_dest->below));
		l_temp2 = l_dest->below;
	}
E 2

D 2
  if (l_dest == NULL)
    {
      u_add_stk(&(top->above));
      (top->above) = l_tb;
      top = l_tb;
      (l_tb->above) = NULL;
    } /* end-if, */
  else
    {
      (l_tb->above) = l_dest;
      (l_dest->below) = l_tb;
    } /* end-if,else */
E 2
I 2
	if (l_dest == NULL) {
		u_add_stk(&(top->above));
		(top->above) = l_tb;
		top = l_tb;
		(l_tb->above) = NULL;
	} else {
		(l_tb->above) = l_dest;
		(l_dest->below) = l_tb;
	}
E 2

D 2
  if (l_dest == bottom)
    {
      bottom = l_te;
      (l_te->below) = NULL;
    } /* end-if, */
  else
    {
      (l_te->below) = l_temp2;
      u_add_stk(&(l_temp2->above));
      (l_temp2->above) = l_te;
    } /* end-if,else */
E 2
I 2
	if (l_dest == bottom) {
		bottom = l_te;
		(l_te->below) = NULL;
	} else {
		(l_te->below) = l_temp2;
		u_add_stk(&(l_temp2->above));
		(l_temp2->above) = l_te;
	}
E 2

D 2
  current = l_te;
  change_flag = 1;
  *errnum = 1;
  return;
} /* end-t */
E 2
I 2
	current = l_te;
	change_flag = 1;
I 3
	sigspecial--;
E 3
	*errnum = 1;
	return;
}
E 2
E 1
