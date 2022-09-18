h62412
s 00002/00002/00105
d D 8.1 93/05/31 14:29:20 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00106
d D 5.4 93/04/28 18:24:40 bostic 4 3
c bcopy -> memmove
e
s 00004/00002/00103
d D 5.3 93/02/28 15:28:52 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00080/00082/00025
d D 5.2 93/01/23 15:47:43 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00107/00000/00000
d D 5.1 93/01/23 11:13:11 bostic 1 0
c date and time created 93/01/23 11:13:11 by bostic
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
 * This is for getting RE and replacement patterns for any command
 * that uses RE's and replacements.
 */
D 2

char
*get_pattern(delim, inputt, errnum, flag)

int delim;
FILE *inputt;
int *errnum, flag;

E 2
I 2
char *
get_pattern(delim, inputt, errnum, flag)
	int delim, *errnum, flag;
	FILE *inputt;
E 2
{
D 2
  int l_cnt=1;
  static int l_max=510;
  char *l_pat, *l_pat_tmp;
E 2
I 2
	static int l_max = 510;
	int l_cnt = 1;
	char *l_pat, *l_pat_tmp;
E 2

D 2
  /* get a "reasonable amount of space for the RE */
  l_pat = (char *)calloc(l_max+2, sizeof(char));
  if (l_pat == NULL)
    {
      *errnum = -3;
      strcpy(help_msg, "out of memory error");
      return(NULL);
    }
  l_pat[0] = delim;
E 2
I 2
	/* get a "reasonable amount of space for the RE */
	l_pat = calloc(l_max + 2, sizeof(char));
	if (l_pat == NULL) {
		*errnum = -3;
		strcpy(help_msg, "out of memory error");
		return (NULL);
	}
	l_pat[0] = delim;
E 2

D 2
  if ((delim == ' ') || (delim == '\n'))
    {
      if (delim == '\n')
        ungetc(delim, inputt);
      strcpy(help_msg, "illegal delimiter");
      *errnum = -2;
      return(l_pat);
    }
  
  while (1)
       {
         ss = getc(inputt);
         if (ss == '\\')
           {
             ss = getc(inputt);
             if ((ss == delim) || ((flag == 1) && (ss == '\n')))
                 l_pat[l_cnt] = ss;
             else
               {
                 l_pat[l_cnt] = '\\';
                 /*ungetc(ss, inputt);*/
                 l_pat[++l_cnt] = ss;
               }
             goto leap;
           }
         else if ((ss == '\n') || (ss == EOF))
           {
             ungetc(ss, inputt);
             strcpy(help_msg, "no closing delimiter found");
             *errnum = -1;
             l_pat[l_cnt] = '\0'; /* this is done for 's's backward compat. */
             return(l_pat);
           }
         if (ss == delim)
           break;
E 2
I 2
	if ((delim == ' ') || (delim == '\n')) {
		if (delim == '\n')
			ungetc(delim, inputt);
		strcpy(help_msg, "illegal delimiter");
		*errnum = -2;
		return (l_pat);
	}
	for (;;) {
		ss = getc(inputt);
		if (ss == '\\') {
			ss = getc(inputt);
			if ((ss == delim) || ((flag == 1) && (ss == '\n')))
				l_pat[l_cnt] = ss;
			else {
				l_pat[l_cnt] = '\\';
D 3
				/* ungetc(ss, inputt); */
E 3
				l_pat[++l_cnt] = ss;
			}
			goto leap;
		} else
			if ((ss == '\n') || (ss == EOF)) {
				ungetc(ss, inputt);
				strcpy(help_msg, "no closing delimiter found");
				*errnum = -1;
				/* This is done for s's backward compat. */
				l_pat[l_cnt] = '\0';
				return (l_pat);
			}
		if (ss == delim)
			break;
E 2

D 2
         l_pat[l_cnt] = ss;
E 2
I 2
		l_pat[l_cnt] = ss;
E 2

D 2
leap:
         if (l_cnt > l_max)
           {
             /* the RE is really long; get more space for it */
             l_max = l_max + 256;
             l_pat_tmp = l_pat;
             l_pat = (char *)calloc(l_max+2, sizeof(char));
             if (l_pat == NULL)
               {
                 *errnum = -3;
                 strcpy(help_msg, "out of memory error");
                 return(NULL);
               }
             bcopy(l_pat_tmp, l_pat, l_cnt);
             free(l_pat_tmp);
           }
         l_cnt++;
       }
  l_pat[l_cnt] = '\0';
  *errnum = 0;
  /* send back the pattern. l_pat[0] has the delimiter in it so the RE
   * really starts at l_pat[1]. It's done this way for the special forms
   * of 's' (substitute).
   */
  return(l_pat);
} /* end-get_pattern */
E 2
I 2
leap:		if (l_cnt > l_max) {
			/* The RE is really long; get more space for it. */
			l_max = l_max + 256;
			l_pat_tmp = l_pat;
			l_pat = calloc(l_max + 2, sizeof(char));
			if (l_pat == NULL) {
				*errnum = -3;
				strcpy(help_msg, "out of memory error");
				return (NULL);
			}
D 4
			bcopy(l_pat_tmp, l_pat, l_cnt);
E 4
I 4
			memmove(l_pat, l_pat_tmp, l_cnt);
E 4
			free(l_pat_tmp);
		}
		l_cnt++;
	}
	l_pat[l_cnt] = '\0';
	*errnum = 0;
	/*
	 * Send back the pattern.  l_pat[0] has the delimiter in it so the RE
	 * really starts at l_pat[1]. It's done this way for the special forms
	 * of 's' (substitute).
	 */
	return (l_pat);
}
E 2
E 1
