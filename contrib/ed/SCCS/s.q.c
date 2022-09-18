h42532
s 00002/00002/00092
d D 8.1 93/05/31 14:29:50 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00093
d D 5.6 93/04/28 18:07:13 bostic 6 5
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00017/00011/00077
d D 5.5 93/03/18 12:17:34 bostic 5 4
c update from Rodney Ruddock
e
s 00002/00002/00086
d D 5.4 93/03/08 18:31:58 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00014/00001/00074
d D 5.3 93/02/28 15:28:59 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00048/00050/00027
d D 5.2 93/01/23 15:47:52 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00077/00000/00000
d D 5.1 93/01/23 11:13:20 bostic 1 0
c date and time created 93/01/23 11:13:20 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
#include <unistd.h>

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
 * End this editting session and exit with saving the buffer. If no
 * write has occurred since the last buffer modification a warning
 * is given once ('Q' over-rides the warning).
 */
D 2

E 2
void
q(inputt, errnum)
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
  int l_which; /* which is it? 'q' or 'Q' */
  register int l_ss=ss;
E 2
I 2
	register int l_ss = ss;
	int l_which;			/* Which is it? 'q' or 'Q'. */
E 2

I 3
	sigspecial = 1; /* yes, 1, because we want to ensure it's on */
	sigspecial2 = 0;

E 3
D 2
  l_which = ss;
E 2
I 2
	l_which = ss;
D 5
	for (;;) {
		l_ss = getc(inputt);
		if ((l_ss != ' ') && (l_ss != '\n') && (l_ss != EOF)) {
			*errnum = -1;
			strcpy(help_msg, "illegal command option");
			return;
E 5
I 5
	if (ss != -1) {
		for (;;) {
			l_ss = getc(inputt);
			if ((l_ss != ' ') && (l_ss != '\n') && (l_ss != EOF)) {
				*errnum = -1;
				strcpy(help_msg, "illegal command option");
				return;
			}
			if ((l_ss == '\n') || (l_ss == EOF))
				break;
E 5
		}
D 5
		if ((l_ss == '\n') || (l_ss == EOF))
			break;
	}
E 5
E 2

D 2
  while (1)
     {
       l_ss = getc(inputt);
       if ((l_ss != ' ') && (l_ss != '\n') && (l_ss != EOF))
         {
           *errnum = -1;
           strcpy(help_msg, "illegal command option");
           return;
         }
       if ((l_ss == '\n') || (l_ss == EOF))
         break;
     }
E 2
I 2
D 5
	ungetc(l_ss, inputt);
E 5
I 5
		ungetc(l_ss, inputt);
	}
E 5
	/* Note: 'Q' will bypass this if stmt., which warns of no save. */
D 5
	if ((change_flag == 1L) && (l_which == 'q')) {
E 5
I 5
	if ((change_flag == 1L) && ((l_which == 'q') || (l_which == -1)) ) {
E 5
		change_flag = 0L;
		strcpy(help_msg, "buffer changes not saved");
		*errnum = -1;
		ss = l_ss;
I 5
		if (l_which == EOF)
			ungetc('\n', inputt);
E 5
		return;
	}
	/* Do cleanup; should it be even bothered?? */
D 4
	start = top;
E 4
I 4
	Start = top;
E 4
	End = bottom;
D 4
	start_default = End_default = 0;
E 4
I 4
	Start_default = End_default = 0;
E 4
E 2

D 2
  ungetc(l_ss, inputt);
  /* note: 'Q' will bypass this if stmt., which warns of no save */
  if ((change_flag == 1L) && (l_which == 'q'))
    {
      change_flag = 0L;
      strcpy(help_msg, "buffer changes not saved");
      *errnum = -1;
      ss = l_ss;
      return;
    }

  /* do cleanup; should it be even bothered?? */
  start = top;
  End = bottom;
  start_default = End_default = 0;
  d(inputt, errnum); /* we don't care about the returned errnum val anymore */
  u_clr_stk();
  free(text);
  free(filename_current); 
#ifdef STDIO

  fclose(fhtmp);
  unlink(template);
#endif
#ifdef DBI
  (dbhtmp->close)(dbhtmp); /* overhead as the cache is flushed */
  unlink(template);
#endif
  exit(0);
} /* end-q */
E 2
I 2
	/* We don't care about the returned errnum val anymore. */
I 5
	if (l_which == EOF)
		ungetc('\n', inputt);
E 5
	d(inputt, errnum);
	u_clr_stk();
	free(text);
	free(filename_current);
I 3
#ifdef STDIO
	fclose(fhtmp);
#endif
#ifdef DBI
E 3
	(dbhtmp->close) (dbhtmp);	/* Overhead as the cache is flushed. */
I 3
#endif
#ifndef MEMORY
E 3
	unlink(template);
I 3
#endif
E 3
D 6
	exit(0);
E 6
I 6
	exit(exit_code);
E 6
}
E 2
E 1
