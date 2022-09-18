h07410
s 00004/00011/00017
d D 8.2 95/05/04 18:00:02 christos 4 3
c 
e
s 00002/00002/00026
d D 8.1 93/05/31 15:20:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00016/00027
d D 5.2 92/06/23 18:05:51 marc 2 1
c remove unneded prototypes
e
s 00043/00000/00000
d D 5.1 91/03/07 20:27:48 bostic 1 0
c date and time created 91/03/07 20:27:48 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#ifndef SYSV
#define strchr mystrchr
#endif
E 2
I 2
#include <string.h>
E 2

D 4
#ifdef __STDC__
void scopyn(const char *, char *, int);
D 2
char *strchr(const char *, int);
void mybcopy(const pointer, pointer, int);
E 2
int prefix(const char *, const char *);
int number(const char *);
int is_number(const char *);
D 2
int strcmp(const char *, const char *);	/* from C library */
char *strcpy(char *, const char *);	/* from C library */
int strlen(const char *);		/* from C library */
char *strcat(char *, const char *);	/* from C library */
E 2
#else
void scopyn();
D 2
char *strchr();
void mybcopy();
E 2
int prefix();
int number();
int is_number();
D 2
int strcmp();
char *strcpy();
int strlen();
char *strcat();
E 2
#endif
E 4
I 4
void scopyn __P((const char *, char *, int));
int prefix __P((const char *, const char *));
int number __P((const char *));
int is_number __P((const char *));
E 4

#define equal(s1, s2)	(strcmp(s1, s2) == 0)
#define scopy(s1, s2)	((void)strcpy(s2, s1))
D 2
#define bcopy(src, dst, n)	mybcopy((pointer)(src), (pointer)(dst), n)
E 2
E 1
