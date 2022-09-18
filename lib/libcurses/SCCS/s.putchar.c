h57307
s 00002/00002/00021
d D 8.2 94/05/04 06:24:53 bostic 10 9
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00021
d D 8.1 93/06/04 16:48:57 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00022
d D 5.6 93/05/16 15:54:46 bostic 8 7
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00008/00007/00015
d D 5.5 92/08/23 11:48:16 bostic 7 5
c rename _putchar to __cputchar, lint, KNF
e
s 00008/00007/00015
d R 5.5 92/05/15 15:25:43 bostic 6 5
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00021
d D 5.4 90/06/01 15:39:55 bostic 5 4
c new copyright notice
e
s 00010/00005/00022
d D 5.3 88/06/30 17:21:59 bostic 4 3
c install approved copyright notice
e
s 00010/00004/00017
d D 5.2 88/06/08 13:57:40 bostic 3 2
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00003/00011
d D 5.1 85/06/07 11:40:39 dist 2 1
c Add copyright
e
s 00014/00000/00000
d D 1.1 85/05/01 17:29:07 bloom 1 0
c date and time created 85/05/01 17:29:07 by bloom
e
u
U
t
T
I 1
D 2
# include	"curses.ext"

E 2
/*
D 2
 * %W% (Berkeley) %G%
E 2
I 2
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 9
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 10
 * Copyright (c) 1981, 1993
E 10
I 10
 * Copyright (c) 1981, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
E 3
E 2
 */
I 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 7
#endif /* not lint */
E 7
I 7
#endif	/* not lint */
E 7
E 3

D 7
# include	"curses.ext"
E 7
I 7
D 10
#include <curses.h>
E 10
I 10
#include "curses.h"
E 10
E 7

E 2
D 7
char
_putchar(c)
reg char	c; {
E 7
I 7
void
__cputchar(ch)
	int ch;
{
E 7

D 7
	putchar(c);
E 7
#ifdef DEBUG
D 7
	fprintf(outf, "_PUTCHAR(%s)\n", unctrl(c));
E 7
I 7
D 8
	__TRACE("__cputchar: %s\n", unctrl(ch));
E 8
I 8
	__CTRACE("__cputchar: %s\n", unctrl(ch));
E 8
E 7
#endif
I 7
	(void)putchar(ch);
E 7
}
E 1
