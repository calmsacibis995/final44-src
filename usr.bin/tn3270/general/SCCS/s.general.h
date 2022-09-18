h01928
s 00002/00002/00037
d D 8.1 93/06/06 16:51:38 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00036
d D 4.2 91/04/26 15:59:54 bostic 14 13
c new copyright; att/bsd/shared
e
s 00000/00000/00049
d D 4.1 88/12/04 15:12:19 minshall 13 12
c Release 4.1
e
s 00010/00005/00039
d D 3.3 88/06/29 20:09:18 bostic 12 11
c install approved copyright notice
e
s 00013/00002/00031
d D 3.2 88/03/28 12:28:43 bostic 11 10
c add Berkeley specific headers
e
s 00000/00000/00033
d D 3.1 87/08/11 10:19:11 minshall 10 9
c New version numbering.
e
s 00002/00000/00031
d D 1.9 87/07/17 10:04:12 minshall 9 8
c Install sccs headers and copyright notices.
e
s 00001/00000/00030
d D 1.8 87/05/31 17:58:24 minshall 8 7
c Add 'memcmp' translation for unix.
e
s 00006/00006/00024
d D 1.7 87/05/21 22:05:59 minshall 7 6
c Remove 'ExitString' call from non-zero memset (do non-zero memset 
c instead).
e
s 00001/00001/00029
d D 1.6 87/05/20 14:41:35 minshall 6 5
c Format change.
e
s 00001/00001/00029
d D 1.5 87/05/19 09:46:08 minshall 5 4
c ClearStructure->ClearElement
e
s 00001/00001/00029
d D 1.4 87/05/13 11:36:44 minshall 4 3
c Match up the double-quote marks.
e
s 00021/00001/00009
d D 1.3 87/05/12 10:44:07 minshall 3 2
c Map system 5/ansi routines onto BSD routines.
e
s 00003/00000/00007
d D 1.2 87/04/01 13:57:43 minshall 2 1
c Fix close/open sequences in a rational way.
e
s 00007/00000/00000
d D 1.1 87/03/26 15:07:50 minshall 1 0
c date and time created 87/03/26 15:07:50 by minshall
e
u
U
t
T
I 1
D 14
/*
D 11
 * Some general definitions.
E 11
I 11
 * Copyright (c) 1988 Regents of the University of California.
E 14
I 14
/*-
D 15
 * Copyright (c) 1988 The Regents of the University of California.
E 14
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
E 11
I 9
 *
D 11
 * %W% (Berkeley) %G%
E 11
I 11
D 14
 * Redistribution and use in source and binary forms are permitted
D 12
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 12
I 12
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 12
 *
 *	%W% (Berkeley) %G%
E 11
E 9
 */

I 11
/*
 * Some general definitions.
 */
E 11

#define	numberof(x)	(sizeof x/sizeof x[0])
#define	highestof(x)	(numberof(x)-1)
I 2

D 3
#define	ClearStructure(x)	bzero((char *)&x, sizeof x)
E 3
I 3
#if	defined(unix)
#define	ClearElement(x)		bzero((char *)&x, sizeof x)
E 3
#define	ClearArray(x)		bzero((char *)x, sizeof x)
I 3
#else	/* defined(unix) */
D 5
#define	ClearStructure(x)	memset((char *)&x, 0, sizeof x)
E 5
I 5
D 6
#define	ClearElement(x)	memset((char *)&x, 0, sizeof x)
E 6
I 6
#define	ClearElement(x)		memset((char *)&x, 0, sizeof x)
E 6
E 5
#define	ClearArray(x)		memset((char *)x, 0, sizeof x)
#endif	/* defined(unix) */

#if	defined(unix)		/* Define BSD equivalent mem* functions */
#define	memcpy(dest,src,n)	bcopy(src,dest,n)
#define	memmove(dest,src,n)	bcopy(src,dest,n)
#define	memset(s,c,n)		if (c == 0) { \
				    bzero(s,n); \
				} else { \
D 7
				    char buffer[100]; \
				    \
				    sprintf( \
D 4
				    "Attempt to use memchr(, != 0,) in %s, %s.\n, \
E 4
I 4
				"Attempt to use memchr(, != 0,) in %s, %s.\n", \
E 4
						__FILE__, __LINE__); \
				    ExitString(stderr, buffer, 1); \
E 7
I 7
				    register char *src = s; \
				    register int count = n; \
					\
				    while (count--) { \
					*src++ = c; \
				    } \
E 7
				}
I 8
#define	memcmp(s1,s2,n)		bcmp(s1,s2,n)
E 8
#endif	/* defined(unix) */
E 3
E 2
E 1
