h35803
s 00001/00001/00081
d D 8.2 94/04/16 08:15:01 bostic 11 10
c /usr/games/sail uses setruid(), which has been deprecated.
c Take a look at line 51 of dr_main.c, and change the setruid() to
c setuid() -- it sets the uid to 'games', etc., and never gives
c it back, so 'setuid()' is the thing to do.
c From: "Chris G. Demetriou" <cgd@postgres.Berkeley.EDU>
e
s 00002/00002/00080
d D 8.1 93/05/31 17:50:05 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00081
d D 5.5 90/06/01 13:19:19 bostic 9 8
c new copyright notice
e
s 00010/00005/00082
d D 5.4 88/06/18 19:55:25 bostic 8 7
c install approved copyright notice
e
s 00009/00003/00078
d D 5.3 88/03/09 12:30:17 bostic 7 6
c written by David Riggle and Edward Wang; add Berkeley specific copyright
e
s 00001/00000/00080
d D 5.2 86/01/21 18:10:22 edward 6 5
c initialize people to 0
e
s 00005/00005/00075
d D 5.1 85/05/29 16:01:52 dist 5 4
c Add copyright
e
s 00009/00005/00071
d D 2.3 85/04/26 12:14:05 edward 4 2
c return some value from dr_main() (mostly for lint)
e
s 00001/00000/00076
d R 2.3 85/04/25 20:58:56 edward 3 2
c lint
e
s 00006/00000/00070
d D 2.2 85/04/23 21:51:36 edward 2 1
c copyright message
e
s 00070/00000/00000
d D 2.1 85/03/04 18:08:48 edward 1 0
c date and time created 85/03/04 18:08:48 by edward
e
u
U
t
T
I 2
/*
D 5
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 5
I 5
D 10
 * Copyright (c) 1983 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
E 7
E 5
 */

E 2
I 1
#ifndef lint
D 5
static	char *sccsid = "%W% %E%";
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 5

#include "driver.h"

dr_main()
{
	register int n;
	register struct ship *sp;
	int nat[NNATION];
I 4
	int value = 0;
E 4

	(void) signal(SIGINT, SIG_IGN);
	(void) signal(SIGQUIT, SIG_IGN);
	(void) signal(SIGTSTP, SIG_IGN);
	if (issetuid)
D 11
		(void) setruid(geteuid());
E 11
I 11
		(void) setuid(geteuid());
E 11
	if (game < 0 || game >= NSCENE) {
		fprintf(stderr, "DRIVER: Bad game number %d\n", game);
		exit(1);
	}
	cc = &scene[game];
	ls = SHIP(cc->vessels);
	if (sync_open() < 0) {
		perror("driver: syncfile");
		exit(1);
	}
	for (n = 0; n < NNATION; n++)
		nat[n] = 0;
	foreachship(sp) {
		if (sp->file == NULL &&
		    (sp->file = (struct File *)calloc(1, sizeof (struct File))) == NULL) {
			(void) fprintf(stderr, "DRIVER: Out of memory.\n");
			exit(1);
		}
		sp->file->index = sp - SHIP(0);
		sp->file->loadL = L_ROUND;
		sp->file->loadR = L_ROUND;
		sp->file->readyR = R_LOADED|R_INITIAL;
		sp->file->readyL = R_LOADED|R_INITIAL;
		sp->file->stern = nat[sp->nationality]++;
		sp->file->dir = sp->shipdir;
		sp->file->row = sp->shiprow;
		sp->file->col = sp->shipcol;
	}
	windspeed = cc->windspeed;
	winddir = cc->winddir;
I 6
	people = 0;
E 6
	for (;;) {
		sleep(7);
		if (Sync() < 0) {
D 4
			sync_close(1);
			exit(1);
E 4
I 4
			value = 1;
			break;
E 4
		}
D 4
		next();
E 4
I 4
		if (next() < 0)
			break;
E 4
		unfoul();
		checkup();
		prizecheck();
		moveall();
		thinkofgrapples();
		boardcomp();
		compcombat();
		resolve();
		reload();
		checksails();
		if (Sync() < 0) {
D 4
			sync_close(1);
			exit(1);
E 4
I 4
			value = 1;
			break;
E 4
		}
	}
I 4
	sync_close(1);
	return value;
E 4
}
E 1
