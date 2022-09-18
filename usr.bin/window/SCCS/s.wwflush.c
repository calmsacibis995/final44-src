h26563
s 00002/00002/00080
d D 8.1 93/06/06 22:32:01 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00051/00001/00031
d D 3.13 92/11/10 11:49:44 edward 13 12
c checkpointing stuff
e
s 00003/00000/00029
d D 3.12 90/06/06 21:45:18 bostic 12 11
c fix contrib notice (Edward Wang)
e
s 00001/00011/00028
d D 3.11 90/06/02 15:24:01 bostic 11 10
c new copyright notice
e
s 00012/00006/00027
d D 3.10 89/08/02 19:13:01 edward 10 9
c data compression and some other stuff
e
s 00010/00005/00023
d D 3.9 88/06/29 21:38:05 bostic 9 8
c install approved copyright notice
e
s 00013/00007/00015
d D 3.8 88/02/21 13:38:21 bostic 8 7
c written by Edward Wang; attach Berkeley specific copyright
e
s 00006/00000/00016
d D 3.7 85/04/24 16:16:44 edward 7 6
c copyright messages
e
s 00001/00001/00015
d D 3.6 84/05/23 01:58:49 edward 6 5
c new sccs id
e
s 00001/00001/00015
d D 3.5 84/03/03 22:46:54 edward 5 4
c interrupt driven input
e
s 00005/00001/00011
d D 3.4 83/09/14 14:16:31 edward 4 3
c Off screen windows!!!!!!
e
s 00001/00000/00011
d D 3.3 83/08/15 18:15:16 edward 3 2
c tt cleanup
e
s 00000/00000/00011
d D 3.2 83/08/11 17:24:37 edward 2 1
i
c last few day's work
e
s 00011/00000/00000
d D 3.1 83/08/09 18:37:51 edward 1 0
c date and time created 83/08/09 18:37:51 by edward
e
u
U
t
T
I 1
D 8
#ifndef lint
D 6
static	char *sccsid = "%W% %E%";
E 6
I 6
static char sccsid[] = "%W% %G%";
E 6
#endif

E 8
I 7
/*
D 8
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 8
I 8
D 14
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
I 12
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 12
D 11
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
E 8
 */
I 8

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8

E 7
#include "ww.h"
I 3
#include "tt.h"
I 13
#include <sys/signal.h>
E 13
E 3

wwflush()
{
D 4
	(*tt.tt_move)(wwcursorrow, wwcursorcol);
E 4
I 4
D 10
	if (wwcursorrow < 0 || wwcursorrow >= wwnrow
	    || wwcursorcol < 0 || wwcursorcol >= wwncol)
		(*tt.tt_move)(0, 0);
	else
		(*tt.tt_move)(wwcursorrow, wwcursorcol);
E 4
D 5
	(void) fflush(stdout);
E 5
I 5
	ttflush();
E 10
I 10
	register row, col;

	if ((row = wwcursorrow) < 0)
		row = 0;
	else if (row >= wwnrow)
		row = wwnrow - 1;
	if ((col = wwcursorcol) < 0)
		col = 0;
	else if (col >= wwncol)
		col = wwncol - 1;
	xxmove(row, col);
D 13
	xxflush(1);
E 13
I 13
	if (wwdocheckpoint) {
		xxflush(0);
		wwcheckpoint();
	} else
		xxflush(1);
}

wwcheckpoint()
{
	int s = sigblock(sigmask(SIGALRM) | sigmask(SIGIO));

	tt.tt_ack = 0;
	do {
		(*tt.tt_checkpoint)();
#ifndef OLD_TTY
		(void) tcdrain(1);
#endif
		(void) alarm(3);
		for (wwdocheckpoint = 0; !wwdocheckpoint && tt.tt_ack == 0;)
			(void) sigpause(s);
	} while (tt.tt_ack == 0);
	(void) alarm(0);
	wwdocheckpoint = 0;
	if (tt.tt_ack < 0) {
		wwcopyscreen(wwcs, wwos);
		(void) alarm(1);
		wwreset();
		wwupdate();
		wwflush();
	} else {
		wwcopyscreen(wwos, wwcs);
		(void) alarm(3);
	}
	(void) sigsetmask(s);
}

wwcopyscreen(s1, s2)
	register union ww_char **s1, **s2;
{
	register i;
	register s = wwncol * sizeof **s1;

	for (i = wwnrow; --i >= 0;)
		bcopy((char *) *s1++, (char *) *s2++, s);
}

void
wwalarm()
{
	wwdocheckpoint = 1;
E 13
E 10
E 5
}
E 1
