h24638
s 00002/00002/00026
d D 8.1 93/05/31 14:53:06 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00000/00000
d D 1.1 92/12/13 22:51:36 muller 1 0
c date and time created 92/12/13 22:51:36 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * data structure for storing user supplied replacement strings (-s)
 */
typedef struct replace {
	char		*nstr;	/* the new string we will substitute with */
#	ifdef NET2_REGEX
	regexp		*rcmp;	/* compiled regular expression used to match */
#	else
	regex_t		rcmp;	/* compiled regular expression used to match */
#	endif
	int		flgs;	/* print conversions? global in operation?  */
#define	PRNT		0x1
#define	GLOB		0x2
	struct replace	*fow;	/* pointer to next pattern */
} REPLACE;
E 1
