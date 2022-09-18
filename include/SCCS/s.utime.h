h38398
s 00002/00002/00022
d D 8.1 93/06/02 20:07:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00019
d D 5.4 91/04/03 16:43:13 bostic 4 3
c protect all user-level include files against reinclusion
e
s 00001/00001/00018
d D 5.3 91/02/23 14:13:01 donn 3 2
c Add const qualifiers to make utime declaration more like POSIX version.
e
s 00005/00005/00014
d D 5.2 91/02/05 17:11:00 bostic 2 1
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00019/00000/00000
d D 5.1 90/08/27 21:33:13 bostic 1 0
c date and time created 90/08/27 21:33:13 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4
#ifndef	_UTIME_H_
#define	_UTIME_H_

E 4
struct utimbuf {
	time_t actime;		/* Access time */
	time_t modtime;		/* Modification time */
};

D 2
#if __STDC__ || c_plusplus
int utime(char *, struct utimbuf *);
#else
int utime();
#endif
E 2
I 2
#include <sys/cdefs.h>

__BEGIN_DECLS
D 3
int utime __P((char *, struct utimbuf *));
E 3
I 3
int utime __P((const char *, const struct utimbuf *));
E 3
__END_DECLS
I 4

#endif /* !_UTIME_H_ */
E 4
E 2
E 1
