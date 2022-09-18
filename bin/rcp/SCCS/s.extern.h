h05342
s 00002/00002/00022
d D 8.1 93/05/31 15:08:06 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00023
d D 5.2 93/04/29 13:39:14 bostic 2 1
c use err/warn from the C library
e
s 00024/00000/00000
d D 5.1 92/07/19 12:17:57 bostic 1 0
c date and time created 92/07/19 12:17:57 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

typedef struct {
	int cnt;
	char *buf;
} BUF;

extern int iamremote;

BUF	*allocbuf __P((BUF *, int, int));
char	*colon __P((char *));
D 2
void	 err __P((const char *, ...));
E 2
void	 lostconn __P((int));
void	 nospace __P((void));
int	 okname __P((char *));
I 2
void	 run_err __P((const char *, ...));
E 2
int	 susystem __P((char *, int));
void	 verifydir __P((char *));
E 1
