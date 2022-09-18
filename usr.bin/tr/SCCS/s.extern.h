h47255
s 00002/00002/00023
d D 8.1 93/06/06 16:38:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00006/00022
d D 5.2 91/10/27 10:38:19 bostic 2 1
c various bug fixes, don't restrict class usage at all on the grounds
c that you can't get it right.  Hal Jesperson agrees that this is correct,
c it's not clear from the POSIX draft.
e
s 00028/00000/00000
d D 5.1 91/10/24 17:49:04 bostic 1 0
c POSIX 1003.2/D11.2 version
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
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

typedef struct {
D 2
	enum { EOS, INFINITE, NORMAL, RANGE, SEQUENCE, SET, ULSET } state;
E 2
I 2
	enum { STRING1, STRING2 } which;
	enum { EOS, INFINITE, NORMAL, RANGE, SEQUENCE, SET } state;
E 2
	int	 cnt;			/* character count */
	int	 lastch;		/* last character */
I 2
	int	equiv[2];		/* equivalence set */
E 2
	int	*set;			/* set of characters */
	char	*str;			/* user's string */
D 2

#define	T_CLASS	0x01			/* class != lower/upper */
#define	T_SEQ	0x02			/* sequence */
#define	T_UL	0x04			/* lower/upper classes */
	u_int	type;			/* Permissible string conventions. */
E 2
} STR;

#include <limits.h>
#define	NCHARS	(UCHAR_MAX + 1)		/* Number of possible characters. */
#define	OOBCH	(UCHAR_MAX + 1)		/* Out of band character value. */

void	 err __P((const char *fmt, ...));
int	 next __P((STR *));
E 1
