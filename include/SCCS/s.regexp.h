h57542
s 00002/00002/00041
d D 8.1 93/06/02 20:06:24 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00038
d D 5.2 91/04/03 16:21:50 bostic 7 6
c protect all user-level include files against reinclusion
e
s 00008/00011/00030
d D 5.1 91/02/05 17:10:56 bostic 6 5
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00040
d D 1.5 90/06/01 14:01:20 bostic 5 4
c new copyright notice
e
s 00001/00001/00050
d D 1.4 90/05/29 19:26:52 bostic 4 3
c C++ wants the prototypes, too
e
s 00007/00000/00044
d D 1.3 90/03/06 15:58:42 bostic 3 2
c add ANSI C prototypes
e
s 00023/00002/00021
d D 1.2 89/04/11 14:15:13 bostic 2 1
c add Berkeley specific copyright notice
e
s 00023/00000/00000
d D 1.1 87/09/29 13:30:07 bostic 1 0
c date and time created 87/09/29 13:30:07 by bostic
e
u
U
t
T
I 1
/*
I 2
 * Copyright (c) 1986 by University of Toronto.
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley
 * by Henry Spencer.
 *
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

I 7
#ifndef	_REGEXP_H_
#define	_REGEXP_H_

E 7
/*
E 2
 * Definitions etc. for regexp(3) routines.
 *
 * Caveat:  this is V8 regexp(3) [actually, a reimplementation thereof],
 * not the System V one.
D 2
 *
 *	%W% (Berkeley) %G%
E 2
 */
#define NSUBEXP  10
typedef struct regexp {
	char *startp[NSUBEXP];
	char *endp[NSUBEXP];
	char regstart;		/* Internal use only. */
	char reganch;		/* Internal use only. */
	char *regmust;		/* Internal use only. */
	int regmlen;		/* Internal use only. */
	char program[1];	/* Unwarranted chumminess with compiler. */
} regexp;

I 3
D 4
#ifdef __STDC__
E 4
I 4
D 6
#if __STDC__ || c_plusplus
E 4
extern regexp *regcomp(const char *);
extern int regexec(const  regexp *, const char *);
extern void regsub(const  regexp *, const char *, char *);
extern void regerror(const char *);
#else
E 3
extern regexp *regcomp();
extern int regexec();
extern void regsub();
extern void regerror();
I 3
#endif
E 6
I 6
#include <sys/cdefs.h>

__BEGIN_DECLS
regexp *regcomp __P((const char *));
int regexec __P((const  regexp *, const char *));
void regsub __P((const  regexp *, const char *, char *));
void regerror __P((const char *));
__END_DECLS
I 7

#endif /* !_REGEXP_H_ */
E 7
E 6
E 3
E 1
