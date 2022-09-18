h42387
s 00002/00002/00124
d D 8.1 93/05/31 17:56:50 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00125
d D 5.4 90/06/01 13:24:19 bostic 7 6
c new copyright notice
e
s 00010/00005/00126
d D 5.3 88/06/18 15:07:46 bostic 6 5
c install approved copyright notice
e
s 00009/00003/00122
d D 5.2 88/05/05 18:34:03 bostic 5 4
c written by Eric Allman; add Berkeley header
e
s 00007/00001/00118
d D 5.1 85/05/30 08:55:01 dist 4 3
c Add copyright
e
s 00001/00001/00118
d D 4.3 83/05/27 00:34:01 layer 3 2
c finished conversion to 4.1c
e
s 00001/00001/00118
d D 4.2 83/05/09 21:54:53 layer 2 1
c conversion of source code to 4.1c BSD
e
s 00119/00000/00000
d D 4.1 83/03/23 14:59:52 mckusick 1 0
c date and time created 83/03/23 14:59:52 by mckusick
e
u
U
t
T
I 4
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
E 5
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W%	(Berkeley)	%G%";
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

# include	"trek.h"

/*
**  Paramize Quadrant Upon Entering
**
**	A quadrant is initialized from the information held in the
**	Quad matrix.  Basically, everything is just initialized
**	randomly, except for the starship, which goes into a fixed
**	sector.
**
**	If there are Klingons in the quadrant, the captain is informed
**	that the condition is RED, and he is given a chance to put
**	his shields up if the computer is working.
**
**	The flag `f' is set to disable the check for condition red.
**	This mode is used in situations where you know you are going
**	to be docked, i.e., abandon() and help().
*/

initquad(f)
int	f;
{
	register int		i, j;
	int			rx, ry;
	int			nbases, nstars;
	register struct quad	*q;
	int			nholes;

	q = &Quad[Ship.quadx][Ship.quady];

	/* ignored supernova'ed quadrants (this is checked again later anyway */
	if (q->stars < 0)
		return;
	Etc.nkling = q->klings;
	nbases = q->bases;
	nstars = q->stars;
	nholes = q->holes;

	/* have we blundered into a battle zone w/ shields down? */
	if (Etc.nkling > 0 && !f)
	{
		printf("Condition RED\n");
		Ship.cond = RED;
		if (!damaged(COMPUTER))
			shield(1);
	}

	/* clear out the quadrant */
	for (i = 0; i < NSECTS; i++)
		for (j = 0; j < NSECTS; j++)
			Sect[i][j] = EMPTY;

	/* initialize Enterprise */
	Sect[Ship.sectx][Ship.secty] = Ship.ship;

	/* initialize Klingons */
	for (i = 0; i < Etc.nkling; i++)
	{
		sector(&rx, &ry);
		Sect[rx][ry] = KLINGON;
		Etc.klingon[i].x = rx;
		Etc.klingon[i].y = ry;
		Etc.klingon[i].power = Param.klingpwr;
		Etc.klingon[i].srndreq = 0;
	}
	compkldist(1);

	/* initialize star base */
	if (nbases > 0)
	{
		sector(&rx, &ry);
		Sect[rx][ry] = BASE;
		Etc.starbase.x = rx;
		Etc.starbase.y = ry;
	}

	/* initialize inhabited starsystem */
D 3
	if (q->systemname != 0)
E 3
I 3
	if (q->qsystemname != 0)
E 3
	{
		sector(&rx, &ry);
		Sect[rx][ry] = INHABIT;
D 2
		nstars =- 1;
E 2
I 2
		nstars -= 1;
E 2
	}

	/* initialize black holes */
	for (i = 0; i < nholes; i++)
	{
		sector(&rx, &ry);
		Sect[rx][ry] = HOLE;
	}

	/* initialize stars */
	for (i = 0; i < nstars; i++)
	{
		sector(&rx, &ry);
		Sect[rx][ry] = STAR;
	}
	Move.newquad = 1;
}


sector(x, y)
int	*x, *y;
{
	register int		i, j;

	do
	{
		i = ranf(NSECTS);
		j = ranf(NSECTS);
	} while (Sect[i][j] != EMPTY);
	*x = i;
	*y = j;
	return;
}
E 1
