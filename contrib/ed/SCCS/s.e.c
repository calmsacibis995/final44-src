h47380
s 00002/00002/00173
d D 8.1 93/05/31 14:28:50 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00013/00170
d D 5.8 93/05/31 13:57:39 bostic 8 7
c use btree access method, not recno access method, so garbage collection
c works -- from Rodney for 4.4BSD
e
s 00001/00000/00182
d D 5.7 93/05/11 12:07:36 bostic 7 6
c update from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00013/00000/00169
d D 5.6 93/04/28 18:07:03 bostic 6 5
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00004/00004/00165
d D 5.5 93/03/08 18:31:46 ralph 5 4
c changed start to Start and start_default to Start_default to
c avoid conflicts with start defined in crt0.o
e
s 00001/00000/00168
d D 5.4 93/03/01 16:56:26 bostic 4 3
c STDIO fix
e
s 00041/00007/00127
d D 5.3 93/02/28 15:28:33 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00096/00110/00038
d D 5.2 93/01/23 15:47:36 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00148/00000/00000
d D 5.1 93/01/23 11:13:03 bostic 1 0
c date and time created 93/01/23 11:13:03 by bostic
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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
#include <sys/stat.h>

D 3
#include <db.h>
E 3
#include <fcntl.h>
I 3
#include <limits.h>
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
 * Places a new file in the buffer to be editted. The current contents
 * of the buffer are deleted - no undo can be perfomed. A warning is
 * issued once if no write has occurred since the last buffer
 * modification (unless 'E' spec'd).
 */

void
e(inputt, errnum)
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
  int l_which;  /* which is it? 'e' or 'E' */
  char *l_temp;
E 2
I 2
	int l_which;		/* which is it? 'e' or 'E' */
	char *l_temp;
E 2

D 2
  l_which = ss;
E 2
I 2
	l_which = ss;
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
  *errnum = 0;
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
	*errnum = 0;
E 2

D 2
  /* note: 'E' will bypass this if stmt., which warns of no save */
  if ((change_flag == 1L) && (l_which == 'e'))
    {
      change_flag = 0L;
      strcpy(help_msg, "warning: buffer changes not saved");
      *errnum = -1;
      ungetc('\n', inputt);
      return;
    }
E 2
I 2
	/* Note: 'E' will bypass this if stmt., which warns of no save. */
	if ((change_flag == 1L) && (l_which == 'e')) {
		change_flag = 0L;
		strcpy(help_msg, "warning: buffer changes not saved");
		*errnum = -1;
		ungetc('\n', inputt);
		return;
	}
D 5
	start = top;
E 5
I 5
	Start = top;
E 5
	End = bottom;
D 5
	start_default = End_default = 0;
	if (start == NULL && bottom == NULL);
E 5
I 5
	Start_default = End_default = 0;
	if (Start == NULL && bottom == NULL);
E 5
	else {
		ungetc(ss, inputt);
		d(inputt, errnum);	/* delete the whole buffer */
	}
D 3
	if (sigint_flag)
		SIGINT_ACTION;
E 3
E 2

D 2
  start = top;
  End = bottom;
  start_default = End_default = 0;
  if (start == NULL && bottom == NULL)
    ;
  else
    {
      ungetc(ss, inputt);
      d(inputt, errnum);  /* delete the whole buffer */
    }
  if (sigint_flag)
    SIGINT_ACTION;
  u_clr_stk();  /* an 'e' clears all traces of last doc'mt, even in 'g' */
  if (*errnum  < 0)
    return;
  *errnum = 0;
#ifdef STDIO
  if (fhtmp > NULL)
    {
      fclose(fhtmp);
      unlink(template);
    }
#endif
#ifdef DBI
  if (dbhtmp != NULL)
    {
      (dbhtmp->close)(dbhtmp);
      unlink(template);
    }
#endif
E 2
I 2
	/* An 'e' clears all traces of last doc'mt, even in 'g'. */
	u_clr_stk();
	if (*errnum < 0)
		return;
	*errnum = 0;
I 3
#ifdef STDIO
	if (fhtmp > NULL) {
		fclose(fhtmp);
		unlink(template);
	}
#endif
#ifdef DBI
E 3
	if (dbhtmp != NULL) {
		(dbhtmp->close) (dbhtmp);
		unlink(template);
	}
I 3
#endif
E 3
E 2

D 2
  name_set = 1;
  e2(inputt, errnum);
  
  *errnum = 1;
} /* end-e */
E 2
I 2
	name_set = 1;
	e2(inputt, errnum);
E 2

I 2
	*errnum = 1;
}
E 2

D 2
 /* This is pulled out of e.c to make the "simulated 'e'" at startup
  * easier to handle.
  */

E 2
I 2
/*
 * This is pulled out of e.c to make the "simulated 'e'" at startup easier to
 * handle.
 */
E 2
void
e2(inputt, errnum)
D 2

FILE *inputt;
int *errnum;

E 2
I 2
	FILE *inputt;
	int *errnum;
E 2
{
I 3
	char *tmp_path;
D 8
#ifdef DBI
E 3
D 2
#ifdef DBI
  RECNOINFO l_dbaccess;
#endif
E 2
I 2
	RECNOINFO l_dbaccess;
I 3
#endif
E 8
E 3
E 2

I 3
	sigspecial++;
#ifndef MEMORY
E 3
D 2
  if (template == NULL)
    {
      template = (char *)calloc(FILENAME_LEN, sizeof(char));
      if (template == NULL)
        ed_exit(4);
    }
E 2
I 2
	if (template == NULL) {
		template = (char *) calloc(FILENAME_LEN, sizeof(char));
		if (template == NULL)
			ed_exit(4);
	}
	/* create the buffer using the method favored at compile time */
D 3
	bcopy("/tmp/_4.4bsd_ed_XXXXXX\0", template, 22);
E 3
I 3
	tmp_path = getenv("TMPDIR");
	sprintf(template, "%s/_4.4bsd_ed_XXXXXX", tmp_path ? tmp_path : "/tmp");
E 3
	mktemp(template);
I 3
#endif
#ifdef STDIO
	fhtmp = fopen(template, "w+");
	if (fhtmp == NULL) {
		ed_exit(5); /* unable to create buffer */
	}
I 4
	fwrite("R", sizeof(char), 1, fhtmp);
E 4
	file_seek = 0;
#endif
#ifdef DBI
I 6
D 8
/*
E 6
E 3
	(l_dbaccess.bval) = (u_char) '\0';
	(l_dbaccess.cachesize) = 0;
	(l_dbaccess.flags) = R_NOKEY;
	(l_dbaccess.lorder) = 0;
	(l_dbaccess.reclen) = 0;
E 8
I 8
	/* open using btree only, recno will mess things up
	 * because of garbage collection and how recno operates
	 * with delete.
	 */
E 8
	dbhtmp = dbopen(template, O_CREAT | O_RDWR,
D 8
	    S_IRUSR | S_IWUSR, (DBTYPE) DB_RECNO, &l_dbaccess);
I 6
*/
	dbhtmp = dbopen(template, O_CREAT | O_RDWR,
	    S_IRUSR | S_IWUSR, (DBTYPE) DB_RECNO, NULL);
E 8
I 8
	    S_IRUSR | S_IWUSR, (DBTYPE) DB_BTREE, NULL);
E 8
E 6
I 3
	if (dbhtmp == NULL) {
		ed_exit(5); /* unable to create buffer */
	}
#endif
E 3
	current = top;
D 5
	start = top;
E 5
I 5
	Start = top;
E 5
	End = bottom;
E 2

D 2
  /* create the buffer using the method favored at compile time */
  bcopy("/tmp/_4.4bsd_ed_XXXXXX\0", template, 22);
  mktemp(template);
#ifdef STDIO
  fhtmp = fopen(template, "w+");
  file_seek = 0;
#endif
#ifdef DBI
  (l_dbaccess.bval) = (u_char)'\0';
  (l_dbaccess.cachesize) = 0;
  (l_dbaccess.flags) = R_NOKEY;
  (l_dbaccess.lorder) = 0;
  (l_dbaccess.reclen) = 0;
  dbhtmp = dbopen(template, (O_CREAT | O_RDWR), (S_IRUSR | S_IWUSR), (DBTYPE)DB_RECNO, &l_dbaccess);
#endif
  current = top;
  start = top;
  End = bottom;

  if (sigint_flag)
    SIGINT_ACTION;
  if (name_set)
    {
      filename_flag = 1; /* so 'r' knows the filename is already read in */
      r(inputt, errnum);
    }
  change_flag = 0;
} /* end-e2 */
E 2
I 2
D 3
	if (sigint_flag)
E 3
I 3
	sigspecial--;
	if (sigint_flag &&(!sigspecial))
E 3
		SIGINT_ACTION;
I 3

	change_flag = 1;
E 3
	if (name_set) {
		/* So 'r' knows the filename is already read in. */
		filename_flag = 1;
		r(inputt, errnum);
I 6
		gut_num = line_number(bottom) + 512;
		if (gut == NULL) {
			gut = malloc(sizeof(LINE **) * gut_num);
			if (gut == NULL) {
				*errnum = -1;
				strcpy(help_msg, "out of memory error");
				return;
			}
		}
E 6
	}
	change_flag = 0;
I 7
	*errnum = 1;
E 7
}
E 2
E 1
