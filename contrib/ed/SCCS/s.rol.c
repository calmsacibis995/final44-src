h10907
s 00002/00002/00068
d D 8.1 93/05/31 14:29:59 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00066
d D 5.3 93/02/28 15:29:02 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00037/00030/00030
d D 5.2 93/01/23 15:47:55 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00060/00000/00000
d D 5.1 93/01/23 11:13:23 bostic 1 0
c date and time created 93/01/23 11:13:23 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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
 * After the command check the rest of the line to see nothing illegal
 * is following. Any single instance of a printsfx suffix is the only
 * legal thing to follow ( that is, a 'l', 'n', or 'p'). If a suffix
 * occurs the execution of that suffix occurs back in the cmd_loop
 * function after the command that called this function finishes
 * successfully.
 */
D 2

E 2
int
rol(inputt, errnum)
D 2

FILE *inputt;
int *errnum;

E 2
I 2
	FILE *inputt;
	int *errnum;
E 2
{
I 2
	ss = getc(inputt);
	printsfx = 0;
E 2

D 2
  ss = getc(inputt);
  printsfx = 0;
  /* only one of the suffix is allowed */
  if (ss == 'p')
    printsfx = 1;
  else if (ss == 'n')
    printsfx = 2;
  else if (ss == 'l')
    printsfx = 4;
  else
    ungetc(ss, inputt);
E 2
I 2
	/* Only one of the suffix is allowed. */
	if (ss == 'p')
		printsfx = 1;
	else
		if (ss == 'n')
			printsfx = 2;
		else
			if (ss == 'l')
				printsfx = 4;
			else
				ungetc(ss, inputt);
E 2

D 2
  while (1)
     {
       ss = getc(inputt);
       if ((ss != ' ') && (ss != '\n') && (ss != EOF))
         {
           *errnum = -1;
           strcpy(help_msg, "illegal command option");
           return(1);
         }
       if ((ss == '\n') || (ss == EOF))
         break;
     }
E 2
I 2
	for (;;) {
		ss = getc(inputt);
		if ((ss != ' ') && (ss != '\n') && (ss != EOF)) {
			*errnum = -1;
			strcpy(help_msg, "illegal command option");
			return (1);
		}
		if ((ss == '\n') || (ss == EOF))
			break;
	}
E 2

D 2
return(0); /* rest-of-line was okay */
} /* end-rol */
E 2
I 2
	/* Rest-of-line was okay. */
	return (0);
}
E 2
E 1
