h40743
s 00000/00000/00014
d D 8.1 93/06/06 22:29:39 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00009
d D 4.2 91/04/18 18:59:56 bostic 2 1
c new copyright; att/bsd/shared
e
s 00010/00000/00000
d D 4.1 83/03/30 12:08:41 sam 1 0
c date and time created 83/03/30 12:08:41 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

#include <stdio.h>
#include <mp.h>
extern MINT *x, *b, *one, *c64, *t45, *z, *q, *r, *two, *t15;
extern char buf[256];
#ifdef debug
#define nin(x, y) m_in(x, 8, y)
#define nout(x, y) m_out(x, 8, y)
#endif
E 1
