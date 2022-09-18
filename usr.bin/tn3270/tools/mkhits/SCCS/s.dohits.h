h27143
s 00002/00002/00028
d D 8.1 93/06/06 16:50:29 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00027
d D 4.2 91/04/26 16:05:56 bostic 8 7
c new copyright; att/bsd/shared
e
s 00000/00000/00040
d D 4.1 88/12/04 15:13:08 minshall 7 6
c Release 4.1
e
s 00010/00005/00030
d D 3.3 88/06/29 20:04:42 bostic 6 5
c install approved copyright notice
e
s 00010/00001/00025
d D 3.2 88/03/28 12:08:10 bostic 5 4
c add Berkeley specific headers
e
s 00000/00000/00026
d D 3.1 87/08/11 10:20:43 minshall 4 3
c New version numbering.
e
s 00005/00000/00021
d D 1.3 87/07/17 10:06:05 minshall 3 2
c Install sccs headers and copyright notices.
e
s 00001/00001/00020
d D 1.2 86/11/12 16:44:58 minshall 2 1
c This version of these things seems to work.
e
s 00021/00000/00000
d D 1.1 86/11/11 09:42:15 minshall 1 0
c date and time created 86/11/11 09:42:15 by minshall
e
u
U
t
T
I 3
D 8
/*
I 5
 * Copyright (c) 1988 Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1988 The Regents of the University of California.
E 8
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
E 5
 *
D 5
 * %W% (Berkeley) %G%
E 5
I 5
D 8
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 6
 *
 *	%W% (Berkeley) %G%
E 5
 */

E 3
I 1
#define	numberof(x)	(sizeof x/sizeof x[0])
#define	highestof(x)	(numberof(x)-1)

#define	firstentry(x)	(table[dohash(0, (x))%highestof(table)])

D 2
extern struct Hits {
E 2
I 2
struct Hits {
E 2
    struct hits hits;
    char *name[4];
};

struct thing {
    struct thing *next;
    struct Hits *hits;
    unsigned char value;
    char name[100];
};

extern struct Hits Hits[256];		/* one for each of 0x00-0xff */
extern struct thing *table[100];

extern unsigned int dohash();
E 1
