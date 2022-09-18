h55478
s 00001/00005/00012
d D 8.2 95/05/04 17:59:53 christos 3 2
c 
e
s 00002/00002/00015
d D 8.1 93/05/31 15:19:32 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00000/00000
d D 5.1 91/03/07 20:27:38 bostic 1 0
c date and time created 91/03/07 20:27:38 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#ifdef __STDC__
void chkmail(int);
#else
void chkmail();
#endif
E 3
I 3
void chkmail __P((int));
E 3
E 1
