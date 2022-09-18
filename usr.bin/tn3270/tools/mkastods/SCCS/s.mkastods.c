h46825
s 00005/00005/00046
d D 8.1 93/06/06 16:49:31 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00014/00047
d D 4.2 91/04/26 16:06:00 bostic 9 8
c new copyright; att/bsd/shared
e
s 00000/00000/00061
d D 4.1 88/12/04 15:13:05 minshall 8 7
c Release 4.1
e
s 00010/00005/00051
d D 3.3 88/06/29 20:04:46 bostic 7 6
c install approved copyright notice
e
s 00015/00019/00041
d D 3.2 88/03/28 12:08:16 bostic 6 5
c add Berkeley specific headers
e
s 00000/00000/00060
d D 3.1 87/08/11 10:20:50 minshall 5 4
c New version numbering.
e
s 00025/00000/00035
d D 1.4 87/07/17 10:06:25 minshall 4 3
c Install sccs headers and copyright notices.
e
s 00002/00002/00033
d D 1.3 87/07/15 15:27:23 minshall 3 2
c New directory structure.
e
s 00003/00003/00032
d D 1.2 87/06/19 12:52:54 minshall 2 1
c Directory changes.
e
s 00035/00000/00000
d D 1.1 87/05/21 21:58:55 minshall 1 0
c date and time created 87/05/21 21:58:55 by minshall
e
u
U
t
T
I 4
D 9
/*
D 6
 *	Copyright (c) 1984-1987 by the Regents of the
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

#ifndef lint
I 6
D 10
char copyright[] =
D 9
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
E 9
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
#endif /* not lint */

#ifndef lint
E 6
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif	/* not lint */
E 6
I 6
#endif /* not lint */
E 6

E 4
I 1
#include <stdio.h>
#if	defined(unix)
#include <strings.h>
#else	/* defined(unix) */
#include <string.h>
#endif	/* defined(unix) */
#include <ctype.h>
D 2
#include "../ascii/ascebc.h"
#include "../ctlr/ebc_disp.h"
E 2
I 2
D 3
#include "../apilib/asc_ebc.h"
#include "../apilib/ebc_disp.h"
E 3
I 3
#include "../api/asc_ebc.h"
#include "../api/ebc_disp.h"
E 3
E 2
D 6

E 6

int
main()
{
    int i;

    /* For each ascii code, find the display code that matches */

    printf("unsigned char asc_disp[256] = {");
    for (i = 0; i < NASCII; i++) {
	if ((i%8) == 0) {
	    printf("\n");
	}
D 2
	printf("\t0x%02x,", ebc_disp[ascebc[0][i]]);
E 2
I 2
	printf("\t0x%02x,", ebc_disp[asc_ebc[i]]);
E 2
    }
    for (i = sizeof disp_ebc; i < 256; i++) {
	if ((i%8) == 0) {
	    printf("\n");
	}
	printf("\t0x%02x,", 0);
    }
    printf("\n};\n");

    return 0;
}
E 1
