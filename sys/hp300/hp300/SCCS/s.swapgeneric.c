h03235
s 00002/00002/00141
d D 8.1 93/06/16 19:27:35 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00142
d D 7.9 93/06/16 19:26:56 mckusick 10 8
c need to add NODEV to end of list
e
s 00002/00002/00141
d R 8.1 93/06/10 21:41:34 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00137
d D 7.8 92/10/11 09:42:48 bostic 8 7
c make kernel includes standard
e
s 00002/00001/00141
d D 7.7 92/07/25 19:45:48 mckusick 7 6
c fixups for GNERIC kernel
e
s 00001/00001/00141
d D 7.6 92/06/05 15:37:02 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00000/00001/00142
d D 7.5 91/05/07 10:01:44 hibler 5 4
c get rid of dumplo definition (this may come back)
e
s 00000/00002/00143
d D 7.4 91/04/20 17:33:07 karels 4 3
c don't need pte.h
e
s 00007/00007/00138
d D 7.3 90/12/16 16:36:36 bostic 3 2
c kernel reorg
e
s 00000/00001/00145
d D 7.2 90/12/05 18:53:37 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00146/00000/00000
d D 7.1 90/05/08 18:09:13 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 11
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "pte.h"
E 3
I 3
D 4
#include "../include/pte.h"
E 3

E 4
D 3
#include "param.h"
#include "conf.h"
#include "buf.h"
D 2
#include "vm.h"
E 2
#include "systm.h"
#include "reboot.h"
E 3
I 3
D 8
#include "sys/param.h"
#include "sys/conf.h"
#include "sys/buf.h"
#include "sys/systm.h"
#include "sys/reboot.h"
E 8
I 8
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/reboot.h>
E 8
E 3

D 3
#include "../hpdev/device.h"
E 3
I 3
D 6
#include "../dev/device.h"
E 6
I 6
D 8
#include "hp/dev/device.h"
E 8
I 8
#include <hp/dev/device.h>
E 8
E 6
E 3

/*
 * Generic configuration;  all in one
 */
dev_t	rootdev = NODEV;
dev_t	argdev = NODEV;
dev_t	dumpdev = NODEV;
int	nswap;
struct	swdevt swdevt[] = {
	{ -1,	1,	0 },
D 10
	{ 0,	0,	0 },
E 10
I 10
	{ NODEV,	0,	0 },
E 10
};
D 5
long	dumplo;
E 5
int	dmmin, dmmax, dmtext;

extern	struct driver rddriver;
extern	struct driver sddriver;
extern struct hp_ctlr hp_cinit[];
extern struct hp_device hp_dinit[];

struct	genericconf {
	caddr_t	gc_driver;
	char	*gc_name;
	dev_t	gc_root;
} genericconf[] = {
	{ (caddr_t)&rddriver,	"rd",	makedev(2, 0),	},
	{ (caddr_t)&sddriver,	"sd",	makedev(4, 0),	},
	{ 0 },
};

setconf()
{
	register struct hp_ctlr *hc;
	register struct hp_device *hd;
	register struct genericconf *gc;
	register char *cp;
	int unit, swaponroot = 0;

	if (rootdev != NODEV)
		goto doswap;
	unit = 0;
	if (boothowto & RB_ASKNAME) {
		char name[128];
retry:
		printf("root device? ");
		gets(name);
		for (gc = genericconf; gc->gc_driver; gc++)
			if (gc->gc_name[0] == name[0] &&
			    gc->gc_name[1] == name[1])
				goto gotit;
		printf("use one of:");
		for (gc = genericconf; gc->gc_driver; gc++)
			printf(" %s%%d", gc->gc_name);
		printf("\n");
		goto retry;
gotit:
I 7
		cp = &name[1];
E 7
		if (*++cp < '0' || *cp > '9') {
			printf("bad/missing unit number\n");
			goto retry;
		}
		while (*cp >= '0' && *cp <= '9')
			unit = 10 * unit + *cp++ - '0';
		if (*cp == '*')
			swaponroot++;
		goto found;
	}
	for (gc = genericconf; gc->gc_driver; gc++) {
		for (hd = hp_dinit; hd->hp_driver; hd++) {
			if (hd->hp_alive == 0)
				continue;
			if (hd->hp_unit == 0 && hd->hp_driver ==
			    (struct driver *)gc->gc_driver) {
				printf("root on %s0\n", hd->hp_driver->d_name);
				goto found;
			}
		}
	}
	printf("no suitable root\n");
	asm("stop #0x2700");
found:
	gc->gc_root = makedev(major(gc->gc_root), unit*8);
	rootdev = gc->gc_root;
doswap:
	swdevt[0].sw_dev = argdev = dumpdev =
	    makedev(major(rootdev), minor(rootdev)+1);
	/* swap size and dumplo set during autoconfigure */
	if (swaponroot)
		rootdev = dumpdev;
}

gets(cp)
	char *cp;
{
	register char *lp;
	register c;

	lp = cp;
	for (;;) {
D 7
		cnputc(c = cngetc());
E 7
I 7
		cnputc(c = (cngetc() & 0177));
E 7
		switch (c) {
		case '\n':
		case '\r':
			*lp++ = '\0';
			return;
		case '\b':
		case '\177':
			if (lp > cp) {
				lp--;
				cnputc(' ');
				cnputc('\b');
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
			cnputc('\n');
			continue;
		default:
			*lp++ = c;
		}
	}
}
E 1
