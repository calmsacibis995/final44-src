h41794
s 00002/00002/00097
d D 8.1 93/06/06 16:51:35 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00096
d D 4.2 91/04/26 15:59:53 bostic 9 8
c new copyright; att/bsd/shared
e
s 00000/00000/00109
d D 4.1 88/12/04 15:12:23 minshall 8 7
c Release 4.1
e
s 00010/00005/00099
d D 3.3 88/06/29 20:09:16 bostic 7 6
c install approved copyright notice
e
s 00010/00019/00094
d D 3.2 88/03/28 12:28:42 bostic 6 5
c add Berkeley specific headers
e
s 00000/00000/00113
d D 3.1 87/08/11 10:19:09 minshall 5 4
c New version numbering.
e
s 00002/00002/00111
d D 1.4 87/07/17 10:04:10 minshall 4 3
c Install sccs headers and copyright notices.
e
s 00001/00029/00112
d D 1.3 87/05/10 14:48:44 minshall 3 2
c Get rid of FieldForward, FieldReverse, and Terminal (Terminal 
c from here at least).
e
s 00078/00000/00063
d D 1.2 87/05/10 13:01:29 minshall 2 1
c Get rid of FieldForward, FieldReverse.
e
s 00063/00000/00000
d D 1.1 86/11/11 22:54:02 minshall 1 0
c date and time created 86/11/11 22:54:02 by minshall
e
u
U
t
T
I 1
D 9
/*
D 4
 *	Copyright (c) 1984, 1985, 1986 by the Regents of the
E 4
I 4
D 6
 *	Copyright (c) 1984-1987 by the Regents of the
E 4
 *	University of California and by Gregory Glenn Minshall.
E 6
I 6
 * Copyright (c) 1988 Regents of the University of California.
E 9
I 9
/*-
D 10
 * Copyright (c) 1988 The Regents of the University of California.
E 9
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
E 6
 *
D 6
 *	Permission to use, copy, modify, and distribute these
 *	programs and their documentation for any purpose and
 *	without fee is hereby granted, provided that this
 *	copyright and permission appear on all copies and
 *	supporting documentation, the name of the Regents of
 *	the University of California not be used in advertising
 *	or publicity pertaining to distribution of the programs
 *	without specific prior permission, and notice be given in
 *	supporting documentation that copying and distribution is
 *	by permission of the Regents of the University of California
 *	and by Gregory Glenn Minshall.  Neither the Regents of the
 *	University of California nor Gregory Glenn Minshall make
 *	representations about the suitability of this software
 *	for any purpose.  It is provided "as is" without
 *	express or implied warranty.
E 6
I 6
D 9
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
E 6
 */

D 6
#ifndef	lint
E 6
I 6
#ifndef lint
E 6
D 4
static	char	sccsid[] = "@(#)genbsubs.c	3.1  10/29/86";
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
D 6
#endif	/* ndef lint */
E 6
I 6
#endif /* not lint */
E 6

/* The output of bunequal is the offset of the byte which didn't match;
 * if all the bytes match, then we return n.
 * bunequal(s1, s2, n) */

int
bunequal(s1, s2, n)
register char *s1, *s2;
register n;
{
    register int i = 0;

    while (i++ < n) {
	if (*s1++ != *s2++) {
	    break;
	}
    }
    return(i-1);
}

/* bskip(s1, n, b) : finds the first occurrence of any byte != 'b' in the 'n'
 * bytes beginning at 's1'.
 */

int
bskip(s1, n, b)
register char *s1;
register int n;
register int b;
{
    register int i = 0;

    while (i++ < n) {
	if (*s1++ != b) {
	    break;
	}
    }
    return(i-1);
}
I 2

/*
D 3
 * memNIchr(const void *s, int c, size_t n, int and)
 *
 * Like memchr, but the comparison is '((*s)&and) == c'.
 *
 */

unsigned char *
memNIchr(s, c, n, and)
char *s;
int c;
unsigned int n;
int and;
{
    register unsigned char _c, *_s, _and;

    _and = and;
    _c = (c&_and);
    _s = (unsigned char *)s;
    while (n--) {
	if (((*_s)&_and) == _c) {
	    return _s;
	}
	_s++;
    }
    return 0;
}

/*
 * memNDchr(const void *s, int c, size_t n, int and)
E 3
I 3
 * memNSchr(const void *s, int c, size_t n, int and)
E 3
 *
 * Like memchr, but the comparison is '((*s)&and) == c',
 * and we increment our way through s by "stride" ('s += stride').
 *
 * We optimize for the most used strides of +1 and -1.
 */

unsigned char *
memNSchr(s, c, n, and, stride)
char *s;
int c;
unsigned int n;
int and;
int stride;
{
    register unsigned char _c, *_s, _and;

    _and = and;
    _c = (c&_and);
    _s = (unsigned char *)s;
    switch (stride) {
    case 1:
	while (n--) {
	    if (((*_s)&_and) == _c) {
		return _s;
	    }
	    _s++;
	}
	break;
    case -1:
	while (n--) {
	    if (((*_s)&_and) == _c) {
		return _s;
	    }
	    _s--;
	}
	break;
    default:
	while (n--) {
	    if (((*_s)&_and) == _c) {
		return _s;
	    }
	    _s += stride;
	}
    }
    return 0;
}
E 2
E 1
