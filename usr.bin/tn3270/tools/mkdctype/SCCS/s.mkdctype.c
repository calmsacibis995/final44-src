h01658
s 00005/00005/00068
d D 8.1 93/06/06 16:50:00 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00014/00069
d D 4.2 91/04/26 16:06:01 bostic 10 9
c new copyright; att/bsd/shared
e
s 00000/00000/00083
d D 4.1 88/12/04 15:12:58 minshall 9 8
c Release 4.1
e
s 00010/00005/00073
d D 3.3 88/06/29 20:04:49 bostic 8 7
c install approved copyright notice
e
s 00015/00018/00063
d D 3.2 88/03/28 12:08:19 bostic 7 6
c add Berkeley specific headers
e
s 00000/00000/00081
d D 3.1 87/08/11 10:20:40 minshall 6 5
c New version numbering.
e
s 00025/00000/00056
d D 1.5 87/07/17 10:06:01 minshall 5 4
c Install sccs headers and copyright notices.
e
s 00001/00001/00055
d D 1.4 87/07/15 15:27:12 minshall 4 3
c New directory structure.
e
s 00001/00001/00055
d D 1.3 87/06/19 12:52:45 minshall 3 2
c Directory changes.
e
s 00001/00001/00055
d D 1.2 87/05/12 14:10:39 minshall 2 1
c Various fixes for running under dos.
e
s 00056/00000/00000
d D 1.1 86/11/12 16:44:15 minshall 1 0
c date and time created 86/11/12 16:44:15 by minshall
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

#ifndef lint
I 7
D 11
char copyright[] =
D 10
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 10
I 10
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
E 10
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 11
#endif /* not lint */

#ifndef lint
E 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif	/* not lint */
E 7
I 7
#endif /* not lint */
E 7

E 5
I 1
D 3
#include "../ctlr/ebc_disp.h"
E 3
I 3
D 4
#include "../apilib/ebc_disp.h"
E 4
I 4
#include "../api/ebc_disp.h"
E 4
E 3
#include "ectype.h"


extern unsigned char ectype[256];


void
main()
{
D 2
    static unsigned char dctype[192] = 0;
E 2
I 2
    static unsigned char dctype[192] = { 0 };
E 2
    int i;
    char *orbar;
    int type;

    for (i = 0; i < sizeof ectype; i++) {
	dctype[ebc_disp[i]] = ectype[i];
    }

    for (i = 0; i < sizeof dctype; i++) {
	if ((i%16) == 0) {
	    printf("/*%02x*/\n", i);
	}
	printf("\t");
	type = dctype[i];
	orbar = "";
	if (type & E_UPPER) {
	    printf("E_UPPER");
	    orbar = "|";
	}
	if (type & E_LOWER) {
	    printf("%sD_LOWER", orbar);
	    orbar = "|";
	}
	if (type & E_DIGIT) {
	    printf("%sD_DIGIT", orbar);
	    orbar = "|";
	}
	if (type & E_SPACE) {
	    printf("%sD_SPACE", orbar);
	    orbar = "|";
	}
	if (type & E_PUNCT) {
	    printf("%sD_PUNCT", orbar);
	    orbar = "|";
	}
	if (type & E_PRINT) {
	    printf("%sD_PRINT", orbar);
	    orbar = "|";
	}
	if (orbar[0] == 0) {
	    printf("0");
	}
	printf(",\n");
    }
}
E 1
