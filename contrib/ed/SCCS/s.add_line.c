h07135
s 00002/00002/00089
d D 8.1 93/05/31 14:28:32 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00090
d D 5.6 93/04/28 18:23:57 bostic 6 5
c bcopy -> memmove
e
s 00006/00015/00085
d D 5.5 93/03/18 12:17:28 bostic 5 4
c update from Rodney Ruddock
e
s 00005/00002/00095
d D 5.4 93/03/02 08:53:41 bostic 4 3
c longjmp fix from Rodney
e
s 00056/00002/00041
d D 5.3 93/02/28 15:28:25 bostic 3 2
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00021/00057/00022
d D 5.2 93/01/23 15:47:32 bostic 2 1
c reformat to KNF, prototype the world, fix lint bugs
e
s 00079/00000/00000
d D 5.1 93/01/23 11:12:58 bostic 1 0
c date and time created 93/01/23 11:12:58 by bostic
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
 * This is where the lines actually are put into the buffer. Notice
 * all the #ifdef's for the various methods of buffering - POSIX said
 * no "no attempt is made to imply a specific implementation". So,
 * you get your choice: standard I/O, core memory, or a database.
E 2
I 2
 * This is where the lines actually are put into the buffer.
E 2
 */
I 3
#ifdef STDIO
long
add_line(p, len)
	char *p;
	long len;
{
	extern int file_loc;
	long l_key;
D 5
	int l_jmp_flag;
E 5

D 5
	if (l_jmp_flag = setjmp(ctrl_position2))
		return (0);
	sigspecial2 = 1;
E 5
I 5
	sigspecial++;
E 5
	if (file_seek)  /* x-ref to get_line for what this does */ {
		file_seek = 0;
		fseek(fhtmp, 0L, 2); /* set to end-to-file */
	}
	l_key = ftell(fhtmp);
D 4
					/* keeps user time down 20%approx */
E 4
I 4
					/* keeps user time down 20% approx. */
E 4
	file_loc = l_key + fwrite(p, sizeof(char), len, fhtmp);
I 4
D 5
	sigspecial2 = 0;
E 5
I 5
	sigspecial--;
E 5
E 4
	return (l_key);
}
#endif

#ifdef DBI
E 3
D 2

#ifdef STDIO
long
add_line(p, len)
#endif
#ifdef DBI
E 2
recno_t
add_line(p, len)
D 2
#endif
#ifdef MEMORY
char
*add_line(p, len)
#endif

char *p;
long len;

E 2
I 2
	char *p;
	long len;
E 2
{
D 2
#ifdef STDIO
  long l_key;
  extern int file_loc;
E 2
I 2
	DBT db_key, db_data;
D 4
	static recno_t l_key;
E 4
I 4
	static recno_t l_key=0;
E 4
I 3
D 5
	int l_jmp_flag;
E 5
E 3
E 2

I 3
D 5
	if (l_jmp_flag = setjmp(ctrl_position2))
		return ((recno_t)0);
	sigspecial2 = 1;
E 5
I 5
	sigspecial++;
E 5
E 3
D 2
  if (file_seek)  /* x-ref to get_line for what this does */
    {
      file_seek = 0;
      fseek(fhtmp, 0L, 2); /* set to end-to-file */
    }
  l_key = ftell(fhtmp);
  file_loc = l_key + fwrite(p, sizeof(char), len, fhtmp); /* keeps user time down 20%approx */
  return(l_key);
#endif

#ifdef DBI
  DBT db_key, db_data;
  static recno_t l_key=0;

  l_key++;
  (db_key.data) = &l_key;
  (db_key.size) = sizeof(recno_t);
  (db_data.data) = p;
  (db_data.size) = len;
  (dbhtmp->put)(dbhtmp, &db_key, &db_data, (u_int)(R_NOOVERWRITE));
  return(l_key);
#endif

#ifdef MEMORY
  char *tmp;
  tmp = (char *)calloc(len+1, sizeof(char));
  if (tmp)
    {
      bcopy(p, tmp, len);
      tmp[len] = '\0';
    }
  return(tmp);
#endif

} /* end-add_line */
E 2
I 2
	l_key++;
	(db_key.data) = &l_key;
	(db_key.size) = sizeof(recno_t);
	(db_data.data) = p;
	(db_data.size) = len;
	(dbhtmp->put)(dbhtmp, &db_key, &db_data, (u_int)(R_NOOVERWRITE));
I 4
D 5
	sigspecial2 = 0;
E 5
I 5
	sigspecial--;
E 5
E 4
D 3
	return(l_key);
E 3
I 3
	return (l_key);
E 3
}
I 3
#endif

#ifdef MEMORY
char *
add_line(p, len)
	char *p;
	long len;
{
	char *tmp;
D 5
	int l_jmp_flag;
E 5

D 5
	if (l_jmp_flag = setjmp(ctrl_position2))
		return (NULL);
	sigspecial2 = 1;
E 5
I 5
	sigspecial++;
E 5
	tmp = (char *)calloc(len+1, sizeof(char));
	if (tmp) {
D 6
		bcopy(p, tmp, len);
E 6
I 6
		memmove(tmp, p, len);
E 6
		tmp[len] = '\0';
	}
I 4
D 5
	sigspecial2 = 0;
E 5
I 5
	sigspecial--;
E 5
E 4
	return (tmp);
}
#endif
E 3
E 2
E 1
