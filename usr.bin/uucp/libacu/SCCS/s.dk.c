h48396
s 00002/00002/00047
d D 8.1 93/06/06 22:08:58 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00041
d D 4.4 91/04/24 17:30:33 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00041
d D 4.3 91/03/02 13:13:33 bostic 3 2
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00000/00042
d D 4.2 88/02/24 20:45:16 rick 2 1
c remove extraneous ifdefs
e
s 00042/00000/00000
d D 4.1 85/01/22 13:04:21 ralph 1 0
c date and time created 85/01/22 13:04:21 by ralph
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

D 3
#include "../condevs.h"
E 3
I 3
#include "condevs.h"
E 3
#ifdef DATAKIT
#include <dk.h>
#define DKTRIES 2
/***
 *	dkopn(flds)	make datakit connection
 *
 *	return codes:
 *		>0 - file number - ok
 *		FAIL - failed
 */
dkopn(flds)
char *flds[];
{
	int dkphone;
	register char *cp;
	register ret, i;

	if (setjmp(Sjbuf))
		return CF_DIAL;

	signal(SIGALRM, alarmtr);
	dkphone = 0;
	cp = flds[F_PHONE];
	while(*cp)
		dkphone = 10 * dkphone + (*cp++ - '0');
	DEBUG(4, "dkphone (%d) ", dkphone);
	for (i = 0; i < DKTRIES; i++) {
		getnextfd();
		ret = dkdial(D_SH, dkphone, 0);
		next_fd = -1;
		DEBUG(4, "dkdial (%d)\n", ret);
		if (ret > -1)
			break;
	}
	return ret;
}
#endif
E 1
