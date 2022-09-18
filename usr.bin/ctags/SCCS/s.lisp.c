h26017
s 00001/00001/00078
d D 8.3 94/04/02 10:08:41 pendry 8 7
c add 1994 copyright
e
s 00023/00015/00056
d D 8.2 94/04/01 13:01:59 pendry 7 6
c prettyness police
e
s 00002/00002/00069
d D 8.1 93/06/06 14:29:50 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00069
d D 5.5 91/02/26 13:42:17 bostic 5 4
c ANSI fixes, use strdup instead of rolling your own
e
s 00001/00011/00069
d D 5.4 90/06/01 15:58:28 bostic 4 3
c new copyright notice
e
s 00001/00001/00079
d D 5.3 90/05/15 19:51:07 bostic 3 2
c string.h is ANSI C include file
e
s 00015/00004/00065
d D 5.2 88/12/31 12:32:32 bostic 2 1
c original by Ken Arnold -- Berkeley copyright
e
s 00069/00000/00000
d D 5.1 87/03/16 17:57:34 bostic 1 0
c date and time created 87/03/16 17:57:34 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
D 6
 * Copyright (c) 1987 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 8
 * Copyright (c) 1987, 1993
E 8
I 8
 * Copyright (c) 1987, 1993, 1994
E 8
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

I 7
#include <ctype.h>
#include <limits.h>
E 7
D 5
#include <ctags.h>
E 5
I 5
#include <stdio.h>
E 5
D 3
#include <strings.h>
E 3
I 3
#include <string.h>
I 7

E 7
I 5
#include "ctags.h"
E 5
E 3

D 7
extern char	*lbp;			/* pointer shared with fortran */

E 7
/*
 * lisp tag functions
 * just look for (def or (DEF
 */
I 7
void
E 7
l_entries()
{
D 7
	register int	special;
	register char	*cp,
			savedc;
E 7
I 7
	int	special;
	char	*cp;
	char	savedc;
E 7
	char	tok[MAXTOKEN];

	for (;;) {
		lineftell = ftell(inf);
D 7
		if (!fgets(lbuf,sizeof(lbuf),inf))
E 7
I 7
		if (!fgets(lbuf, sizeof(lbuf), inf))
E 7
			return;
		++lineno;
		lbp = lbuf;
		if (!cicmp("(def"))
			continue;
		special = NO;
		switch(*lbp | ' ') {
		case 'm':
			if (cicmp("method"))
				special = YES;
			break;
		case 'w':
			if (cicmp("wrapper") || cicmp("whopper"))
				special = YES;
		}
D 7
		for (;!isspace(*lbp);++lbp);
		for (;isspace(*lbp);++lbp);
		for (cp = lbp;*cp && *cp != '\n';++cp);
E 7
I 7
		for (; !isspace(*lbp); ++lbp)
			continue;
		for (; isspace(*lbp); ++lbp)
			continue;
		for (cp = lbp; *cp && *cp != '\n'; ++cp)
			continue;
E 7
		*cp = EOS;
		if (special) {
D 7
			if (!(cp = index(lbp,')')))
E 7
I 7
			if (!(cp = strchr(lbp, ')')))
E 7
				continue;
D 7
			for (;cp >= lbp && *cp != ':';--cp);
E 7
I 7
			for (; cp >= lbp && *cp != ':'; --cp)
				continue;
E 7
			if (cp < lbp)
				continue;
			lbp = cp;
D 7
			for (;*cp && *cp != ')' && *cp != ' ';++cp);
E 7
I 7
			for (; *cp && *cp != ')' && *cp != ' '; ++cp)
				continue;
E 7
		}
		else
			for (cp = lbp + 1;
D 7
			    *cp && *cp != '(' && *cp != ' ';++cp);
E 7
I 7
			    *cp && *cp != '(' && *cp != ' '; ++cp)
				continue;
E 7
		savedc = *cp;
		*cp = EOS;
D 7
		(void)strcpy(tok,lbp);
E 7
I 7
		(void)strcpy(tok, lbp);
E 7
		*cp = savedc;
		getline();
D 7
		pfnote(tok,lineno);
E 7
I 7
		pfnote(tok, lineno);
E 7
	}
	/*NOTREACHED*/
}
E 1
