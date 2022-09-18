h33482
s 00001/00003/00078
d D 5.2 91/05/06 20:43:15 bostic 3 2
c new copyright; att/bsd/shared
e
s 00009/00000/00072
d D 5.1 91/04/12 11:50:58 bostic 2 1
c new copyright; att/bsd/shared
e
s 00072/00000/00000
d D 1.1 86/08/01 08:56:09 sam 1 0
c date and time created 86/08/01 08:56:09 by sam
e
u
U
t
T
I 2
/*-
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
D 3
 * %sccs.include.proprietary.c%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */
D 3

E 2
I 1
/* @(#)gmon.h	2.0 (Tahoe) 3/20/85 */
E 3

struct phdr {
    char	*lpc;
    char	*hpc;
    int		ncnt;
};

    /*
     *	histogram counters are unsigned shorts (according to the kernel).
     */
#define	HISTCOUNTER	unsigned short

    /*
     *	fraction of text space to allocate for histogram counters
     *	here, 1/2
     */
#define	HISTFRACTION	2

    /*
     *	Fraction of text space to allocate for from hash buckets.
     *	The value of HASHFRACTION is based on the minimum number of bytes
     *	of separation between two subroutine call points in the object code.
     *	Given MIN_SUBR_SEPARATION bytes of separation the value of
     *	HASHFRACTION is calculated as:
     *
     *		HASHFRACTION = MIN_SUBR_SEPARATION / (2 * sizeof(short) - 1);
     *
     *	For the Tahoe, the shortest two call sequence is:
     *
     *		calls	$0,(r0)
     *		calls	$0,(r0)
     *
     *	which is separated by only three bytes, thus HASHFRACTION is 
     *	calculated as:
     *
     *		HASHFRACTION = 3 / (2 * 2 - 1) = 1
     *
     *	Note that the division above rounds down, thus if MIN_SUBR_FRACTION
     *	is less than three, this algorithm will not work!
     */
#define	HASHFRACTION	1

    /*
     *	percent of text space to allocate for tostructs
     *	with a minimum.
     */
#define ARCDENSITY	2
#define MINARCS		50

struct tostruct {
    char		*selfpc;
    long		count;
    unsigned short	link;
};

    /*
     *	a raw arc,
     *	    with pointers to the calling site and the called site
     *	    and a count.
     */
struct rawarc {
    unsigned long	raw_frompc;
    unsigned long	raw_selfpc;
    long		raw_count;
};

    /*
     *	general rounding functions.
     */
#define ROUNDDOWN(x,y)	(((x)/(y))*(y))
#define ROUNDUP(x,y)	((((x)+(y)-1)/(y))*(y))
E 1
