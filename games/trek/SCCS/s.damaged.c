h25210
s 00002/00002/00039
d D 8.1 93/05/31 17:55:59 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00040
d D 5.4 90/06/01 13:22:47 bostic 5 4
c new copyright notice
e
s 00010/00005/00041
d D 5.3 88/06/18 15:07:21 bostic 4 3
c install approved copyright notice
e
s 00009/00003/00037
d D 5.2 88/05/05 18:33:30 bostic 3 2
c written by Eric Allman; add Berkeley header
e
s 00007/00001/00033
d D 5.1 85/05/30 08:51:04 dist 2 1
c Add copyright
e
s 00034/00000/00000
d D 4.1 83/03/23 14:58:45 mckusick 1 0
c date and time created 83/03/23 14:58:45 by mckusick
e
u
U
t
T
I 2
/*
D 6
 * Copyright (c) 1980 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W%	(Berkeley)	%G%";
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

# include	"trek.h"

/*  DAMAGED -- check for device damaged
**
**	This is a boolean function which returns non-zero if the
**	specified device is broken.  It does this by checking the
**	event list for a "device fix" action on that device.
*/

damaged(dev)
int	dev;
{
	register int		d;
	register struct event	*e;
	register int		i;

	d = dev;

	for (i = 0; i < MAXEVENTS; i++)
	{
		e = &Event[i];
		if (e->evcode != E_FIXDV)
			continue;
		if (e->systemname == d)
			return (1);
	}

	/* device fix not in event list -- device must not be broken */
	return (0);
}
E 1
