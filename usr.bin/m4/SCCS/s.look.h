h37026
s 00021/00000/00000
d D 5.1 91/09/03 09:33:13 bostic 1 0
c New version from Oz Yigit
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifdef __STDC__
#define proto(s) s
#else
#define proto(s) ()
#endif

int hash proto((char *name));
ndptr lookup proto((char *name));
ndptr addent proto((char *name));
void remhash proto((char *name, int all));

#undef proto
E 1
