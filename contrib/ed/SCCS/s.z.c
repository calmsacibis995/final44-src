h41616
s 00002/00002/00099
d D 8.1 93/05/31 14:30:18 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00096
d D 5.5 93/03/08 18:32:01 ralph 5 4
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00007/00001/00094
d D 5.4 93/03/01 17:04:38 bostic 4 3
c new version from Rodney
e
s 00013/00012/00082
d D 5.3 93/02/28 15:29:07 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00067/00067/00027
d D 5.2 93/01/23 15:48:00 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00094/00000/00000
d D 5.1 93/01/23 11:13:28 bostic 1 0
c date and time created 93/01/23 11:13:28 by bostic
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
 * This prints out the next group of lines (as spec'd by the skicky
 * number; 22 by default). It's really useful for scrolling in chunks
 * through the buffer (better than l, n, or p). Shame on POSIX for
 * not including it; yaaa! BSD for keeping it! :-)
 */
D 2

E 2
void
z(inputt, errnum)
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
  register int l_cnt;
E 2
I 2
	register int l_cnt;
E 2

D 2
  if (current == NULL)
    {
      *errnum = -1;
      strcpy(help_msg, "no lines in buffer");
      return;
    }
  /* set zsnum if need be here */
  ss = getc(inputt);
  if ((ss > 48) && (ss < 57))
    zsnum = dig_num_conv(inputt, errnum);  /* default set in main */
  else if ((ss != '\n') && (ss != EOF))
    {
      ungetc(ss, inputt);
      if (rol(inputt, errnum))
        return;
    }
E 2
I 2
	if (current == NULL) {
		*errnum = -1;
D 3
		strcpy(help_msg, "no lines in buffer");
E 3
I 3
		strcpy(help_msg, "buffer empty");
E 3
		return;
	}
	/* Set zsnum if need be here. */
	ss = getc(inputt);
	if ((ss > 48) && (ss < 57))
		/* Default set in main. */
		zsnum = dig_num_conv(inputt, errnum);
	else
		if ((ss != '\n') && (ss != EOF)) {
			ungetc(ss, inputt);
			if (rol(inputt, errnum))
				return;
		}
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
I 3
D 4
	if (start == NULL) {
E 4
I 4
	if (top == NULL) {
E 4
		strcpy(help_msg, "buffer empty");
		*errnum = -1;
		ungetc('\n', inputt);
		return;
	}
E 3
	if (End_default) {
		if ((current->below) != NULL)
D 5
			start = current->below;
E 5
I 5
			Start = current->below;
E 5
		else {
			strcpy(help_msg, "at end of buffer");
			*errnum = -1;
			ungetc('\n', inputt);
			return;
		}
	} else
D 5
		start = End;
I 4
	if (start == NULL) {
E 5
I 5
		Start = End;
	if (Start == NULL) {
E 5
		strcpy(help_msg, "bad address");
		*errnum = -1;
		ungetc('\n', inputt);
		return;
	}
E 4
D 3
	if (start == NULL) {
		strcpy(help_msg, "bad address");
		*errnum = -1;
		ungetc('\n', inputt);
		return;
	}
E 3
D 5
	start_default = End_default = 0;
E 5
I 5
	Start_default = End_default = 0;
E 5
E 2

D 2
  if (sigint_flag)
    SIGINT_ACTION;
  if (End_default)
    {
      if ((current->below) != NULL)
        start = current->below;
      else
        {
          strcpy(help_msg, "at end of buffer");
          *errnum = -1;
          ungetc('\n', inputt);
          return;
        }
    }
  else
    start = End;
  if (start == NULL)
    {
      strcpy(help_msg, "bad address");
      *errnum = -1;
      ungetc('\n', inputt);
      return;
    }
  start_default = End_default = 0;

  current = start;
  l_cnt = 1;  /* yes, set to = 1 */
  while (1)
     {
       /* scroll-out the next 'zsnum' of lines or until bottom */
       if (sigint_flag)
         SIGINT_ACTION;
       if (current == NULL)
         break;
       get_line(current->handle, current->len);
       printf("%s\n", text);
       if (current == bottom)
         break;
       l_cnt++;
       if (zsnum < l_cnt)
         break;
       current = current->below;
     } /* end-while */
  *errnum = 1;
} /* end-z */
E 2
I 2
D 5
	current = start;
E 5
I 5
	current = Start;
E 5
	l_cnt = 1;		/* Yes, set to = 1. */
	while (1) {
		/* Scroll-out the next 'zsnum' of lines or until bottom. */
D 3
		if (sigint_flag)
			SIGINT_ACTION;
E 3
		if (current == NULL)
			break;
I 3
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
		get_line(current->handle, current->len);
		printf("%s\n", text);
		if (current == bottom)
			break;
		l_cnt++;
		if (zsnum < l_cnt)
			break;
		current = current->below;
	}
	*errnum = 1;
}
E 2
E 1
