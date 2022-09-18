h26197
s 00002/00002/00037
d D 8.1 93/06/04 15:13:08 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00034
d D 5.10 91/03/06 12:34:35 bostic 13 11
c unsigned length fix
e
s 00004/00003/00035
d R 5.10 91/03/06 12:27:53 bostic 12 11
c unsigned integer fix (again!)
e
s 00007/00003/00031
d D 5.9 91/02/24 13:57:56 bostic 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00004/00033
d D 5.8 90/06/27 21:01:31 karels 10 9
c optimize for machines other than the Cray (infinite loop takes too long)
e
s 00004/00001/00033
d D 5.7 90/06/24 14:27:55 bostic 9 8
c change length to size_t; make sure length of 0 still works
e
s 00001/00011/00033
d D 5.6 90/06/01 14:47:18 bostic 8 7
c new copyright notice
e
s 00004/00004/00039
d D 5.5 90/05/17 12:05:49 bostic 7 6
c keep string.h and source in sync
e
s 00019/00002/00024
d D 5.4 88/06/27 17:37:49 bostic 6 5
c written by Jeffrey Mogul, Stanford; add Berkeley specific header
e
s 00002/00002/00024
d D 5.3 86/03/09 19:59:03 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00023
d D 5.2 85/06/05 12:39:19 mckusick 4 3
c Add copyright
e
s 00000/00000/00024
d D 5.1 85/05/30 10:51:29 dist 3 2
c Add copyright
e
s 00017/00010/00007
d D 4.2 83/06/27 21:11:37 sam 2 1
c version from mogul with loop unrolled for speed
e
s 00017/00000/00000
d D 4.1 80/12/21 16:40:22 wnj 1 0
c date and time created 80/12/21 16:40:22 by wnj
e
u
U
t
T
I 6
/*
D 14
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
I 7
 * This code is derived from software contributed to Berkeley by
 * Jeffrey Mogul.
 *
E 7
D 8
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

E 6
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5
E 4

E 2
D 7
/*
D 2
 * Swap bytes in 16-bit [half-]words
 * for going between the 11 and the interdata
E 2
I 2
 * Swab bytes
 * Jeffrey Mogul, Stanford
E 2
 */
E 7
I 7
#include <string.h>
E 7

D 2
swab(pf, pt, n)
register short *pf, *pt;
register n;
E 2
I 2
I 7
void
E 7
D 13
swab(from, to, n)
E 13
I 13
swab(from, to, len)
E 13
D 11
	register char *from, *to;
D 9
	register int n;
E 9
I 9
D 10
	register size_t n;
E 10
I 10
	register int n;
E 11
I 11
	const void *from;
	void *to;
D 13
	register size_t n;
E 13
I 13
	size_t len;
E 13
E 11
E 10
E 9
E 2
{
I 11
D 13
	register char *fp, *tp;
E 13
E 11
D 2

	n /= 2;
E 2
I 2
	register unsigned long temp;
I 13
	register int n;
	register char *fp, *tp;
E 13
I 9
D 10

	if (!n)
		return;
E 10
E 9
D 6
	
E 6
I 6

E 6
D 13
	n >>= 1; n++;
E 13
I 13
	n = (len >> 1) + 1;
E 13
D 11
#define	STEP	temp = *from++,*to++ = *from++,*to++ = temp
E 11
I 11
	fp = (char *)from;
	tp = (char *)to;
#define	STEP	temp = *fp++,*tp++ = *fp++,*tp++ = temp
E 11
	/* round to multiple of 8 */
	while ((--n) & 07)
		STEP;
	n >>= 3;
E 2
	while (--n >= 0) {
D 2
		*pt++ = (*pf << 8) + ((*pf >> 8) & 0377);
		pf++;
E 2
I 2
		STEP; STEP; STEP; STEP;
		STEP; STEP; STEP; STEP;
E 2
	}
}
E 1
