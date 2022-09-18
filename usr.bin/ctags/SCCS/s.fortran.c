h62928
s 00001/00001/00141
d D 8.3 94/04/02 10:08:37 pendry 8 7
c add 1994 copyright
e
s 00037/00024/00105
d D 8.2 94/04/01 13:02:01 pendry 7 6
c prettyness police
e
s 00002/00002/00127
d D 8.1 93/06/06 14:29:47 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00003/00123
d D 5.5 91/02/26 13:42:16 bostic 5 4
c ANSI fixes, use strdup instead of rolling your own
e
s 00001/00011/00125
d D 5.4 90/06/01 15:58:23 bostic 4 3
c new copyright notice
e
s 00001/00001/00135
d D 5.3 90/05/15 19:51:06 bostic 3 2
c string.h is ANSI C include file
e
s 00015/00004/00121
d D 5.2 88/12/31 12:32:31 bostic 2 1
c original by Ken Arnold -- Berkeley copyright
e
s 00125/00000/00000
d D 5.1 87/03/16 17:57:33 bostic 1 0
c date and time created 87/03/16 17:57:33 by bostic
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

D 5
char	*lbp;				/* line buffer pointer */
E 5
I 5
D 7
static void takeprec();
E 7
I 7
static void takeprec __P((void));
E 7
E 5

I 5
char *lbp;				/* line buffer pointer */

I 7
int
E 7
E 5
PF_funcs()
{
D 7
	register bool	pfcnt;		/* pascal/fortran functions found */
	register char	*cp;
	char	tok[MAXTOKEN],
		*gettoken();
E 7
I 7
	bool	pfcnt;			/* pascal/fortran functions found */
	char	*cp;
	char	tok[MAXTOKEN];
E 7

	for (pfcnt = NO;;) {
		lineftell = ftell(inf);
D 7
		if (!fgets(lbuf,sizeof(lbuf),inf))
			return(pfcnt);
E 7
I 7
		if (!fgets(lbuf, sizeof(lbuf), inf))
			return (pfcnt);
E 7
		++lineno;
		lbp = lbuf;
		if (*lbp == '%')	/* Ratfor escape to fortran */
			++lbp;
D 7
		for (;isspace(*lbp);++lbp);
E 7
I 7
		for (; isspace(*lbp); ++lbp)
			continue;
E 7
		if (!*lbp)
			continue;
		switch (*lbp | ' ') {	/* convert to lower-case */
		case 'c':
			if (cicmp("complex") || cicmp("character"))
				takeprec();
			break;
		case 'd':
			if (cicmp("double")) {
D 7
				for (;isspace(*lbp);++lbp);
E 7
I 7
				for (; isspace(*lbp); ++lbp)
					continue;
E 7
				if (!*lbp)
					continue;
				if (cicmp("precision"))
					break;
				continue;
			}
			break;
		case 'i':
			if (cicmp("integer"))
				takeprec();
			break;
		case 'l':
			if (cicmp("logical"))
				takeprec();
			break;
		case 'r':
			if (cicmp("real"))
				takeprec();
			break;
		}
D 7
		for (;isspace(*lbp);++lbp);
E 7
I 7
		for (; isspace(*lbp); ++lbp)
			continue;
E 7
		if (!*lbp)
			continue;
		switch (*lbp | ' ') {
		case 'f':
			if (cicmp("function"))
				break;
			continue;
		case 'p':
			if (cicmp("program") || cicmp("procedure"))
				break;
			continue;
		case 's':
			if (cicmp("subroutine"))
				break;
		default:
			continue;
		}
D 7
		for (;isspace(*lbp);++lbp);
E 7
I 7
		for (; isspace(*lbp); ++lbp)
			continue;
E 7
		if (!*lbp)
			continue;
D 7
		for (cp = lbp + 1;*cp && intoken(*cp);++cp);
E 7
I 7
		for (cp = lbp + 1; *cp && intoken(*cp); ++cp)
			continue;
E 7
		if (cp = lbp + 1)
			continue;
		*cp = EOS;
D 7
		(void)strcpy(tok,lbp);
E 7
I 7
		(void)strcpy(tok, lbp);
E 7
		getline();			/* process line for ex(1) */
D 7
		pfnote(tok,lineno);
E 7
I 7
		pfnote(tok, lineno);
E 7
		pfcnt = YES;
	}
	/*NOTREACHED*/
}

/*
 * cicmp --
 *	do case-independent strcmp
 */
I 7
int
E 7
cicmp(cp)
D 7
	register char	*cp;
E 7
I 7
	char	*cp;
E 7
{
D 7
	register int	len;
	register char	*bp;
E 7
I 7
	int	len;
	char	*bp;
E 7

D 7
	for (len = 0,bp = lbp;*cp && (*cp &~ ' ') == (*bp++ &~ ' ');
	    ++cp,++len);
E 7
I 7
	for (len = 0, bp = lbp; *cp && (*cp &~ ' ') == (*bp++ &~ ' ');
	    ++cp, ++len)
		continue;
E 7
	if (!*cp) {
		lbp += len;
D 7
		return(YES);
E 7
I 7
		return (YES);
E 7
	}
D 7
	return(NO);
E 7
I 7
	return (NO);
E 7
}

D 5
static
E 5
I 5
static void
E 5
takeprec()
{
D 7
	for (;isspace(*lbp);++lbp);
E 7
I 7
	for (; isspace(*lbp); ++lbp)
		continue;
E 7
	if (*lbp == '*') {
D 7
		for (++lbp;isspace(*lbp);++lbp);
E 7
I 7
		for (++lbp; isspace(*lbp); ++lbp)
			continue;
E 7
		if (!isdigit(*lbp))
			--lbp;			/* force failure */
		else
D 7
			while (isdigit(*++lbp));
E 7
I 7
			while (isdigit(*++lbp))
				continue;
E 7
	}
}
E 1
