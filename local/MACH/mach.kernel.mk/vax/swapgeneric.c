/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	swapgeneric.c,v $
 * Revision 2.5  89/03/09  22:21:32  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  20:28:44  gm0w
 * 	Changes for cleanup.
 * 
 * 29-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Allow root to be an arbitrary slice on the drive.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed useless definition of "part" in setconf.
 *
 *  4-Aug-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	MACH: Removed definitions/references of/to swdev and argdev.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 20-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.
 *	CMUCS:  Added conditionals around device driver references
 *	for use in partial generic configurations; compose root device
 *	prompt string based on the devices which are configured.
 *	[V1(1)]
 *
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)swapgeneric.c	7.1 (Berkeley) 6/6/86
 */

#include <hp.h>
#include <up.h>
#include <rk.h>
#include <rb.h>
#include <rl.h>
#include <ra.h>
#include <mba.h>

#include <vax/pte.h>

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/vm.h>
#include <sys/systm.h>
#include <sys/reboot.h>

#include <vax/cons.h>
#include <vax/mtpr.h>
#include <vaxmba/mbareg.h>
#include <vaxmba/mbavar.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

/*
 * Generic configuration;  all in one
 */
dev_t	rootdev = NODEV;
dev_t	dumpdev = NODEV;
/*
struct	swdevt swdevt[] = {
	{ -1,	1,	0 },
 	{ 0,	0,	0 },
 	{ 0,	0,	0 },
 	{ 0,	0,	0 },
	{ 0,	0,	0 },
};
*/
long	dumplo;

#if	NHP > 0
extern struct mba_driver hpdriver;
#endif	NHP
#if	NSC > 0
extern struct uba_driver scdriver;
#endif	NSC
#if	NHK > 0
extern struct uba_driver hkdriver;
#endif	NHK
#if	NIDC > 0
extern struct uba_driver idcdriver;
#endif	NIDC
#if	NHL > 0
extern struct uba_driver hldriver;
#endif	NHL
#if	NUDA > 0
extern struct uba_driver udadriver;
#endif	NUDA

struct	genericconf {
	caddr_t	gc_driver;
	char	*gc_name;
	dev_t	gc_root;
} genericconf[] = {
#if	NHP > 0
	{ (caddr_t)&hpdriver,	"hp",	makedev( 0, 0), },
#endif	NHP
#if	NSC > 0
	{ (caddr_t)&scdriver,	"up",	makedev( 2, 0), },
#endif	NSC
#if	NUDA > 0
	{ (caddr_t)&udadriver,	"ra",	makedev( 9, 0), },
#endif	NUDA
#if	NIDC > 0
	{ (caddr_t)&idcdriver,	"rb",	makedev(11, 0), },
#endif	NIDC
#if	NHL > 0
	{ (caddr_t)&hldriver,	"rl",	makedev(14, 0), },
#endif	NHL
#if	NHK > 0
	{ (caddr_t)&hkdriver,	"hk",	makedev( 3, 0), },
	{ (caddr_t)&hkdriver,	"rk",	makedev(3, 0),	},
#endif	NHK
	{ 0 },
};

setconf()
{
	register struct mba_device *mi;
	register struct uba_device *ui;
	register struct genericconf *gc;
	int unit, swaponroot = 0;
	int slice = 0;
	char name[128];

	if (rootdev != NODEV)
		goto doswap;
	if (boothowto & RB_ASKNAME) {
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
		if (name[2] >= '0' && name[2] <= '7') {
			if (name[3] >= 'a' && name[3] <= 'h') {
				slice = name[3] - 'a';
			} else if (name[3]) {
				printf("bad partition number\n");
				goto bad;
			}
			unit = name[2] - '0';
			goto found;
		}
		printf("bad/missing unit number\n");
bad:
		for (gc = genericconf; gc->gc_driver; gc++)
			printf("%s%s%%d",
			       (gc == genericconf)?"use ":
				    (((gc+1)->gc_driver)?", ":" or "),
			       gc->gc_name);
		printf("\n");
		goto retry;
	}
	unit = 0;
	for (gc = genericconf; gc->gc_driver; gc++) {
#if	NMBA <= 0
#else	NMBA <= 0
		for (mi = mbdinit; mi->mi_driver; mi++) {
			if (mi->mi_alive == 0)
				continue;
			if (mi->mi_unit == 0 && mi->mi_driver ==
			    (struct mba_driver *)gc->gc_driver) {
				printf("root on %s0\n",
				    mi->mi_driver->md_dname);
				goto found;
			}
		}
#endif	NMBA <= 0
		for (ui = ubdinit; ui->ui_driver; ui++) {
			if (ui->ui_alive == 0)
				continue;
			if (ui->ui_unit == 0 && ui->ui_driver ==
			    (struct uba_driver *)gc->gc_driver) {
				printf("root on %s0\n",
				    ui->ui_driver->ud_dname);
				goto found;
			}
		}
	}
	printf("no suitable root\n");
	asm("halt");
found:
	gc->gc_root = makedev(major(gc->gc_root), unit*8+slice);
	rootdev = gc->gc_root;
doswap:
	dumpdev =
	    makedev(major(rootdev), minor(rootdev)+1);
	/* swap size and dumplo set during autoconfigure */
	if (swaponroot)
		rootdev = dumpdev;
}
#define getchar	cngetc

gets(cp)
	char *cp;
{
	register char *lp;
	register c;

	lp = cp;
	for (;;) {
		c = getchar() & 0177;
		switch (c) {
		case '\n':
		case '\r':
			*lp++ = '\0';
			return;
		case '\b':
		case '#':
		case '\177':
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
