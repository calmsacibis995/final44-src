h34887
s 00002/00002/00100
d D 8.1 93/06/06 14:49:48 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00097
d D 5.5 92/07/14 14:30:31 bostic 5 4
c fix for quads; prototype and cleanup in general
e
s 00001/00011/00097
d D 5.4 90/06/01 16:52:24 bostic 4 3
c new copyright notice
e
s 00025/00011/00083
d D 5.3 90/05/07 22:56:02 bostic 3 2
c changes to support od(1), plus type "etc" -> "etb"
e
s 00005/00006/00089
d D 5.2 89/08/30 11:11:52 bostic 2 1
c _c should zero-pad the hexnumbers, which should be octal
e
s 00095/00000/00000
d D 5.1 89/08/29 18:36:15 bostic 1 0
c date and time created 89/08/29 18:36:15 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 5

#include <stdio.h>
E 5
#include <ctype.h>
#include "hexdump.h"

I 5
void
E 5
conv_c(pr, p)
	PR *pr;
	u_char *p;
{
I 3
	extern int deprecated;
E 3
D 2
	char *str;
E 2
I 2
	char buf[10], *str;
E 2

	switch(*p) {
	case '\0':
		str = "\\0";
		goto strpr;
	/* case '\a': */
	case '\007':
I 3
		if (deprecated)		/* od didn't know about \a */
			break;
E 3
		str = "\\a";
		goto strpr;
	case '\b':
		str = "\\b";
		goto strpr;
	case '\f':
		str = "\\f";
		goto strpr;
	case '\n':
		str = "\\n";
		goto strpr;
	case '\r':
		str = "\\r";
		goto strpr;
	case '\t':
		str = "\\t";
		goto strpr;
	case '\v':
I 3
		if (deprecated)
			break;
E 3
		str = "\\v";
D 2
strpr:		*pr->cchar = 's';
		(void)printf(pr->fmt, str);
		break;
E 2
I 2
		goto strpr;
E 2
	default:
D 3
		if (isprint(*p)) {
			*pr->cchar = 'c';
			(void)printf(pr->fmt, *p);
		} else {
D 2
			*pr->cchar = 'x';
			(void)printf(pr->fmt, (int)*p);
E 2
I 2
			(void)sprintf(str = buf, "%03o", (int)*p);
strpr:			*pr->cchar = 's';
			(void)printf(pr->fmt, str);
E 2
		}
E 3
I 3
		break;
E 3
	}
I 3
	if (isprint(*p)) {
		*pr->cchar = 'c';
		(void)printf(pr->fmt, *p);
	} else {
		(void)sprintf(str = buf, "%03o", (int)*p);
strpr:		*pr->cchar = 's';
		(void)printf(pr->fmt, str);
	}
E 3
}

I 5
void
E 5
conv_u(pr, p)
	PR *pr;
	u_char *p;
{
I 3
	extern int deprecated;
E 3
	static char *list[] = {
		"nul", "soh", "stx", "etx", "eot", "enq", "ack", "bel",
		 "bs",  "ht",  "lf",  "vt",  "ff",  "cr",  "so",  "si",
D 3
		"dle", "dcl", "dc2", "dc3", "dc4", "nak", "syn", "etc",
E 3
I 3
		"dle", "dcl", "dc2", "dc3", "dc4", "nak", "syn", "etb",
E 3
		"can",  "em", "sub", "esc",  "fs",  "gs",  "rs",  "us",
	};

I 3
						/* od used nl, not lf */
E 3
	if (*p <= 0x1f) {
		*pr->cchar = 's';
D 3
		(void)printf(pr->fmt, list[*p]);
	} else if (*p == 0xff) {
E 3
I 3
		if (deprecated && *p == 0x0a)
			(void)printf(pr->fmt, "nl");
		else
			(void)printf(pr->fmt, list[*p]);
	} else if (*p == 0x7f) {
E 3
		*pr->cchar = 's';
		(void)printf(pr->fmt, "del");
I 3
D 5
	} else if (deprecated && *p == 0x20) {	/* od replace space with sp */
E 5
I 5
	} else if (deprecated && *p == 0x20) {	/* od replaced space with sp */
E 5
		*pr->cchar = 's';
		(void)printf(pr->fmt, " sp");
E 3
	} else if (isprint(*p)) {
		*pr->cchar = 'c';
		(void)printf(pr->fmt, *p);
	} else {
		*pr->cchar = 'x';
		(void)printf(pr->fmt, (int)*p);
	}
}
E 1
