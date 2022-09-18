h12151
s 00002/00002/00025
d D 8.1 93/06/02 20:05:23 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00000/00014
d D 5.2 92/06/29 14:43:42 bostic 2 1
c move fnmatch function declaration from unistd.h
e
s 00014/00000/00000
d D 5.1 92/06/28 13:01:24 bostic 1 0
c date and time created 92/06/28 13:01:24 by bostic
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

I 2
#ifndef	_FNMATCH_H_
#define	_FNMATCH_H_

E 2
#define	FNM_NOMATCH	1	/* Match failed. */

#define	FNM_NOESCAPE	0x01	/* Disable backslash escaping. */
#define	FNM_PATHNAME	0x02	/* Slash must be matched by slash. */
#define	FNM_PERIOD	0x04	/* Period must be matched by period. */
I 2

#include <sys/cdefs.h>

__BEGIN_DECLS
#ifndef	_POSIX_SOURCE
int	 fnmatch __P((const char *, const char *, int));
#endif
__END_DECLS

#endif /* !_FNMATCH_H_ */
E 2
E 1
