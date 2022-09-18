h45391
s 00000/00001/00022
d D 8.3 95/06/05 12:20:50 christos 4 3
c Instead of special casing SIGKILL, pretend that trap 
c succeeded every time sigaction failed [suggested by mycroft]
e
s 00009/00015/00014
d D 8.2 95/05/04 18:00:13 christos 3 2
c 
e
s 00002/00002/00027
d D 8.1 93/05/31 15:20:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00000/00000
d D 5.1 91/03/07 20:28:02 bostic 1 0
c date and time created 91/03/07 20:28:02 by bostic
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

extern int pendingsigs;

D 3
#ifdef __STDC__
void clear_traps(void);
int setsignal(int);
void ignoresig(int);
void dotrap(void);
void setinteractive(int);
void exitshell(int);
#else
void clear_traps();
int setsignal();
void ignoresig();
void dotrap();
void setinteractive();
void exitshell();
#endif
E 3
I 3
int trapcmd __P((int, char **));
void clear_traps __P((void)); 
long setsignal __P((int)); 
D 4
sig_t getsigaction __P((int));
E 4
void ignoresig __P((int));
void onsig __P((int));
void dotrap __P((void));
void setinteractive __P((int));
void exitshell __P((int)); 
E 3
E 1
