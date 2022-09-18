h27749
s 00002/00002/00064
d D 8.1 93/05/31 17:25:52 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00065
d D 5.6 90/06/01 13:08:56 bostic 6 5
c new copyright notice
e
s 00002/00001/00074
d D 5.5 90/05/02 14:29:19 bostic 5 4
c use paths.h for /dev/null
e
s 00010/00005/00065
d D 5.4 88/06/18 19:38:38 bostic 4 3
c install approved copyright notice
e
s 00011/00004/00059
d D 5.3 87/12/29 17:17:10 bostic 3 2
c  Berkeley header, comment out debugging code
e
s 00001/00001/00062
d D 5.2 87/04/09 16:59:14 bostic 2 1
c bug report 4.2BSD/games/20
e
s 00063/00000/00000
d D 5.1 86/11/26 13:37:24 bostic 1 0
c date and time created 86/11/26 13:37:24 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1982 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 4
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

I 5
# include	<paths.h>
E 5
# include	"mille.h"

/*
 * @(#)varpush.c	1.1 (Berkeley) 4/1/82
 */

int	read(), write();

/*
 *	push variables around via the routine func() on the file
 * channel file.  func() is either read or write.
 */
varpush(file, func)
reg int	file;
reg int	(*func)(); {

	int	temp;

	(*func)(file, (char *) &Debug, sizeof Debug);
	(*func)(file, (char *) &Finished, sizeof Finished);
	(*func)(file, (char *) &Order, sizeof Order);
	(*func)(file, (char *) &End, sizeof End);
	(*func)(file, (char *) &On_exit, sizeof On_exit);
	(*func)(file, (char *) &Handstart, sizeof Handstart);
	(*func)(file, (char *) &Numgos, sizeof Numgos);
	(*func)(file, (char *)  Numseen, sizeof Numseen);
	(*func)(file, (char *) &Play, sizeof Play);
	(*func)(file, (char *) &Window, sizeof Window);
	(*func)(file, (char *)  Deck, sizeof Deck);
	(*func)(file, (char *) &Discard, sizeof Discard);
	(*func)(file, (char *)  Player, sizeof Player);
	if (func == read) {
		read(file, (char *) &temp, sizeof temp);
		Topcard = &Deck[temp];
I 3
#ifdef DEBUG
E 3
		if (Debug) {
			char	buf[80];
over:
			printf("Debug file:");
			gets(buf);
			if ((outf = fopen(buf, "w")) == NULL) {
				perror(buf);
				goto over;
			}
D 5
			if (strcmp(buf, "/dev/null") != 0)
E 5
I 5
			if (strcmp(buf, _PATH_DEVNULL) != 0)
E 5
D 2
				setbuf(outf, NULL);
E 2
I 2
				setbuf(outf, (char *)NULL);
E 2
		}
I 3
#endif
E 3
	}
	else {
		temp = Topcard - Deck;
		write(file, (char *) &temp, sizeof temp);
	}
}
D 3

E 3
E 1
