h54522
s 00002/00002/00028
d D 8.1 93/06/04 16:48:31 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00013/00021
d D 5.5 92/08/23 11:12:24 bostic 8 6
c KNF, lint
e
s 00008/00012/00022
d R 5.5 92/05/15 15:24:28 bostic 7 6
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00033
d D 5.4 90/06/01 15:39:13 bostic 6 5
c new copyright notice
e
s 00010/00005/00034
d D 5.3 88/06/30 17:21:46 bostic 5 4
c install approved copyright notice
e
s 00010/00004/00029
d D 5.2 88/06/08 13:57:22 bostic 4 3
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00023
d D 5.1 85/06/07 11:35:29 dist 3 2
c Add copyright
e
s 00004/00005/00020
d D 1.2 85/05/01 17:18:19 bloom 2 1
c new version from arnold
e
s 00025/00000/00000
d D 1.1 81/01/26 17:02:59 arnold 1 0
c date and time created 81/01/26 17:02:59 by arnold
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 9
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1981, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 8
#endif /* not lint */
E 8
I 8
#endif	/* not lint */
E 8
E 4

E 3
I 1
D 8
# define	reg	register

E 8
/*
D 8
 *	This routine fills in "def" with the long name of the terminal.
 *
E 8
I 8
 * longname --
 *	Fill in "def" with the long name of the terminal.
E 8
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */
char *
longname(bp, def)
D 8
reg char	*bp, *def; {
E 8
I 8
	register char *bp, *def;
{
	register char *cp;
E 8

D 8
	reg char	*cp;

E 8
	while (*bp && *bp != ':' && *bp != '|')
		bp++;
	if (*bp == '|') {
D 8
		bp++;
D 2
		cp = bp;
		while (*cp && *cp != ':' && *cp != '|')
			cp++;
E 2
I 2
		cp = def;
		while (*bp && *bp != ':' && *bp != '|')
E 8
I 8
		for (cp = def, ++bp; *bp && *bp != ':' && *bp != '|';)
E 8
			*cp++ = *bp++;
E 2
D 8
		*cp = 0;
E 8
I 8
		*cp = '\0';
E 8
D 2
		return bp;
E 2
	}
D 8
	return def;
E 8
I 8
	return (def);
E 8
}
E 1
