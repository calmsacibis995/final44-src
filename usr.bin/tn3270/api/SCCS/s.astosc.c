h16680
s 00002/00002/00070
d D 8.1 93/06/06 16:36:38 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00069
d D 4.2 91/04/26 15:32:20 bostic 10 9
c new copyright; att/bsd/shared
e
s 00000/00000/00082
d D 4.1 88/12/04 15:11:04 minshall 9 8
c Release 4.1
e
s 00014/00007/00068
d D 3.3 88/06/29 19:55:27 bostic 8 7
c install approved copyright notice
e
s 00010/00021/00065
d D 3.2 88/03/28 13:46:46 bostic 7 6
c add Berkeley specific header
e
s 00000/00000/00086
d D 3.1 87/08/11 10:17:34 minshall 6 5
c New version numbering.
e
s 00025/00000/00061
d D 1.5 87/07/17 10:01:27 minshall 5 4
c Install sccs headers and copyright notices.
e
s 00001/00001/00060
d D 1.4 87/07/09 10:38:28 minshall 4 3
c Keep from dereferencing through a null pointer.
e
s 00003/00004/00058
d D 1.3 87/06/19 12:38:02 minshall 3 2
c Return "-1" on an error.
e
s 00036/00003/00026
d D 1.2 87/05/31 17:09:55 minshall 2 1
c Version without termcodes.m4.
e
s 00029/00000/00000
d D 1.1 87/05/31 14:34:17 minshall 1 0
c date and time created 87/05/31 14:34:17 by minshall
e
u
U
t
T
I 5
D 10
/*
D 7
 *	Copyright (c) 1984-1987 by the Regents of the
 *	University of California and by Gregory Glenn Minshall.
E 7
I 7
 * Copyright (c) 1988 Regents of the University of California.
E 10
I 10
/*-
D 11
 * Copyright (c) 1988 The Regents of the University of California.
E 10
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
E 7
 *
D 7
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
E 7
I 7
D 10
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *	%W% (Berkeley) %G%
E 8
I 8
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
E 7
 */
I 8

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8
D 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif	/* not lint */
E 7

E 5
I 1
D 2
#include "astosc.h"
#include "state.h"
E 2
I 2
#include <ctype.h>
E 2

I 2
#include "../general/general.h"

E 2
#include "../ctlr/function.h"

I 2
#include "astosc.h"
D 3
#include "state.h"
E 3

E 2
struct astosc astosc[256] = {
#include "astosc.out"
};

I 2
/* compare two strings, ignoring case */
E 2

I 2
static
ustrcmp(string1, string2)
register char *string1;
register char *string2;
{
    register int c1, c2;

    while ((c1 = (unsigned char) *string1++) != 0) {
	if (isupper(c1)) {
	    c1 = tolower(c1);
	}
	if (isupper(c2 = (unsigned char) *string2++)) {
	    c2 = tolower(c2);
	}
	if (c1 < c2) {
	    return(-1);
	} else if (c1 > c2) {
	    return(1);
	}
    }
    if (*string2) {
	return(-1);
    } else {
	return(0);
    }
}


E 2
/*
 * This routine takes a string and returns an integer.  It may return
D 3
 * STATE_NULL if there is no other integer which corresponds to the
 * string.  STATE_NULL implies an error.
E 3
I 3
 * -1 if there is no other integer which corresponds to the
 * string.  -1 implies an error.
E 3
 */

int
ascii_to_index(string)
register char *string;
{
    register struct astosc *this;

    for (this = astosc; this <= &astosc[highestof(astosc)]; this++) {
D 2
	if ((this->name[0] == string[0]) && (strcmp(this->name, string) == 0)) {
E 2
I 2
D 4
	if (ustrcmp(this->name, string) == 0) {
E 4
I 4
	if ((this->name != 0) && (ustrcmp(this->name, string) == 0)) {
E 4
E 2
	    return this-astosc;
	}
    }
D 3
    return STATE_NULL;
E 3
I 3
    return -1;
E 3
}
E 1
