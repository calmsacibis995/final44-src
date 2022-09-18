h61670
s 00002/00002/00068
d D 8.1 93/05/31 14:28:56 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00066
d D 5.4 93/04/28 18:07:06 bostic 4 3
c corrections for echoing the last command when "!!" is given,
c undo working when 0 or 1 lines were in the buffer before the last buffer
c modification, a RE interpretation correction; from Rodney Ruddock
e
s 00012/00001/00058
d D 5.3 93/02/28 15:28:43 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00038/00037/00021
d D 5.2 93/01/23 15:47:37 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00058/00000/00000
d D 5.1 93/01/23 11:13:05 bostic 1 0
c date and time created 93/01/23 11:13:05 by bostic
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
D 2
 * If a SIGHUP is received then user contact is severed. Try, if
 * possible, to save the buffer. But be nice and don't save over
 * remembered filename (you can figure out why, can't you?).
 * The buffer is saved in a file named "ed.hup" in the directory that
 * ed was started-up in. If a write cannot be made to that directory (say
 * because it is read-only) then try writting "ed.hup" in the user's $HOME
 * direcory. Then exit.
E 2
I 2
 * If a SIGHUP is received then user contact is severed. Try, if possible,
 * to save the buffer. But be nice and don't save over remembered filename
 * (you can figure out why, can't you?).  The buffer is saved in a file
 * named "ed.hup" in the directory that ed was started-up in.  If a write
 * cannot be made to that directory (say because it is read-only) then try
 * writting "ed.hup" in the user's $HOME directory. Then exit.
E 2
 */
D 2

E 2
I 2
__dead void
E 2
do_hup()
D 2

E 2
{
D 2
  char l_filename[FILENAME_LEN], *l_temp;
  FILE *l_fp;
E 2
I 2
	char l_filename[FILENAME_LEN], *l_temp;
	FILE *l_fp;
E 2

I 3
	sigspecial++;
E 3
D 2
  if (change_flag == 0)
    exit(1); /* no need to save buffer contents */
  if ((l_fp = fopen("ed.hup", "w")) == NULL)
    {
      /* try writting ed.hup to the $HOME directory instead */
      l_temp = getenv("HOME");
      if ((l_temp == NULL) || ((strlen(l_temp)+7)>FILENAME_LEN))
        exit(1);
      strcpy(l_filename, l_temp);
      strcat(l_filename, "/ed.hup");
      if ((l_fp = fopen(l_filename, "w")) == NULL)
        exit(1); /* we tried... */
    }
  edwrite(l_fp, top, bottom);
  fclose(l_fp);
#ifdef STDIO
  fclose(fhtmp);
  unlink(template);
#endif
#ifdef DBI
  (dbhtmp->close)(dbhtmp);
  unlink(template);
#endif
  exit(1); /* hangup */

} /* end-do_hup */
E 2
I 2
	if (change_flag == 0)
D 4
		exit(1);		/* No need to save buffer contents. */
E 4
I 4
		exit(exit_code+2);		/* No need to save buffer contents. */
E 4
	if ((l_fp = fopen("ed.hup", "w")) == NULL) {
		/* Try writting ed.hup to the $HOME directory instead. */
		l_temp = getenv("HOME");
		if ((l_temp == NULL) || ((strlen(l_temp) + 7) > FILENAME_LEN))
D 4
			exit(1);
E 4
I 4
			exit(exit_code+2);
E 4
		strcpy(l_filename, l_temp);
		strcat(l_filename, "/ed.hup");
		if ((l_fp = fopen(l_filename, "w")) == NULL)
D 4
			exit(1);		/* We tried... */
E 4
I 4
			exit(exit_code+2);		/* We tried... */
E 4
	}
	edwrite(l_fp, top, bottom);
	fclose(l_fp);
I 3
#ifdef STDIO
	fclose(fhtmp);
	unlink(template);
#endif
#ifdef DBI
E 3
	(dbhtmp->close) (dbhtmp);
	unlink(template);
I 3
#endif
E 3
D 4
	exit(1);				/* Hangup */
E 4
I 4
	exit(exit_code+2);				/* Hangup */
E 4
}
E 2
E 1
