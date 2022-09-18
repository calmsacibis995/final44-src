h46225
s 00002/00002/00034
d D 8.1 93/06/06 16:28:45 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00035
d D 5.4 93/05/21 15:34:13 mckusick 8 7
c update header to reflect redistributable status
e
s 00006/00005/00030
d D 5.3 92/07/23 17:57:12 bostic 7 6
c update copyright/header notice
e
s 00001/00019/00034
d D 5.2 92/07/23 17:45:52 bostic 6 5
c Elan's new kvm lib version; prototype in extern.h
e
s 00007/00001/00046
d D 5.1 85/05/30 16:20:03 mckusick 5 4
c Add copyright
e
s 00007/00001/00040
d D 1.4 85/04/29 00:41:30 sam 4 3
c add netstat display
e
s 00014/00009/00027
d D 1.3 85/04/28 00:37:10 sam 3 2
c add vsta in; add help command (minimal); make loadav display something 
c which can be turned off
e
s 00014/00005/00022
d D 1.2 84/08/09 19:13:28 mckusick 2 1
c update to new sources from sam; weed out unnecessary #includes
e
s 00027/00000/00000
d D 1.1 83/10/02 21:41:03 sam 1 0
c date and time created 83/10/02 21:41:03 by sam
e
u
U
t
T
I 5
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 9
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * %sccs.include.proprietary.c%
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
 */

E 5
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% (Lucasfilm) %G%";
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
D 5
#endif
E 5
I 5
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 5

#include "systat.h"
D 6

D 2
int     showpigs(), fetchpigs(), labelpigs(), initpigs(), closepigs();
E 2
I 2
int     showpigs(), fetchpigs(), labelpigs();
int	initpigs(), closepigs();
E 2
WINDOW	*openpigs();
D 2
int     showswap(), fetchswap(), labelswap(), initswap(), closeswap();
E 2
I 2
int     showswap(), fetchswap(), labelswap();
int	initswap(), closeswap();
E 2
WINDOW	*openswap();
D 2
int	showmbufs(), fetchmbufs(), labelmbufs(), initmbufs(), closembufs();
E 2
I 2
int	showmbufs(), fetchmbufs(), labelmbufs();
int	initmbufs(), closembufs();
E 2
WINDOW	*openmbufs();
D 2
int	showiostat(), fetchiostat(), labeliostat(), initiostat(), closeiostat();
E 2
I 2
int	showiostat(), fetchiostat(), labeliostat();
int	initiostat(), closeiostat(), cmdiostat();
E 2
WINDOW	*openiostat();
I 2
D 3
int	showvmstat(), fetchvmstat(), labelvmstat();
int	initvmstat(), closevmstat();
WINDOW	*openvmstat();
E 3
I 3
int	showkre(), fetchkre(), labelkre();
int	initkre(), closekre(), cmdkre();
WINDOW	*openkre();
I 4
int	shownetstat(), fetchnetstat(), labelnetstat();
int	initnetstat(), closenetstat(), cmdnetstat();
WINDOW	*opennetstat();
E 6
I 6
#include "extern.h"
E 6
E 4
E 3
E 2

struct	cmdtab cmdtab[] = {
        { "pigs",	showpigs,	fetchpigs,	labelpigs,
D 3
	  initpigs,	openpigs,	closepigs },
E 3
I 3
	  initpigs,	openpigs,	closepigs,	0,
	  CF_LOADAV },
E 3
        { "swap",	showswap,	fetchswap,	labelswap,
D 3
	  initswap,	openswap,	closeswap },
E 3
I 3
	  initswap,	openswap,	closeswap,	0,
	  CF_LOADAV },
E 3
        { "mbufs",	showmbufs,	fetchmbufs,	labelmbufs,
D 3
	  initmbufs,	openmbufs,	closembufs },
E 3
I 3
	  initmbufs,	openmbufs,	closembufs,	0,
	  CF_LOADAV },
E 3
        { "iostat",	showiostat,	fetchiostat,	labeliostat,
D 2
	  initiostat,	openiostat,	closeiostat },
E 2
I 2
D 3
	  initiostat,	openiostat,	closeiostat,	cmdiostat },
        { "vmstat",	showvmstat,	fetchvmstat,	labelvmstat,
	  initvmstat,	openvmstat,	closevmstat },
E 3
I 3
	  initiostat,	openiostat,	closeiostat,	cmdiostat,
	  CF_LOADAV },
        { "vmstat",	showkre,	fetchkre,	labelkre,
	  initkre,	openkre,	closekre,	cmdkre,
	  0 },
I 4
        { "netstat",	shownetstat,	fetchnetstat,	labelnetstat,
	  initnetstat,	opennetstat,	closenetstat,	cmdnetstat,
	  CF_LOADAV },
E 4
E 3
E 2
        { 0 }
};
struct  cmdtab *curcmd = &cmdtab[0];
E 1
