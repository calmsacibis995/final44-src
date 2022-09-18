h36419
s 00002/00002/00047
d D 8.1 93/05/31 17:22:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00022/00044
d D 5.4 93/02/03 17:17:08 torek 4 3
c rm pdp11 ifdefs, rm private bogus abs(), fix call to fseek
e
s 00001/00011/00065
d D 5.3 90/06/01 13:07:07 bostic 3 2
c new copyright notice
e
s 00011/00006/00065
d D 5.2 88/06/18 14:44:35 bostic 2 1
c install approved copyright notice
e
s 00071/00000/00000
d D 5.1 87/12/22 13:08:07 bostic 1 0
c date and time created 87/12/22 13:08:07 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
E 2
I 2
D 5
 * Copyright (c) 1983 Regents of the University of California.
E 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 3
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 4
# include	"hangman.h"
E 4
I 4
#include "hangman.h"
#include <stdlib.h>
E 4

D 4
# if pdp11
#	define	RN	(((off_t) rand() << 16) | (off_t) rand())
# else
#	define	RN	rand()
# endif

E 4
/*
 * getword:
 *	Get a valid word out of the dictionary file
 */
getword()
{
	register FILE		*inf;
	register char		*wp, *gp;
I 4
	register long		 pos;
E 4

	inf = Dict;
	for (;;) {
D 4
		fseek(inf, abs(RN % Dict_size), 0);
E 4
I 4
		pos = (double)rand() / (RAND_MAX + 1.0) * (double)Dict_size;
		fseek(inf, pos, 0);
E 4
		if (fgets(Word, BUFSIZ, inf) == NULL)
			continue;
		if (fgets(Word, BUFSIZ, inf) == NULL)
			continue;
		Word[strlen(Word) - 1] = '\0';
		if (strlen(Word) < MINLEN)
			continue;
		for (wp = Word; *wp; wp++)
			if (!islower(*wp))
				goto cont;
		break;
cont:		;
	}
	gp = Known;
	wp = Word;
	while (*wp) {
		*gp++ = '-';
		wp++;
	}
	*gp = '\0';
D 4
}

/*
 * abs:
 *	Return the absolute value of an integer
 */
off_t
abs(i)
off_t	i;
{
	if (i < 0)
		return -(off_t) i;
	else
		return (off_t) i;
E 4
}
E 1
