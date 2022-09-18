h02654
s 00001/00003/00030
d D 5.2 91/05/06 20:43:13 bostic 3 2
c new copyright; att/bsd/shared
e
s 00010/00001/00023
d D 5.1 91/04/12 11:50:56 bostic 2 1
c new copyright; att/bsd/shared
e
s 00024/00000/00000
d D 1.1 86/08/01 08:56:09 sam 1 0
c date and time created 86/08/01 08:56:09 by sam
e
u
U
t
T
I 1
D 2
    /*	@(#)gcrt0.h	1.1 (Tahoe) 3/21/85	*/
E 2
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

/* @(#)gcrt0.h	1.1 (Tahoe) 3/21/85 */
E 3
E 2

struct phdr {
    char	*lpc;
    char	*hpc;
    int		ncnt;
};

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
E 1
