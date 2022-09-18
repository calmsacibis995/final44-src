h33413
s 00002/00002/00061
d D 8.1 93/05/31 17:58:23 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00059
d D 5.5 90/06/26 21:43:26 bostic 6 5
c setexit and reset are gone; use setjmp/longjmp
e
s 00001/00011/00060
d D 5.4 90/06/01 13:27:11 bostic 5 4
c new copyright notice
e
s 00010/00005/00061
d D 5.3 88/06/18 15:08:39 bostic 4 3
c install approved copyright notice
e
s 00009/00003/00057
d D 5.2 88/05/05 18:35:07 bostic 3 2
c written by Eric Allman; add Berkeley header
e
s 00007/00001/00053
d D 5.1 85/05/30 09:06:26 dist 2 1
c Add copyright
e
s 00054/00000/00000
d D 4.1 83/03/23 15:02:19 mckusick 1 0
c date and time created 83/03/23 15:02:19 by mckusick
e
u
U
t
T
I 2
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
# include	"getpar.h"
I 6
# include	<setjmp.h>
E 6

/*
**  Signal game won
**
**	This routine prints out the win message, arranges to print out
**	your score, tells you if you have a promotion coming to you,
**	cleans up the current input line, and arranges to have you
D 6
**	asked whether or not you want another game (via the reset()
E 6
I 6
**	asked whether or not you want another game (via the longjmp()
E 6
**	call).
**
**	Pretty straightforward, although the promotion algorithm is
**	pretty off the wall.
*/

win()
{
	long			s;
I 6
	extern jmp_buf		env;
E 6
	extern long		score();
	extern struct cvntab	Skitab[];
	register struct cvntab	*p;

	sleep(1);
	printf("\nCongratulations, you have saved the Federation\n");
	Move.endgame = 1;

	/* print and return the score */
	s = score();

	/* decide if she gets a promotion */
	if (Game.helps == 0 && Game.killb == 0 && Game.killinhab == 0 && 5 * Game.kills + Game.deaths < 100 &&
			s >= 1000 && Ship.ship == ENTERPRISE)
	{
		printf("In fact, you are promoted one step in rank,\n");
		if (Game.skill >= 6)
			printf("to the exalted rank of Commodore Emeritus\n");
		else
		{
			p = &Skitab[Game.skill - 1];
			printf("from %s%s ", p->abrev, p->full);
			p++;
			printf("to %s%s\n", p->abrev, p->full);
		}
	}

	/* clean out input, and request new game */
	skiptonl(0);
D 6
	reset();
E 6
I 6
	longjmp(env, 1);
E 6
}
E 1
