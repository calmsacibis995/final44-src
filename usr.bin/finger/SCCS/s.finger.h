h04939
s 00002/00002/00035
d D 8.1 93/06/06 14:39:08 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00013/00035
d D 5.7 91/07/27 17:59:16 bostic 7 6
c finger really didn't need its own hashing scheme
e
s 00001/00012/00047
d D 5.6 91/07/27 15:58:23 bostic 6 5
c Welcome to the Wonderful World of ANSI!
e
s 00001/00011/00058
d D 5.5 90/06/01 16:49:32 bostic 5 4
c new copyright notice
e
s 00000/00000/00069
d D 5.4 90/02/07 08:25:15 bostic 4 3
x 3
c exclude sccs changes to remove contrib line from copyright
e
s 00000/00003/00066
d D 5.3 89/05/08 11:36:02 bostic 3 2
c clean up copyright notice
e
s 00030/00006/00039
d D 5.2 89/05/07 01:02:53 edward 2 1
c show last login time if more recent than current logins,
c cleaned up, speeded up, put people in hash table, separate login info
c from personal info
e
s 00045/00000/00000
d D 5.1 89/05/06 13:53:30 bostic 1 0
c Tony Nardo (trn@warper.jhuapl.edu) reworked the original, I
c redid his stuff; should handle multiple logons right.
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 3
 * This code is derived from software contributed to Berkeley by
 * Tony Nardo of the Johns Hopkins University/Applied Physics Lab.
 *
E 3
D 5
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

D 6
#include <pwd.h>
#include <utmp.h>

E 6
D 2
enum status { PRINTED, FOUND, LOGGEDIN };
E 2
I 2
D 7
/*
 * All unique persons are linked in a list headed by "head" and linkd
 * by the "next" field, as well as kept in a hash table.
 */

E 7
E 2
typedef struct person {
D 7
	struct person *next;		/* link to next person */
D 2
	time_t loginat;			/* time of (last) login */
	time_t idletime;		/* how long idle (if logged in) */
E 2
I 2
	struct person *hlink;		/* link to next person in hash bucket */
E 7
E 2
	uid_t uid;			/* user id */
D 2
	enum status info;		/* type/status of request */
	short writable;			/* tty is writable */
E 2
	char *dir;			/* user's home directory */
	char *homephone;		/* pointer to home phone no. */
	char *name;			/* login name */
	char *office;			/* pointer to office name */
	char *officephone;		/* pointer to office phone no. */
	char *realname;			/* pointer to full name */
	char *shell;			/* user's shell */
I 2
D 7
	struct where *whead, *wtail;	/* list of where he is or has been */
E 7
I 7
	struct where *whead, *wtail;	/* list of where user is or has been */
E 7
} PERSON;

enum status { LASTLOG, LOGGEDIN };

typedef struct where {
D 7
	struct where *next;		/* next place he is or has been */
E 7
I 7
	struct where *next;		/* next place user is or has been */
E 7
	enum status info;		/* type/status of request */
	short writable;			/* tty is writable */
	time_t loginat;			/* time of (last) login */
	time_t idletime;		/* how long idle (if logged in) */
E 2
	char tty[UT_LINESIZE+1];	/* null terminated tty line */
	char host[UT_HOSTSIZE+1];	/* null terminated remote host name */
D 2
} PERSON;
E 2
I 2
} WHERE;
D 7

#define	HBITS	8			/* number of bits in hash code */
#define	HSIZE	(1 << 8)		/* hash table size */
#define	HMASK	(HSIZE - 1)		/* hash code mask */
E 7

D 6
PERSON *htab[HSIZE];			/* the buckets */
PERSON *phead, *ptail;			/* the linked list of all people */

int entries;				/* number of people */

PERSON *enter_person(), *find_person(), *palloc();
WHERE *walloc();
E 2

extern char tbuf[1024];			/* temp buffer for anybody */
E 6
I 6
#include "extern.h"
E 6
E 1
