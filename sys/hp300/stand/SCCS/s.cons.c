h65510
s 00002/00002/00082
d D 8.1 93/06/10 21:46:34 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00081
d D 7.6 92/10/11 10:01:35 bostic 6 5
c make kernel includes standard
e
s 00009/00002/00075
d D 7.5 92/06/18 21:33:20 hibler 5 4
c merge with latest Utah version
e
s 00000/00001/00077
d D 7.4 91/05/05 13:55:54 bostic 4 3
c nodev not referenced
e
s 00002/00002/00076
d D 7.3 90/12/16 16:39:10 bostic 3 2
c kernel reorg
e
s 00006/00000/00072
d D 7.2 90/05/25 16:17:33 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00072/00000/00000
d D 7.1 90/05/08 22:46:00 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: cons.c 1.5 89/08/22$
E 5
I 5
 * from: Utah $Hdr: cons.c 1.7 92/02/28$
E 5
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "param.h"
E 3
I 3
D 6
#include "sys/param.h"
E 3
#include "samachdep.h"
D 3
#include "machine/cons.h"
E 3
I 3
D 5
#include "../hp300/cons.h"
E 5
I 5
#include "../hp/dev/cons.h"
E 6
I 6
#include <sys/param.h>
#include <hp300/stand/samachdep.h>
#include <hp/dev/cons.h>
E 6
E 5
E 3

D 4
int	nodev();
E 4
#ifdef ITECONSOLE
int	iteprobe(), iteinit(), itegetchar(), iteputchar();
#endif
#ifdef DCACONSOLE
int	dcaprobe(), dcainit(), dcagetchar(), dcaputchar();
#endif
I 2
#ifdef DCMCONSOLE
int	dcmprobe(), dcminit(), dcmgetchar(), dcmputchar();
#endif
E 2

struct consdev constab[] = {
#ifdef ITECONSOLE
	{ iteprobe,	iteinit,	itegetchar,	iteputchar },
#endif
#ifdef DCACONSOLE
	{ dcaprobe,	dcainit,	dcagetchar,	dcaputchar },
I 2
#endif
#ifdef DCMCONSOLE
	{ dcmprobe,	dcminit,	dcmgetchar,	dcmputchar },
E 2
#endif
	{ 0 },
};

struct consdev *cn_tab;
int noconsole;

cninit()
{
	register struct consdev *cp;

	cn_tab = NULL;
	noconsole = 1;
	for (cp = constab; cp->cn_probe; cp++) {
		(*cp->cn_probe)(cp);
		if (cp->cn_pri > CN_DEAD &&
		    (cn_tab == NULL || cp->cn_pri > cn_tab->cn_pri))
			cn_tab = cp;
	}
	if (cn_tab) {
		(*cn_tab->cn_init)(cn_tab);
		noconsole = 0;
	}
}

cngetc()
{
	if (cn_tab)
		return((*cn_tab->cn_getc)());
	return(0);
}

cnputc(c)
	int c;
{
I 5
#ifdef ROMPRF
	extern int userom;

	if (userom)
		romputchar(c);
	else
#endif
E 5
	if (cn_tab)
		(*cn_tab->cn_putc)(c);
}
E 1
