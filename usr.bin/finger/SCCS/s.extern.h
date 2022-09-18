h04822
s 00000/00001/00023
d D 8.2 95/04/28 17:35:53 bostic 5 4
c You may have already done the same (does the Alpha have alignment
c constraints? I think it does...).  I also changed it to use the libc
c err, instead of its own, and fixed most of the `gcc -Wall' complaints.
c The important changes are to memcpy the pointers from db->get and db->seq.
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00022
d D 8.1 93/06/06 14:38:47 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00024
d D 5.3 91/11/13 09:47:34 bostic 3 2
c multiple definition
e
s 00001/00002/00024
d D 5.2 91/07/27 17:59:12 bostic 2 1
c finger really didn't need its own hashing scheme
e
s 00026/00000/00000
d D 5.1 91/07/27 15:58:30 bostic 1 0
c date and time created 91/07/27 15:58:30 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
extern PERSON *htab[HSIZE];		/* The buckets. */
extern PERSON *phead, *ptail;		/* The linked list of all people. */
E 2
extern char tbuf[1024];			/* Temp buffer for anybody. */
extern int entries;			/* Number of people. */
I 2
extern DB *db;				/* Database. */
E 2

void	 enter_lastlog __P((PERSON *));
PERSON	*enter_person __P((struct passwd *));
void	 enter_where __P((struct utmp *, PERSON *));
D 5
void	 err __P((const char *, ...));
E 5
PERSON	*find_person __P((char *));
void	 lflag_print __P((void));
int	 match __P((struct passwd *, char *));
void	 netfinger __P((char *));
PERSON	*palloc __P((void));
char	*prphone __P((char *));
void	 sflag_print __P((void));
D 3
WHERE	*walloc __P((PERSON *));
E 3
E 1
