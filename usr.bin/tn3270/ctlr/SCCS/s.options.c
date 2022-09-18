h20012
s 00002/00002/00153
d D 8.1 93/06/06 16:40:10 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00152
d D 4.2 91/04/26 15:40:52 bostic 9 8
c new copyright; att/bsd/shared
e
s 00000/00000/00165
d D 4.1 88/12/04 15:12:00 minshall 8 7
c Release 4.1
e
s 00002/00002/00163
d D 3.4 88/08/28 17:57:55 minshall 7 6
c Lint (and, maybe, copyrights).
e
s 00010/00005/00155
d D 3.3 88/06/29 19:49:58 bostic 6 5
c install approved copyright notice
e
s 00010/00019/00150
d D 3.2 88/03/28 12:34:27 bostic 5 4
c add Berkeley specific header
e
s 00000/00000/00169
d D 3.1 87/08/11 10:18:37 minshall 4 3
c New version numbering.
e
s 00002/00002/00167
d D 1.3 87/07/17 10:03:09 minshall 3 2
c Install sccs headers and copyright notices.
e
s 00001/00001/00168
d D 1.2 87/05/22 11:18:03 minshall 2 1
c New directory structure.
e
s 00169/00000/00000
d D 1.1 86/11/11 22:54:06 minshall 1 0
c date and time created 86/11/11 22:54:06 by minshall
e
u
U
t
T
I 1
D 9
/*
D 3
 *	Copyright (c) 1984, 1985, 1986 by the Regents of the
E 3
I 3
D 5
 *	Copyright (c) 1984-1987 by the Regents of the
E 3
 *	University of California and by Gregory Glenn Minshall.
E 5
I 5
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
E 5
 *
D 5
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
E 5
I 5
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 6
E 5
 */

D 5
#ifndef	lint
E 5
I 5
#ifndef lint
E 5
D 3
static	char	sccsid[] = "@(#)options.c	3.1  10/29/86";
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
D 5
#endif	/* ndef lint */
E 5
I 5
#endif /* not lint */
E 5

/*
 * this file contains the definitions, initialization, and processing of
 *	commands to handle the various local options (APL ON, etc.)
 */

#include "options.h"

D 2
#include "../system/globals.h"
E 2
I 2
#include "../general/globals.h"
E 2
D 7
#include "options.ext"
E 7
I 7
#include "declare.h"
E 7

void
OptInit()
{
    register int i;

    OptAPLmode = 0;
    OptNullProcessing = 1;		/* improved null processing */
    OptZonesMode = 0;		/* zones mode off */
    OptEnterNL = 0;		/* regular enter/new line keys */
    OptColFieldTab = 0;		/* regular column/field tab keys */
    OptPacing = 1;			/* do pacing */
    OptAlphaInNumeric = 0;		/* allow alpha in numeric fields */
    for (i = 0; i < sizeof OptColTabs; i++) {
	OptColTabs[i] = ((i%8) == 0);	/* every 8 columns */
    }
    OptHome = 0;
    OptLeftMargin = 0;
    OptWordWrap = 0;
}

OptOrder(pointer, count, control)
D 7
char *pointer;
E 7
I 7
unsigned char *pointer;
E 7
int count;
int control;
{
    int i, j, character, origCount;

    origCount = count;

    if (count == 0) {
	return(0);
    }
    character = *pointer&0xff;
    pointer++;
    count--;
    switch (character) {
    case 0xa0:
	OptAPLmode = 1;
	break;
    case 0x61:
	OptAPLmode = 0;
	break;
    case 0x95:
	OptNullProcessing = 0;
	break;
    case 0xd5:
	OptNullProcessing = 1;
	break;
    case 0xa9:
	OptZonesMode = 1;
	break;
    case 0xe9:
	OptZonesMode = 0;
	break;
    case 0x85:
	OptEnterNL = 1;
	break;
    case 0xc5:
	OptEnterNL = 0;
	break;
    case 0x83:
	OptColFieldTab = 1;
	break;
    case 0xc3:
	OptColFieldTab = 0;
	break;
    case 0x97:
	OptPacing = 0;
	break;
    case 0xd7:
	OptPacing = 1;
	break;
    case 0xa5:
	OptAlphaInNumeric = 1;
	break;
    case 0xe5:
	OptAlphaInNumeric = 0;
	break;
    case 0xe3:
	if (!control && count < 30) {
	    return(0);		/* want more! */
	}
	for (i = 0; i < sizeof OptColTabs; i++) {
	    OptColTabs[i] = 0;
	}
	if (!count) {
	    break;
	}
	j = (*pointer&0xff)-0x40;
	count--;
	pointer++;
	if (j < 0 || j >= 24) {
	    break;
	}
	OptHome = j;
	if (!count) {
	    break;
	}
	j = (*pointer&0xff)-0x40;
	count--;
	pointer++;
	if (j < 0 || j >= 80) {
	    break;
	}
	OptLeftMargin = j;
	if (!count) {
	    break;
	}
	i = count;
	if (i > 28) {
	    i = 28;
	}
	while (i) {
	    j = (*pointer&0xff)-0x40;
	    if (j < 0 || j >= sizeof OptColTabs) {
		break;
	    }
	    OptColTabs[j] = 1;
	    i --;
	    pointer++;
	    count--;
	}
	break;
    case 0xa6:
	OptWordWrap = 1;
	break;
    case 0xe6:
	OptWordWrap = 0;
	break;
    default:
	break;
    }
    return(origCount - count);
}
E 1
