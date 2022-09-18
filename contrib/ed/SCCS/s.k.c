h27170
s 00002/00002/00112
d D 8.1 93/05/31 14:29:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00113
d D 5.4 93/03/08 18:31:54 ralph 4 3
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00007/00003/00107
d D 5.3 93/02/28 15:28:55 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00067/00071/00043
d D 5.2 93/01/23 15:47:47 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00114/00000/00000
d D 5.1 93/01/23 11:13:15 bostic 1 0
c date and time created 93/01/23 11:13:15 by bostic
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
 * This the mark command (k); see ed(1).
 */

void
set_mark(inputt, errnum)
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
  int l_mark;
E 2
I 2
	int l_mark;
E 2

D 2
  l_mark = getc(inputt);
  if (End_default == 1)
    End = current;
  if (End == NULL)
    {
      strcpy(help_msg, "bad address");
      *errnum = -1;
      ungetc('\n', inputt);
      return;
    }
  start_default = End_default = 0;
E 2
I 2
	l_mark = getc(inputt);
	if (End_default == 1)
		End = current;
	if (End == NULL) {
		strcpy(help_msg, "bad address");
		*errnum = -1;
		ungetc('\n', inputt);
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
  /* the marks have to be "a" to "z" (inclusive); that is, ye olde
   * portable character set (ASCII) lower case alphabet
   */
  if ((l_mark < 97) || (l_mark > 122) || (End == NULL))
    {
      strcpy(help_msg, "illegal mark character");
      *errnum = -1;
      return;
    }
  l_mark = l_mark - 97;
  (mark_matrix[l_mark].address) = End;
E 2
I 2
	/*
	 * The marks have to be "a" to "z" (inclusive); that is, ye olde
	 * portable character set (ASCII) lower case alphabet.
	 */
	if ((l_mark < 97) || (l_mark > 122) || (End == NULL)) {
		strcpy(help_msg, "illegal mark character");
		*errnum = -1;
		return;
	}
	l_mark = l_mark - 97;
	(mark_matrix[l_mark].address) = End;
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
  *errnum = 1;
} /* end-set_mark */
E 2
I 2
	*errnum = 1;
}
E 2


/*
 * This gets the address of a marked line.
 */
D 2

LINE
*get_mark(errnum)

int *errnum;

E 2
I 2
LINE *
D 3
get_mark(errnum)
E 3
I 3
get_mark(inputt, errnum)
	FILE *inputt;
E 3
	int *errnum;
E 2
{
D 2
  int l_mark;
E 2
I 2
	int l_mark;
E 2

D 2
  l_mark = getchar();
  /* ditto above comment */
  if ((l_mark < 97) || (l_mark > 122))
    {
      strcpy(help_msg, "illegal mark character");
      *errnum = -1;
      return(NULL);
    }
E 2
I 2
D 3
	l_mark = getchar();
E 3
I 3
	l_mark = getc(inputt);
E 3
	/* Ditto above comment. */
	if ((l_mark < 97) || (l_mark > 122)) {
		strcpy(help_msg, "illegal mark character");
		*errnum = -1;
		return (NULL);
	}
	l_mark = l_mark - 97;
	*errnum = 0;
	return (mark_matrix[l_mark].address);
}
E 2

D 2
  l_mark = l_mark - 97;
  *errnum = 0;
  return( mark_matrix[l_mark].address );
} /* end-get_mark */
E 2

D 2

E 2
/*
 * This is for the restoration of marks during an undo.
 */
D 2

E 2
void
ku_chk(begi, fini, val)
D 2

LINE *begi, *fini, *val;

E 2
I 2
	LINE *begi, *fini, *val;
E 2
{
D 2
  register int l_cnt;
  LINE *l_midd;
E 2
I 2
	register int l_cnt;
	LINE *l_midd;
E 2

D 2
  l_midd = begi;
  while (l_midd != NULL)
       {
         for (l_cnt=0; l_cnt<26; l_cnt++)
            if (mark_matrix[l_cnt].address == l_midd)
              {
                u_add_stk(&(mark_matrix[l_cnt].address));
                (mark_matrix[l_cnt].address) = val;
              }
         if (l_midd == fini)
           break;
         l_midd = l_midd->below;
       } /* end-while */
} /* end-ku_chk */
E 2
I 2
	l_midd = begi;
	while (l_midd != NULL) {
		for (l_cnt = 0; l_cnt < 26; l_cnt++)
			if (mark_matrix[l_cnt].address == l_midd) {
				u_add_stk(&(mark_matrix[l_cnt].address));
				(mark_matrix[l_cnt].address) = val;
			}
		if (l_midd == fini)
			break;
		l_midd = l_midd->below;
	}
}
E 2
E 1
