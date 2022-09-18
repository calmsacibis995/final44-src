h01322
s 00003/00009/00012
d D 8.2 95/05/04 17:59:47 christos 3 2
c 
e
s 00002/00002/00019
d D 8.1 93/05/31 15:19:10 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00000/00000
d D 5.1 91/03/07 20:27:31 bostic 1 0
c date and time created 91/03/07 20:27:31 by bostic
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
void init(void);
void reset(void);
void initshellproc(void);
#else
void init();
void reset();
void initshellproc();
#endif
E 3
I 3
void init __P((void));
void reset __P((void));
void initshellproc __P((void));
E 3
E 1
