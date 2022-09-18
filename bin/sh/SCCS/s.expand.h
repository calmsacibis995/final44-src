h16434
s 00006/00013/00034
d D 8.2 95/05/04 17:59:44 christos 5 4
c 
e
s 00002/00002/00045
d D 8.1 93/05/31 15:19:07 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00046
d D 5.3 92/07/30 15:42:29 marc 3 2
c fix bug where quoted pattern to case(1) wasen't being quoted
e
s 00009/00000/00037
d D 5.2 92/04/30 15:09:58 marc 2 1
c add support for tilde
e
s 00037/00000/00000
d D 5.1 91/03/07 20:27:30 bostic 1 0
c date and time created 91/03/07 20:27:30 by bostic
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
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct strlist {
	struct strlist *next;
	char *text;
};


struct arglist {
	struct strlist *list;
	struct strlist **lastp;
};

I 2
/*
 * expandarg() flags
 */
#define EXP_FULL	0x1	/* perform word splitting & file globbing */
#define EXP_TILDE	0x2	/* do normal tilde expansion */
#define	EXP_VARTILDE	0x4	/* expand tildes in an assignment */
#define	EXP_REDIR	0x8	/* file glob for a redirection (1 match only) */
I 3
#define EXP_CASE	0x10	/* keeps quotes around for CASE pattern */
E 3


E 2
D 5
#ifdef __STDC__
E 5
union node;
D 5
void expandarg(union node *, struct arglist *, int);
void expandhere(union node *, int);
int patmatch(char *, char *);
void rmescapes(char *);
int casematch(union node *, char *);
#else
void expandarg();
void expandhere();
int patmatch();
void rmescapes();
int casematch();
#endif
E 5
I 5
void expandhere __P((union node *, int));
void expandarg __P((union node *, struct arglist *, int));
void expari __P((int));
int patmatch __P((char *, char *));
void rmescapes __P((char *));
int casematch __P((union node *, char *));
E 5
E 1
