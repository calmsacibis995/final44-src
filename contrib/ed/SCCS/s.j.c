h23334
s 00002/00002/00172
d D 8.1 93/05/31 14:29:28 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00017/00157
d D 5.4 93/03/08 18:31:52 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00028/00013/00146
d D 5.3 93/02/28 15:28:54 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00122/00124/00037
d D 5.2 93/01/23 15:47:46 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00161/00000/00000
d D 5.1 93/01/23 11:13:14 bostic 1 0
c date and time created 93/01/23 11:13:14 by bostic
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
 * Join the spec'd lines onto one line. Make the new line from the
 * old lines and then delete the old ones (undo-able).
 */

void
j(inputt, errnum)
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
  LINE *l_ptr, *l_temp_line;
  char *l_temp1;
  long l_ttl=0;
E 2
I 2
	LINE *l_ptr, *l_temp_line;
	long l_ttl = 0;
	char *l_temp1;
E 2

D 2
  if (start_default && End_default)
    {
      start = current;
      *errnum = 1;
      if ((start->below) != NULL)
        End = start->below;
      else
        return;
    }
  else if (start_default)
    {
      if (rol(inputt, errnum))
        return;
E 2
I 2
D 4
	if (start_default && End_default) {
		start = current;
E 4
I 4
	if (Start_default && End_default) {
		Start = current;
E 4
		*errnum = 1;
D 3
		if ((start->below) != NULL)
			End = start->below;
E 3
I 3
D 4
		if (start == NULL) {
E 4
I 4
		if (Start == NULL) {
E 4
			strcpy(help_msg, "buffer empty");
			*errnum = -1;
			return;
		} else
D 4
			if ((start->below) != NULL)
				End = start->below;
E 4
I 4
			if ((Start->below) != NULL)
				End = Start->below;
E 4
E 3
		else
			return;
	} else
D 4
		if (start_default) {
E 4
I 4
		if (Start_default) {
E 4
			if (rol(inputt, errnum))
				return;
E 2

D 2
      if (End == NULL)
        {
          strcpy(help_msg, "bad address");
          *errnum = -1;
        }
      else
        {
E 2
I 2
			if (End == NULL) {
				strcpy(help_msg, "bad address");
				*errnum = -1;
			} else {
E 2
#ifdef BSD
D 2
          /* for BSD a 'j' with one address sets "current" to that line */
          if (start)
            current = start;
E 2
I 2
				/*
				 * For BSD a 'j' with one address sets
				 * "current" to that line
				 */
D 4
				if (start)
					current = start;
E 4
I 4
				if (Start)
					current = Start;
E 4
E 2
#endif
D 2
          *errnum = 1;
        }
      return;
    }
  if (start == NULL)
    {
      strcpy(help_msg, "bad address");
      *errnum = -1;
      ungetc('\n', inputt);
      return;
    }
  start_default = End_default = 0;
  if (sigint_flag)
    SIGINT_ACTION;
E 2
I 2
				*errnum = 1;
			}
			return;
		}
I 3

E 3
D 4
	if (start == NULL) {
E 4
I 4
	if (Start == NULL) {
E 4
D 3
		strcpy(help_msg, "bad address");
E 3
I 3
		strcpy(help_msg, "buffer empty");
E 3
		*errnum = -1;
D 3
		ungetc('\n', inputt);
E 3
		return;
	}
I 3

E 3
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
  u_set = 1; /* set for d */
E 2
I 2
	if (g_flag == 0)
		u_clr_stk();
	u_set = 1;		/* set for d */
E 2

D 2
  /* figure out what the length of the joined lines will be */
  for (l_ptr=start; l_ptr!=(End->below); l_ptr=(l_ptr->below) )
     l_ttl = l_ptr->len + l_ttl;
E 2
I 2
	/* Figure out what the length of the joined lines will be. */
D 4
	for (l_ptr = start; l_ptr != (End->below); l_ptr = (l_ptr->below))
E 4
I 4
	for (l_ptr = Start; l_ptr != (End->below); l_ptr = (l_ptr->below))
E 4
		l_ttl = l_ptr->len + l_ttl;
E 2

D 2
  if (l_ttl > nn_max)
    {
      /* the new line is bigger than any so far, so make more space */
      free(text);
      nn_max = l_ttl;
      text = (char *)calloc(l_ttl+2, sizeof(char));
      if (text == NULL)
        {
          *errnum = -1;
          strcpy(help_msg, "out of memory error");
          return;
        }
    }
E 2
I 2
	if (l_ttl > nn_max) {
		/*
		 * The new line is bigger than any so far, so make more
		 * space.
		 */
I 3
		sigspecial++;
E 3
		free(text);
		nn_max = l_ttl;
		text = calloc(l_ttl + 2, sizeof(char));
I 3
		sigspecial--;
E 3
		if (text == NULL) {
			*errnum = -1;
			strcpy(help_msg, "out of memory error");
			return;
		}
	}
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	l_temp1 = calloc(l_ttl + 2, sizeof(char));
D 3
	if (text == NULL) {
E 3
I 3
	if (l_temp1 == NULL) {
E 3
		*errnum = -1;
		strcpy(help_msg, "out of memory error");
		return;
	}
	l_temp1[0] = '\0';
E 2

D 2
  if (sigint_flag)
    SIGINT_ACTION;
  l_temp1 = (char *)calloc(l_ttl+2, sizeof(char));
  if (text == NULL)
    {
      *errnum = -1;
      strcpy(help_msg, "out of memory error");
      return;
    }
  l_temp1[0] = '\0';
E 2
I 2
D 4
	l_ptr = start;
E 4
I 4
	l_ptr = Start;
E 4
I 3

	sigspecial++;
E 3
	for (;;) {
		/* Get each line and catenate. */
D 3
		if (sigint_flag)
			goto point;
E 3
		get_line(l_ptr->handle, l_ptr->len);
I 3
		if (sigint_flag && (!sigspecial))
			goto point;
E 3
		strcat(l_temp1, text);
		l_ptr = l_ptr->below;
		if (l_ptr == End->below)
			break;
	}
E 2

D 2
  l_ptr = start;
  while (1)
     {
       /* get each line and catenate */
       if (sigint_flag)
         goto point;
       get_line(l_ptr->handle, l_ptr->len);
       strcat(l_temp1, text);
       l_ptr = l_ptr->below;
       if (l_ptr == End->below)
         break;
     }
E 2
I 2
	l_temp_line = malloc(sizeof(LINE));
D 3
	if (text == NULL) {
E 3
I 3
	if (l_temp_line == NULL) {
E 3
		*errnum = -1;
		strcpy(help_msg, "out of memory error");
		return;
	}
	(l_temp_line->len) = l_ttl;
	/* Add the new line to the buffer. */
	(l_temp_line->handle) = add_line(l_temp1, l_ttl);
D 4
	if (start == top) {
E 4
I 4
	if (Start == top) {
E 4
		top = l_temp_line;
		(l_temp_line->above) = NULL;
	} else {
D 4
		(l_temp_line->above) = start->above;
E 4
I 4
		(l_temp_line->above) = Start->above;
E 4
		u_add_stk(&(l_temp_line->above->below));
		(l_temp_line->above->below) = l_temp_line;
	}
D 4
	(l_temp_line->below) = start;
	u_add_stk(&(start->above));
	(start->above) = l_temp_line;
E 4
I 4
	(l_temp_line->below) = Start;
	u_add_stk(&(Start->above));
	(Start->above) = l_temp_line;
E 4
E 2

I 3
	sigspecial--;
	if (sigint_flag && (!sigspecial))
		goto mk;
E 3
D 2
  l_temp_line = (LINE *)malloc(sizeof(LINE));
  if (text == NULL)
    {
      *errnum = -1;
      strcpy(help_msg, "out of memory error");
      return;
    }
  (l_temp_line->len) = l_ttl;
  /* add the new line to the buffer */
  (l_temp_line->handle) = add_line(l_temp1, l_ttl);
  if (start == top)
    {
      top = l_temp_line;
      (l_temp_line->above) = NULL;
    }
  else
    {
      (l_temp_line->above) = start->above;
      u_add_stk(&(l_temp_line->above->below));
      (l_temp_line->above->below) = l_temp_line;
    }
  (l_temp_line->below) = start;
  u_add_stk(&(start->above));
  (start->above) = l_temp_line;
E 2
I 2
	ungetc(ss, inputt);
	/* Delete the lines used to make the joined line. */
I 3
	join_flag = 1;
E 3
	d(inputt, errnum);
I 3
	join_flag = 0;
E 3
	if (*errnum < 0)
		return;
	*errnum = 0;
I 3
mk:
E 3
	current = l_temp_line;
E 2

D 2
  ungetc(ss, inputt);
  /* delete the lines used to make the joined line */
  d(inputt, errnum);
  if (*errnum < 0)
    return;
  *errnum = 0;
  current = l_temp_line;
E 2
I 2
	*errnum = 1;
E 2

D 2
  *errnum = 1;

  point:
  u_set = 0;
  free(l_temp1);
} /* end-j */
E 2
I 2
point:	u_set = 0;
	free(l_temp1);
}
E 2
E 1
