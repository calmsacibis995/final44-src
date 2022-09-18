h34582
s 00002/00002/00108
d D 8.1 93/05/31 14:29:08 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00109
d D 5.7 93/05/11 12:07:47 bostic 7 6
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00001/00001/00109
d D 5.6 93/04/28 18:17:35 bostic 6 5
c l_len isn't used
e
s 00009/00030/00101
d D 5.5 93/04/28 18:07:08 bostic 5 4
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00001/00001/00130
d D 5.4 93/02/28 15:43:32 bostic 4 3
c lint
e
s 00019/00007/00112
d D 5.3 93/02/28 15:28:49 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00094/00095/00025
d D 5.2 93/01/23 15:47:41 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00120/00000/00000
d D 5.1 93/01/23 11:13:08 bostic 1 0
c date and time created 93/01/23 11:13:08 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
I 3
#include <limits.h>
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

I 3

E 3
/*
 * A central function for any command that has to deal with a filename
 * (to be or not to be remembered).
 */
D 2

char
*filename(inputt, errnum)

FILE *inputt;
int *errnum;

E 2
I 2
char *
filename(inputt, errnum)
	FILE *inputt;
	int *errnum;
E 2
{
D 2
  char *l_fname;
  register int l_cnt=0;
  int l_esc=0, l_bang_flag=0, l_len;
E 2
I 2
	register int l_cnt = 0;
	char *l_fname;
D 6
	int l_esc = 0, l_bang_flag = 0, l_len;
E 6
I 6
	int l_esc = 0, l_bang_flag = 0;
E 6
E 2

D 2
  l_fname = (char *)calloc(FILENAME_LEN, sizeof(char));
  if (l_fname == NULL)
    {
      *errnum = -1;
      strcpy(help_msg, "out of memory error");
      return(NULL);
    }
E 2
I 2
D 5
	l_fname = calloc(FILENAME_LEN, sizeof(char));
E 5
I 5
	l_fname = calloc(FILENAME_LEN+2, sizeof(char));
E 5
	if (l_fname == NULL) {
		*errnum = -1;
		strcpy(help_msg, "out of memory error");
		return (NULL);
	}
	if ((ss = getc(inputt)) != ' ') {
		if (ss == '\n') {
			ungetc(ss, inputt);
			/*
			 * It's not really an error, but to flag remembered
			 * filename is to be used.
			 */
			*errnum = -2;
		} else {
			*errnum = -1;
			strcpy(help_msg,
			    "space required before filename given");
		}
		return (NULL);
	}
	while (ss = getc(inputt))
		if (ss != ' ') {
			ungetc(ss, inputt);
			break;
		}
	for (;;) {
		ss = getc(inputt);
		if ((ss == '\\') && (l_esc == 0)) {
			ss = getchar();
			l_esc = 1;
		} else
			l_esc = 0;
		if ((ss == '\n') || (ss == EOF)) {
			l_fname[l_cnt] = '\0';
			break;
		} else
D 7
			if ((ss == '!') && (l_esc == 0))
E 7
I 7
			if ((ss == '!') && (l_esc == 0) && (l_cnt < 2))
E 7
				l_bang_flag = 1;
			else
D 3
				if (ss != ' ')
E 3
I 3
				if ((ss != ' ') || (l_bang_flag))
E 3
					l_fname[l_cnt++] = ss;
D 3
				else
					continue;
E 3
I 3
				else {
					*errnum = -1;
D 4
					return;
E 4
I 4
					return (NULL);
E 4
				}
E 3
E 2

D 2
  if ((ss = getc(inputt)) != ' ')
    {
      if (ss == '\n')
        {
          ungetc(ss, inputt);
          *errnum = -2; /* it's not really an error, but to flag remembered filename is to be used */
        }
      else
        {
          *errnum = -1;
          strcpy(help_msg, "space required before filename given");
        }
      return(NULL);
    }
  while (ss = getc(inputt))
       if (ss != ' ')
         {
           ungetc(ss, inputt);
           break;
         }
  while (1)
       {
         ss = getc(inputt);
         if ((ss == '\\') && (l_esc == 0))
           {
             ss = getchar();
             l_esc = 1;
           } 
         else
           l_esc = 0;
         if ((ss == '\n') || (ss == EOF))
           {
             l_fname[l_cnt] = '\0';
             break;
           }
         else if ((ss == '!') && (l_esc == 0))
             l_bang_flag = 1;
         else if (ss != ' ')
           l_fname[l_cnt++] = ss;
         else
           continue;
E 2
I 2
		if (l_cnt >= FILENAME_LEN) {
			strcpy(help_msg, "filename+path length too long");
			*errnum = -1;
			ungetc('\n', inputt);
			return (NULL);
		}
	}
E 2

D 2
         if (l_cnt >= FILENAME_LEN)
           {
             strcpy(help_msg, "filename+path length too long");
             *errnum = -1;
             ungetc('\n', inputt);
             return(NULL);
           }
       } /* end-while(1) */
E 2
I 2
D 5
	if (l_bang_flag == 1) {	/* user wants the name from a sh command */
		FILE   *namestream, *popen();
E 2

D 2
  if (l_bang_flag == 1) /* user wants the name from a sh command */
    {
      FILE *namestream, *popen();

      if (l_fname[0] == '\0')
        {
          strcpy(help_msg, "no command given");
          *errnum = -1;
          return(NULL);
        }
      if (((namestream = popen(l_fname, "r")) == NULL) || ((fgets(l_fname, FILENAME_LEN-1, namestream)) == NULL))
        {
          strcpy(help_msg, "error executing command");
          *errnum = -1;
          if (namestream != NULL)
            pclose(namestream);
          return(NULL);
        }
      l_len = strlen(l_fname) - 1;
      if (l_fname[l_len] == '\n')
        l_fname[l_len] = '\0';
      pclose(namestream);
    }
  else if (l_fname[0] == '\0')
    strcpy(l_fname, filename_current);
  else
    *errnum = 1;
  return(l_fname);
} /* end-filename */
E 2
I 2
		if (l_fname[0] == '\0') {
			strcpy(help_msg, "no command given");
			*errnum = -1;
			return (NULL);
		}
		if (((namestream = popen(l_fname, "r")) == NULL) ||
		    ((fgets(l_fname, FILENAME_LEN - 1, namestream)) == NULL)) {
			strcpy(help_msg, "error executing command");
			*errnum = -1;
			if (namestream != NULL)
				pclose(namestream);
I 3
			ungetc('\n', inputt);
E 3
			return (NULL);
		}
		l_len = strlen(l_fname) - 1;
		if (l_fname[l_len] == '\n')
			l_fname[l_len] = '\0';
		pclose(namestream);
	} else
D 3
		if (l_fname[0] == '\0')
E 3
I 3
		if (l_fname[0] == '\0') {
			sigspecial++;
E 3
			strcpy(l_fname, filename_current);
D 3
		else
			*errnum = 1;
E 3
I 3
			sigspecial--;
			if (sigint_flag && (!sigspecial))
				SIGINT_ACTION;
		}
E 5
I 5
	if (l_fname[0] == '\0') {
		sigspecial++;
		strcpy(l_fname, filename_current);
		sigspecial--;
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
	}
E 5
	*errnum = 1;
I 5
	l_fname[FILENAME_LEN+1] = l_bang_flag;
E 5
E 3
	return (l_fname);
}
E 2
E 1
