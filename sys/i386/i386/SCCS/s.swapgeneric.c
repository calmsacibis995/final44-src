h16080
s 00002/00002/00138
d D 8.1 93/06/16 19:30:15 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00139
d D 5.7 93/06/16 19:29:59 mckusick 9 7
c have to terminate swapdev list with NODEV
e
s 00002/00002/00138
d R 8.1 93/06/11 15:35:06 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00133
d D 5.6 92/10/11 10:11:05 bostic 7 6
c make kernel includes standard
e
s 00001/00004/00139
d D 5.5 91/05/09 22:19:51 bostic 6 5
c delete argdev; new copyright; att/bsd/shared
e
s 00007/00007/00136
d D 5.4 91/01/19 12:46:36 william 5 4
c kernel reorg
e
s 00006/00005/00137
d D 5.3 90/06/23 19:33:48 donahn 4 3
c improvements
e
s 00012/00001/00130
d D 5.2 90/04/24 19:13:14 william 3 2
c 1st Berkeley Release
e
s 00009/00013/00122
d D 5.1 90/04/24 18:56:46 william 2 1
c 1st Berkeley Release
e
s 00135/00000/00000
d D 1.1 90/03/12 15:48:23 bill 1 0
c date and time created 90/03/12 15:48:23 by bill
e
u
U
t
T
I 1
D 3
/*	swapgeneric.c	1.5	86/11/25	*/
E 3
I 3
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 6
 * %sccs.include.386.c%
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */

I 4
D 6
/*	swapgeneric.c	1.5	86/11/25	*/
E 4
E 3

E 6
D 5
#include "../machine/pte.h"
E 5
I 5
D 7
#include "machine/pte.h"
E 7
I 7
#include <machine/pte.h>
E 7
E 5

D 5
#include "param.h"
#include "conf.h"
#include "buf.h"
#include "vm.h"
#include "systm.h"
#include "reboot.h"
E 5
I 5
D 7
#include "sys/param.h"
#include "sys/conf.h"
#include "sys/buf.h"
#include "sys/vm.h"
#include "sys/systm.h"
#include "sys/reboot.h"
E 7
I 7
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/vm.h>
#include <sys/systm.h>
#include <sys/reboot.h>
E 7
E 5

D 2
#include "../tahoe/cpu.h"
#include "../tahoe/cp.h"
#include "../tahoe/mtpr.h"
#include "../tahoevba/vbavar.h"

E 2
/*
 * Generic configuration;  all in one
 */
D 2
dev_t	rootdev = NODEV;
dev_t	argdev = NODEV;
dev_t	dumpdev = NODEV;
E 2
I 2
D 4
dev_t	rootdev = 0;
dev_t	argdev = 1;
dev_t	dumpdev = 1;
E 4
I 4
dev_t	rootdev = makedev(0,0);
D 6
dev_t	argdev = makedev(0,1);
E 6
dev_t	dumpdev = makedev(0,1);
E 4
E 2
int	nswap;
struct	swdevt swdevt[] = {
D 2
	{ -1,	1,	0 },
	{ 0,	0,	0 },
E 2
I 2
D 4
	{ 1,	0,	4*4096 },
E 4
I 4
	{ 1,	0,	0 },
E 4
D 9
	{ 0,	1,	0 },
E 9
I 9
	{ NODEV,	1,	0 },
E 9
E 2
};
long	dumplo;
int	dmmin, dmmax, dmtext;

D 2
extern	struct vba_driver vddriver;
E 2
I 2
extern	struct driver wddriver;
E 2

struct	genericconf {
	caddr_t	gc_driver;
	char	*gc_name;
	dev_t	gc_root;
} genericconf[] = {
D 2
	{ (caddr_t)&vddriver,	"dk",	makedev(1, 0),	},
E 2
I 2
D 4
	{ (caddr_t)&wddriver,	"wd",	makedev(1, 0),	},
E 4
I 4
	{ (caddr_t)&wddriver,	"wd",	makedev(0, 0),	},
E 4
E 2
	{ 0 },
};

setconf()
{
D 2
	register struct vba_device *ui;
E 2
I 2
#ifdef notdef
E 2
	register struct genericconf *gc;
	int unit, swaponroot = 0;

	if (rootdev != NODEV)
		goto doswap;
	if (boothowto & RB_ASKNAME) {
		char name[128];
retry:
		printf("root device? ");
		gets(name);
		for (gc = genericconf; gc->gc_driver; gc++)
			if (gc->gc_name[0] == name[0] &&
			    gc->gc_name[1] == name[1])
				goto gotit;
		goto bad;
gotit:
		if (name[3] == '*') {
			name[3] = name[4];
			swaponroot++;
		}
		if (name[2] >= '0' && name[2] <= '7' && name[3] == 0) {
			unit = name[2] - '0';
			goto found;
		}
		printf("bad/missing unit number\n");
bad:
		printf("use dk%%d\n");
		goto retry;
	}
	unit = 0;
	for (gc = genericconf; gc->gc_driver; gc++) {
		for (ui = vbdinit; ui->ui_driver; ui++) {
			if (ui->ui_alive == 0)
				continue;
			if (ui->ui_unit == 0 && ui->ui_driver ==
			    (struct vba_driver *)gc->gc_driver) {
				printf("root on %s0\n",
				    ui->ui_driver->ud_dname);
				goto found;
			}
		}
	}
	printf("no suitable root\n");
	asm("halt");
found:
	gc->gc_root = makedev(major(gc->gc_root), unit*8);
	rootdev = gc->gc_root;
doswap:
	swdevt[0].sw_dev = argdev = dumpdev =
	    makedev(major(rootdev), minor(rootdev)+1);
	/* swap size and dumplo set during autoconfigure */
	if (swaponroot)
		rootdev = dumpdev;
I 2
#endif
E 2
}

gets(cp)
	char *cp;
{
	register char *lp;
	register c;

	lp = cp;
	for (;;) {
		printf("%c", c = cngetc()&0177);
		switch (c) {
		case '\n':
		case '\r':
			*lp++ = '\0';
			return;
		case '\b':
		case '\177':
			if (lp > cp) {
				printf(" \b");
				lp--;
			}
			continue;
		case '#':
			lp--;
			if (lp < cp)
				lp = cp;
			continue;
		case '@':
		case 'u'&037:
			lp = cp;
			printf("%c", '\n');
			continue;
		default:
			*lp++ = c;
		}
	}
}
E 1
