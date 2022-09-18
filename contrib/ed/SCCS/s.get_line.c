h46000
s 00002/00002/00107
d D 8.1 93/05/31 14:29:17 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00108
d D 5.4 93/04/28 18:24:23 bostic 4 3
c bcopy -> memmove
e
s 00048/00001/00061
d D 5.3 93/02/28 15:28:51 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00018/00037/00044
d D 5.2 93/01/23 15:47:43 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00081/00000/00000
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
 * Get the specified line from the buffer. Note that in the buffer
 * we stored lengths of text, not strings (NULL terminated, except
 * under MEMORY). So we want to put a terminating NULL in for
 * whatever command is going to be handling the line.
 */

/* these variables are here (instead of main and ed.h) because they
 * are only used with the buffer when run under STDIO. STDIO is a
 * resource pig with most of the OS's I've tested this with. The
 * use of these variables improves performance up to 100% in several
 * cases. The piggyness is thus: fseek causes the current STDIO buf
 * to be flushed out and a new one read in...even when it is not necessary!
 * Read 512 (or 1024) when you don't have to for almost every access
 * and you'll slow down too. So these variable are used to control unneeded
 * fseeks.
 * I've been told the newer BSD STDIO has fixed this, but don't
 * currently have a copy.
 */
D 2

E 2
int file_loc=0;
D 2
extern int file_loc;
E 2

/* Get a particular line of length len from ed's buffer and place it in
 * 'text', the standard repository for the "current" line.
 */
D 2

E 2
void
get_line(loc, len)
I 3
#ifdef STDIO
	long loc;
#endif
#ifdef DBI
E 3
D 2

#ifdef STDIO
long loc;
#endif
#ifdef DBI
recno_t loc;
#endif
#ifdef MEMORY
char *loc;
#endif
int len;

E 2
I 2
	recno_t loc;
I 3
#endif
#ifdef MEMORY
	char *loc;
#endif
E 3
	int len;
E 2
{
I 3
#ifdef DBI
E 3
D 2
#ifdef STDIO
E 2
I 2
	DBT db_key, db_data;
I 3
#endif
	int l_jmp_flag;
E 3
E 2

I 3
	if (l_jmp_flag = setjmp(ctrl_position2)) {
		text[0] = '\0';
		return;
	}

	sigspecial2 = 1;
#ifdef STDIO

	if (loc == 0L) {
		text[0] = '\0';
		return;
	}
	if (file_loc != loc)
		fseek(fhtmp, loc, 0);
	file_seek = 1;
	file_loc = loc + fread(text, sizeof(char), len, fhtmp);
#endif

#ifdef DBI
	if (loc == (recno_t)0) {
		text[0] = '\0';
		return;
	}
E 3
D 2
  if (file_loc != loc)
    fseek(fhtmp, loc, 0);
  file_seek = 1;
  file_loc = loc + fread(text, sizeof(char), len, fhtmp);
#endif

#ifdef DBI
  DBT db_key, db_data;

  (db_key.data) = &loc;
  (db_key.size) = sizeof(recno_t);
  (dbhtmp->get)(dbhtmp, &db_key, &db_data, (u_int)0);
  strcpy(text, db_data.data);
#endif

#ifdef MEMORY
  tmp = (char *)loc;
  bcopy(loc, text, len);
#endif
  text[len] = '\0';
} /* end-get_line */
E 2
I 2
	(db_key.data) = &loc;
	(db_key.size) = sizeof(recno_t);
	(dbhtmp->get) (dbhtmp, &db_key, &db_data, (u_int) 0);
	strcpy(text, db_data.data);
I 3
#endif

#ifdef MEMORY
        if (loc == (char *)NULL) {
                text[0] = '\0';
                return;
        }
D 4
	bcopy(loc, text, len);
E 4
I 4
	memmove(text, loc, len);
E 4
#endif
E 3
	text[len] = '\0';
I 3
	sigspecial2 = 0;
E 3
}
E 2
E 1
