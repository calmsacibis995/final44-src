h12984
s 00002/00002/00165
d D 8.1 93/06/16 19:29:02 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00166
d D 7.4 93/06/16 19:28:43 mckusick 5 3
c have to terminate swapdev list with NODEV
e
s 00002/00002/00165
d R 8.1 93/06/10 23:07:49 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00161
d D 7.3 92/10/11 11:23:22 bostic 3 2
c make kernel includes standard
e
s 00028/00012/00139
d D 7.2 92/09/13 11:46:05 ralph 2 1
c fix GENERIC kernels when using the memory mini-root. rootdev is already defined.
e
s 00151/00000/00000
d D 7.1 92/01/07 17:29:23 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "param.h"
#include "conf.h"
#include "buf.h"
#include "systm.h"
#include "reboot.h"
E 3
I 3
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/reboot.h>
E 3

D 3
#include "../dev/device.h"
E 3
I 3
#include <pmax/dev/device.h>
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
D 5
	{ 0,	0,	0 },
E 5
I 5
	{ NODEV,	0,	0 },
E 5
};
int	dmmin, dmmax, dmtext;

extern	struct driver rzdriver;

struct	genericconf {
	caddr_t	gc_driver;
	char	*gc_name;
	dev_t	gc_root;
} genericconf[] = {
	{ (caddr_t)&rzdriver,	"rz",	makedev(0, 0),	},
	{ 0 },
};

setconf()
{
	register struct scsi_device *dp;
	register struct genericconf *gc;
	register char *cp, *gp;
	int unit, swaponroot = 0;
I 2
	char *root_swap;
E 2

D 2
	if (rootdev != NODEV)
		goto doswap;
E 2
I 2
	/*
	 * If we are running on the in memory, mini-root; then we just need
	 * to set the swap device.
	 */
	if (boothowto & RB_MINIROOT)
		root_swap = "swap";
	else {
		if (rootdev != NODEV) {
			swdevt[0].sw_dev = argdev = dumpdev =
				makedev(major(rootdev), minor(rootdev)+1);
			return;
		}
		root_swap = "root";
	}
E 2
	unit = 0;
	if (boothowto & RB_ASKNAME) {
		char name[128];
retry:
D 2
		printf("root device? ");
E 2
I 2
		printf("%s device? ", root_swap);
E 2
		gets(name);
		for (gc = genericconf; gc->gc_driver; gc++)
		    for (cp = name, gp = gc->gc_name; *cp == *gp; cp++)
			if (*++gp == 0)
				goto gotit;
		printf("use one of:");
		for (gc = genericconf; gc->gc_driver; gc++)
			printf(" %s%%d", gc->gc_name);
		printf("\n");
		goto retry;
gotit:
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
		for (dp = scsi_dinit; dp->sd_driver; dp++) {
			if (dp->sd_alive == 0)
				continue;
			if (dp->sd_unit == unit &&
			    dp->sd_driver == (struct driver *)gc->gc_driver) {
				printf("root on %s%d%c\n",
					dp->sd_driver->d_name, unit,
					"ab"[swaponroot]);
				goto found;
			}
		}
	}
D 2
	printf("no suitable root\n");
E 2
I 2
	printf("no suitable %s\n", root_swap);
E 2
	goto retry;
found:
D 2
	gc->gc_root = makedev(major(gc->gc_root), unit*8);
	rootdev = gc->gc_root;
doswap:
	swdevt[0].sw_dev = argdev = dumpdev =
	    makedev(major(rootdev), minor(rootdev)+1);
	/* swap size and dumplo set during autoconfigure */
	if (swaponroot)
		rootdev = dumpdev;
E 2
I 2
	if (boothowto & RB_MINIROOT) {
		swdevt[0].sw_dev = argdev = dumpdev =
			makedev(major(gc->gc_root), unit*8+1);
	} else {
		rootdev = makedev(major(gc->gc_root), unit*8);
		swdevt[0].sw_dev = argdev = dumpdev =
			makedev(major(rootdev), minor(rootdev)+1);
		/* swap size and dumplo set during autoconfigure */
		if (swaponroot)
			rootdev = dumpdev;
	}
E 2
}

gets(cp)
	char *cp;
{
	register char *lp;
	register c;
	int s;

	lp = cp;
	s = spltty();
	for (;;) {
		cnputc(c = cngetc());
		switch (c) {
		case '\r':
			cnputc('\n');
			*lp++ = '\0';
			break;
		case '\n':
			cnputc('\r');
			*lp++ = '\0';
			break;
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
			continue;
		}
		break;
	}
	splx(s);
}
E 1
