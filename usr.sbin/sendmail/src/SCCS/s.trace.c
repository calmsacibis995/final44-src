h20011
s 00002/00000/00105
d D 8.4 95/05/28 11:49:04 eric 13 12
c lint
e
s 00001/00001/00104
d D 8.3 95/04/21 09:56:39 eric 12 11
c update copyright notice
e
s 00002/00002/00103
d D 8.2 94/03/14 09:41:02 eric 11 10
c SECURITY PROBLEM: wierd values to -d could give you root!
e
s 00002/00002/00103
d D 8.1 93/06/07 10:32:29 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00105
d D 6.1 92/12/21 16:07:55 eric 9 8
c Release 6
e
s 00001/00011/00104
d D 5.6 90/06/01 19:04:51 bostic 8 7
c new copyright notice
e
s 00011/00009/00104
d D 5.5 88/06/30 15:00:00 bostic 7 6
c install approved copyright notice
e
s 00016/00010/00097
d D 5.4 88/03/13 19:53:27 bostic 6 5
c add Berkeley specific header
e
s 00000/00001/00107
d D 5.3 86/12/17 16:05:32 eric 5 4
c delete unneeded #include <ctype.h>
e
s 00000/00002/00108
d D 5.2 85/06/07 22:20:35 miriam 4 3
m 
c Resolve duplicate SccsId
e
s 00014/00000/00096
d D 5.1 85/06/07 15:20:58 dist 3 2
m 
c Add copyright
e
s 00000/00000/00096
d D 4.1 83/07/25 19:43:24 eric 2 1
m 
c 4.2 release version
e
s 00096/00000/00000
d D 3.1 82/08/08 00:37:36 eric 1 0
c date and time created 82/08/08 00:37:36 by eric
e
u
U
f b 
f i 
t
T
I 3
/*
I 7
D 12
 * Copyright (c) 1983 Eric P. Allman
E 12
I 12
 * Copyright (c) 1983, 1995 Eric P. Allman
E 12
E 7
D 6
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 6
I 6
D 10
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
 */
E 6

#ifndef lint
D 6
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 6
I 6
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

E 3
I 1
D 5
# include <ctype.h>
E 5
# include "sendmail.h"

D 4
SCCSID(%W%	%Y%	%G%);

E 4
/*
**  TtSETUP -- set up for trace package.
**
**	Parameters:
**		vect -- pointer to trace vector.
**		size -- number of flags in trace vector.
**		defflags -- flags to set if no value given.
**
**	Returns:
**		none
**
**	Side Effects:
**		environment is set up.
*/

u_char		*tTvect;
int		tTsize;
static char	*DefFlags;

I 13
void
E 13
tTsetup(vect, size, defflags)
	u_char *vect;
	int size;
	char *defflags;
{
	tTvect = vect;
	tTsize = size;
	DefFlags = defflags;
}
/*
**  TtFLAG -- process an external trace flag description.
**
**	Parameters:
**		s -- the trace flag.
**
**	Returns:
**		none.
**
**	Side Effects:
**		sets/clears trace flags.
*/

I 13
void
E 13
tTflag(s)
	register char *s;
{
D 11
	int first, last;
	register int i;
E 11
I 11
	unsigned int first, last;
	register unsigned int i;
E 11

	if (*s == '\0')
		s = DefFlags;

	for (;;)
	{
		/* find first flag to set */
		i = 0;
		while (isdigit(*s))
			i = i * 10 + (*s++ - '0');
		first = i;

		/* find last flag to set */
		if (*s == '-')
		{
			i = 0;
			while (isdigit(*++s))
				i = i * 10 + (*s - '0');
		}
		last = i;

		/* find the level to set it to */
		i = 1;
		if (*s == '.')
		{
			i = 0;
			while (isdigit(*++s))
				i = i * 10 + (*s - '0');
		}

		/* clean up args */
		if (first >= tTsize)
			first = tTsize - 1;
		if (last >= tTsize)
			last = tTsize - 1;

		/* set the flags */
		while (first <= last)
			tTvect[first++] = i;

		/* more arguments? */
		if (*s++ == '\0')
			return;
	}
}
E 1
