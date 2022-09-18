h18389
s 00000/00040/00000
d D 7.4 92/05/19 10:51:47 sklower 4 3
c this file is no longer needed
e
s 00009/00000/00031
d D 7.3 91/05/06 19:24:06 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00031
d D 7.2 89/04/22 11:54:18 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00031/00000/00000
d D 7.1 88/12/14 15:29:45 sklower 1 0
c date and time created 88/12/14 15:29:45 by sklower
e
u
U
t
T
I 3
D 4
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
struct maptab {
	struct iso_addr	map_isoa;		/* iso address */
	u_char			map_enaddr[6];	/* ethernet address */
	u_char			map_valid;		/* true if entry is valid */
};
E 4
E 1
