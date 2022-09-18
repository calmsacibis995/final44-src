h27506
s 00001/00001/00163
d D 8.2 93/12/06 20:25:00 akito 9 8
c sync up to hp300/hp300/swapgeneric.c    7.9 (Berkeley) 6/16/93
e
s 00002/00002/00162
d D 8.1 93/06/16 19:31:23 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00163
d D 7.6 93/06/16 19:31:02 mckusick 7 5
c have to terminate swapdev list with NODEV
e
s 00002/00002/00162
d R 8.1 93/06/10 22:26:49 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00160
d D 7.5 93/01/13 15:46:44 akito 5 4
c rootdev & swapdev message is removed
e
s 00016/00004/00147
d D 7.4 93/01/12 10:55:51 akito 4 3
c changed setconf() which could be allowed partition specification
e
s 00001/00001/00150
d D 7.3 93/01/03 12:49:37 akito 3 2
c remarked from field
e
s 00006/00006/00145
d D 7.2 92/10/11 11:07:55 bostic 2 1
c make kernel includes standard
e
s 00151/00000/00000
d D 7.1 92/06/15 06:38:48 fujita 1 0
c date and time created 92/06/15 06:38:48 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 8
 * Copyright (c) 1982, 1986, 1992 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1982, 1986, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 *
D 3
 * from: hp300/hp300/swapgeneric.c	7.1 (Berkeley) 6/4/92
E 3
I 3
D 9
 * from: hp300/hp300/swapgeneric.c	7.8 (Berkeley) 10/11/92
E 9
I 9
 * from: hp300/hp300/swapgeneric.c	7.9 (Berkeley) 6/16/93
E 9
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "sys/param.h"
#include "sys/conf.h"
#include "sys/buf.h"
#include "sys/systm.h"
#include "sys/reboot.h"
E 2
I 2
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/reboot.h>
E 2

D 2
#include "../dev/device.h"
E 2
I 2
#include <luna68k/dev/device.h>
E 2

/*
 * Generic configuration;  all in one
 */

dev_t	rootdev = NODEV;
dev_t	argdev  = NODEV;
dev_t	dumpdev = NODEV;

int	nswap;

struct	swdevt swdevt[] = {
	{ -1,	1,	0 },
D 7
	{ 0,	0,	0 },
E 7
I 7
	{ NODEV,0,	0 },
E 7
};

int	dmmin, dmmax, dmtext;

extern	struct driver sddriver;
extern struct hp_ctlr hp_cinit[];
extern struct hp_device hp_dinit[];

struct	genericconf {
	caddr_t	gc_driver;
	char	*gc_name;
	dev_t	gc_root;
} genericconf[] = {
	{ (caddr_t)&sddriver,	"sd",	makedev(4, 0) },
	{ 0 },
};

setconf()
{
	register struct hp_ctlr *hc;
	register struct hp_device *hd;
	register struct genericconf *gc;
	register char *cp;
D 4
	int unit, swaponroot = 0;
E 4
I 4
	int unit, part, swaponroot = 0;
E 4

	if (rootdev != NODEV)
		goto doswap;
	unit = 0;
I 4
	part = 0;
E 4
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
		cp = &name[2];
		if (*cp < '0' || *cp > '9') {
			printf("bad/missing unit number\n");
			goto retry;
		}
		while (*cp >= '0' && *cp <= '9')
			unit = 10 * unit + *cp++ - '0';
I 4
		if (*cp < 'a' || *cp > 'h') {
			printf("bad/missing partiiton number\n");
			goto retry;
		}
		part = *cp++ - 'a';
/*
E 4
		if (*cp == '*')
			swaponroot++;
I 4
 */
E 4
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
D 4
	gc->gc_root = makedev(major(gc->gc_root), unit*8);
E 4
I 4
	gc->gc_root = makedev(major(gc->gc_root), (unit * 8) + part );
E 4
	rootdev = gc->gc_root;
I 5
/*
E 5
D 4
	printf("using root device: %s%d%c\n", gc->gc_name, unit, 'a');
E 4
I 4
	printf("using root device: %s%d%c\n", gc->gc_name, unit, 'a' + part);
E 4
D 5

E 5
I 5
 */
E 5
doswap:
	swdevt[0].sw_dev = argdev = dumpdev =
D 4
	    makedev(major(rootdev), minor(rootdev)+1);
E 4
I 4
	    makedev(major(rootdev), (minor(rootdev) & ~0x7) + 1);
D 5

E 5
I 5
/*
E 5
	printf("using swap device: %s%d%c\n",
	       gc->gc_name, unit, 'a' + (minor(swdevt[0].sw_dev) & 0x7));
D 5

E 5
I 5
 */
E 5
E 4
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
		cnputc(c = cngetc());
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
