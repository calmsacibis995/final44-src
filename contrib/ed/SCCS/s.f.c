h04910
s 00002/00002/00082
d D 8.1 93/05/31 14:29:05 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00059
d D 5.4 93/04/28 18:07:07 bostic 4 3
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00011/00007/00048
d D 5.3 93/02/28 15:28:48 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00032/00025/00023
d D 5.2 93/01/23 15:47:40 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00048/00000/00000
d D 5.1 93/01/23 11:13:07 bostic 1 0
c date and time created 93/01/23 11:13:07 by bostic
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

I 4
#include <limits.h>
E 4
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
 * Prints out or sets the remembered filename.
 */
D 2

E 2
void
f(inputt, errnum)
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
  char *l_temp;
E 2
I 2
	char *l_temp;
E 2

D 2
  l_temp = filename(inputt, errnum);
  if (sigint_flag)
     SIGINT_ACTION;
  if (*errnum == 1)
    {
      free(filename_current);
      filename_current = l_temp;
    }
  else if (*errnum == -2)
    while (((ss = getc(inputt)) != '\n') || (ss == EOF))
         ;
  else if (*errnum < 0)
      return;
  if (sigint_flag)
     SIGINT_ACTION;
  fwrite(filename_current, sizeof(char), strlen(filename_current), stdout);
  putchar('\n');
  *errnum = 1;
} /* end-f */
E 2
I 2
	l_temp = filename(inputt, errnum);
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
	if (*errnum == 1) {
I 3
		sigspecial++;
I 4
			/* user wants the name from a sh command */
		if (l_temp && l_temp[FILENAME_LEN+1]) {
			FILE   *namestream, *popen();
			int l_len;

			if (l_temp[0] == '\0') {
				strcpy(help_msg, "no command given");
				*errnum = -1;
				return;
			}
			if (((namestream = popen(l_temp, "r")) == NULL) ||
			    ((fgets(l_temp, FILENAME_LEN - 1, namestream)) == NULL)) {
				strcpy(help_msg, "error executing command");
				*errnum = -1;
				if (namestream != NULL)
					pclose(namestream);
				ungetc('\n', inputt);
				return;
			}
			l_len = strlen(l_temp) - 1;
			if (l_temp[l_len] == '\n')
				l_temp[l_len] = '\0';
			pclose(namestream);
		}
E 4
E 3
		free(filename_current);
		filename_current = l_temp;
I 3
		sigspecial--;
		if (sigint_flag && (!sigspecial))
			SIGINT_ACTION;
E 3
	} else
		if (*errnum == -2)
			while (((ss = getc(inputt)) != '\n') || (ss == EOF));
		else
			if (*errnum < 0)
				return;
D 3
	if (sigint_flag)
		SIGINT_ACTION;
	fwrite(filename_current,
	    sizeof(char), strlen(filename_current), stdout);
E 3
I 3
	if (filename_current)
		fwrite(filename_current,
		    sizeof(char), strlen(filename_current), stdout);
E 3
	putchar('\n');
	*errnum = 1;
}
E 2
E 1
