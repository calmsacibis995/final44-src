h31452
s 00004/00001/00021
d D 8.2 95/05/04 17:59:34 christos 7 6
c 
e
s 00002/00002/00020
d D 8.1 93/05/31 15:40:37 bostic 6 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00022
d R 8.1 93/05/31 15:29:32 bostic 5 3
c yank to 8.1
e
s 00002/00002/00020
d R 8.1 93/05/31 15:26:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00000/00010
d D 1.2 93/05/31 15:26:18 bostic 3 1
c add copyright notices, SCCS headers, yank to 8.1
e
s 00010/00000/00010
d R 8.1 93/05/31 15:25:22 bostic 2 1
c add copyright notices, SCCS headers, yank to 8.1
e
s 00010/00000/00000
d D 1.1 92/05/22 15:06:24 marc 1 0
c date and time created 92/05/22 15:06:24 by marc
e
u
U
t
T
I 3
/*-
D 6
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
#define ALIASINUSE	1

struct alias {
	struct alias *next;
	char *name;
	char *val;
	int flag;
};

D 7
struct alias *lookupalias();
E 7
I 7
struct alias *lookupalias __P((char *, int));
int aliascmd __P((int, char **));
int unaliascmd __P((int, char **));
void rmaliases __P((void));
E 7
E 1
