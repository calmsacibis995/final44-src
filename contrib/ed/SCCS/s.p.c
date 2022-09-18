h24920
s 00002/00002/00074
d D 8.1 93/05/31 14:29:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00068
d D 5.4 93/03/08 18:31:57 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00008/00007/00068
d D 5.3 93/02/28 15:28:59 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00047/00043/00028
d D 5.2 93/01/23 15:47:51 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00071/00000/00000
d D 5.1 93/01/23 11:13:19 bostic 1 0
c date and time created 93/01/23 11:13:19 by bostic
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
 * Both the n and p code are here because they're almost identical.
 * Print out the line. If it's n print the line number, tab, and then
 * the line.
 */
D 2

E 2
void
p(inputt, errnum, flag)
D 2

FILE *inputt;
int *errnum, flag;

E 2
I 2
	FILE *inputt;
	int *errnum, flag;
E 2
{
D 2
  int l_ln;
E 2
I 2
D 3
	int l_ln;
E 3
I 3
	int l_ln=0;
E 3
E 2

D 2
  if (start_default && End_default)
    start = End = current;
  else if (start_default)
    start = End;
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
	start_default = End_default = 0;
E 4
I 4
		if (Start_default)
			Start = End;
	Start_default = End_default = 0;
E 4
E 2

D 2
  if (start == NULL)
    {
      strcpy(help_msg, "bad address");
      *errnum = -1;
      return;
    }
E 2
I 2
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
		return;
	}
	if (rol(inputt, errnum))	/* For "command-suffix pairs". */
		return;
E 2

D 2
  if (rol(inputt, errnum))  /* for "command-suffix pairs" */
    return;
E 2
I 2
	if (flag == 1)
D 4
		l_ln = line_number(start);
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	current = start;
E 4
I 4
		l_ln = line_number(Start);
	current = Start;
E 4
	for (;;) {
		/* Print out the lines. */
D 3
		if (sigint_flag)
			SIGINT_ACTION;
E 3
		if (current == NULL)
			break;
		get_line(current->handle, current->len);
I 3
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
		if (flag == 1)		/* When 'n'. */
			printf("%d\t", l_ln++);
		fwrite(text, sizeof(char), current->len, stdout);
		putchar('\n');
		if (current == End)
			break;
		current = current->below;
	}
E 2

D 2
  if (flag == 1)
    l_ln = line_number(start);
  if (sigint_flag)
    SIGINT_ACTION;
  current = start;
  while (1)
       {
         /* print out the lines */
         if (sigint_flag)
           SIGINT_ACTION;
         if (current == NULL)
           break;
         get_line(current->handle, current->len);
         if (flag == 1) /* when 'n' */
           printf("%d\t", l_ln++);
         fwrite(text, sizeof(char), current->len, stdout);
         putchar('\n');
         if (current == End)
           break;
         current = current->below;
       } /* end-while */

  *errnum = 1;
} /* end-p */
E 2
I 2
	*errnum = 1;
}
E 2
E 1
