h10393
s 00002/00002/00038
d D 8.1 93/06/27 19:24:06 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00039
d D 5.3 93/06/27 19:24:00 bostic 5 3
c new f* functions need stdio.h
e
s 00002/00002/00037
d R 8.1 93/06/27 18:05:38 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00036
d D 5.2 93/06/27 18:05:29 bostic 3 1
c add prototypes for fgetrune, fputrune, fungetrune
c from Paul Borman
e
s 00002/00002/00034
d R 8.1 93/06/02 20:06:30 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00000/00000
d D 5.1 93/05/26 20:06:53 bostic 1 0
c rune support from Paul Borman
c date and time created 93/05/26 20:06:53 by bostic
e
u
U
t
T
I 1
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
 * Paul Borman at Krystal Technologies.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_RUNE_H_
#define	_RUNE_H_

#include <runetype.h>
I 5
#include <stdio.h>
E 5

#define	_PATH_LOCALE	"/usr/share/locale"

#define _INVALID_RUNE   _CurrentRuneLocale->invalid_rune

#define __sgetrune      _CurrentRuneLocale->sgetrune
#define __sputrune      _CurrentRuneLocale->sputrune

#define sgetrune(s, n, r)       (*__sgetrune)((s), (n), (r))
#define sputrune(c, s, n, r)    (*__sputrune)((c), (s), (n), (r))

__BEGIN_DECLS
char	*mbrune __P((const char *, rune_t));
char	*mbrrune __P((const char *, rune_t));
char	*mbmb __P((const char *, char *));
I 3
long	 fgetrune __P((FILE *));
int	 fputrune __P((rune_t, FILE *));
int	 fungetrune __P((rune_t, FILE *));
E 3
int	 setrunelocale __P((char *));
void	 setinvalidrune __P((rune_t));
__END_DECLS

#endif	/*! _RUNE_H_ */
E 1
