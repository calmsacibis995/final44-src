h49559
s 00002/00002/00017
d D 8.1 93/06/06 16:32:59 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00021/00019
d D 5.2 91/03/01 01:31:55 dab 7 6
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00000/00000/00040
d D 5.1 90/09/14 10:42:03 borman 6 5
c Bump the sccs id to 5.1
e
s 00000/00002/00040
d D 1.5 90/06/28 12:57:17 borman 5 4
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00041
d D 1.4 90/06/01 17:45:17 bostic 4 3
c new copyright notice
e
s 00010/00005/00042
d D 1.3 88/06/29 20:15:19 bostic 3 2
c install approved copyright notice
e
s 00014/00000/00033
d D 1.2 88/03/08 10:30:49 bostic 2 1
c add Berkeley specific copyright
e
s 00033/00000/00000
d D 1.1 87/09/11 15:40:33 minshall 1 0
c date and time created 87/09/11 15:40:33 by minshall
e
u
U
t
T
I 1
/*
I 2
D 8
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
E 2
 * Some general definitions.
D 5
 *
 * @(#)general.h	3.1 (Berkeley) 8/11/87
E 5
 */


#define	numberof(x)	(sizeof x/sizeof x[0])
#define	highestof(x)	(numberof(x)-1)

D 7
#if	defined(unix)
#define	ClearElement(x)		bzero((char *)&x, sizeof x)
#define	ClearArray(x)		bzero((char *)x, sizeof x)
#else	/* defined(unix) */
E 7
#define	ClearElement(x)		memset((char *)&x, 0, sizeof x)
#define	ClearArray(x)		memset((char *)x, 0, sizeof x)
D 7
#endif	/* defined(unix) */

#if	defined(unix)		/* Define BSD equivalent mem* functions */
#define	memcpy(dest,src,n)	bcopy(src,dest,n)
#define	memmove(dest,src,n)	bcopy(src,dest,n)
#define	memset(s,c,n)		if (c == 0) { \
				    bzero(s,n); \
				} else { \
				    register char *src = s; \
				    register int count = n; \
					\
				    while (count--) { \
					*src++ = c; \
				    } \
				}
#define	memcmp(s1,s2,n)		bcmp(s1,s2,n)
#endif	/* defined(unix) */
E 7
E 1
