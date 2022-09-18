/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	swapgeneric.c,v $
 * Revision 1.3.1.10  91/07/15  00:16:04  rvb
 * 	Merge in some niceties from Vax3100 swapgeneric.c
 * 	[91/06/27            rvb]
 * 
 * 	more support for sd and flush qt/wt as a boot dev
 * 	[91/06/27            mg32]
 * 
 * Revision 1.3.1.9  91/05/03  10:58:04  rvb
 * 	Flush EXL
 * 	[91/05/03            rvb]
 * 
 * Revision 1.3.1.8  91/03/28  08:44:34  rvb
 * 	Add aha support.
 * 	[91/03/20            rvb]
 * 
 * Revision 1.3.1.7  90/07/10  11:42:50  rvb
 * 	iPSC2: rootdev and dumpdev are easy!
 * 		But on partition B which is BAD.
 * 	[90/06/16            rvb]
 * 
 * Revision 1.3.1.6  90/05/14  13:20:35  rvb
 * 	boottype & boothowto -> machdep.c
 * 	[90/04/23            rvb]
 * 
 * Revision 1.3.1.5  90/02/09  17:23:01  rvb
 * 	Use floppy type passed in when booting from floppy.
 * 	[90/02/09            rvb]
 * 
 * Revision 1.3.1.4  90/01/02  13:50:13  rvb
 * 	Move i386at definition to file prologue.
 * 
 * Revision 1.3.1.3  89/12/28  12:43:25  rvb
 * 	Kill printout "booting ... "
 * 	[89/12/26            rvb]
 * 
 * Revision 1.3.1.2  89/12/21  17:49:23  rvb
 * 	5 1/4' as default
 * 
 * 
 * Revision 1.3.1.1  89/10/22  11:31:39  rvb
 * 	New ... whizzy ... setconf code to find root.
 * 	[89/10/17            rvb]
 * 
 * Revision 1.3  89/02/26  12:34:03  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 * 29-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Allow root to be an arbitrary slice on the drive.
 *
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)swapgeneric.c	7.1 (Berkeley) 6/6/86
 */

#include <hd.h>
#include <fd.h>
#include <aha.h>

#include <cputypes.h>

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/systm.h>
#include <sys/reboot.h>
#include <i386at/disk.h>
/*
 *	 (4) (4) (4) (4)  (8)     (8)
 *	--------------------------------
 *	|MA | AD| CT| UN| PART  | TYPE |
 *	--------------------------------
 */
#define	B_ADAPTOR(val)		(((val) >> B_ADAPTORSHIFT) & B_ADAPTORMASK)
#define B_CONTROLLERSHIFT	20
#define B_CONTROLLERMASK	0xf
#define	B_CONTROLLER(val)	(((val)>>B_CONTROLLERSHIFT) & B_CONTROLLERMASK)
#define	B_UNIT(val)		(((val) >> B_UNITSHIFT) & B_UNITMASK)
#define	B_PARTITION(val)	(((val) >> B_PARTITIONSHIFT) & B_PARTITIONMASK)
#define	B_TYPE(val)		(((val) >> B_TYPESHIFT) & B_TYPEMASK)

int boottype = 0;
int boothowto = 0;

/*
 * Generic configuration;  all in one
 */
dev_t	rootdev = NODEV;
dev_t   dummy = 1;
#ifdef	someday
#if	NHD > 0
extern struct at_driver hddriver;
#endif	NHD
#if	NFD > 0
extern struct at_driver fddriver;
#endif	NFD
#if	NAHA > 0
extern struct at_driver ahadriver;
#endif	NAHA
#else	someday
#define driver dummy		/* non zero */
#define hddriver driver
#define fddriver driver
#define ahadriver driver
#endif	someday

#define aha_makedev hd_makedev

hd_makedev(maj, unit, slice)
{
	return (makedev(maj, unit*16+slice));		/* a */
}

fd_makedev(maj, unit, slice)
{
	if (!slice)
		slice = 3;
	return (makedev(maj, unit*64+slice));
}

struct	genericconf {			/* block or char */
	caddr_t	gc_driver;
	char	*gc_name;
	dev_t	gc_root;
	int	(*gc_makedev)();
} genericconf[] = {
#if	NHD > 0
	{ (caddr_t)&hddriver,	"hd",	0, hd_makedev},
#endif	NHD
#if	NFD > 0
	{ (caddr_t)&fddriver,	"fd",	1, fd_makedev},
#endif	NFD
#if	NAHA > 0
	{ (caddr_t)&ahadriver,	"sd",	3, aha_makedev},
#endif	NAHA > 0
	{ 0 },
};

setconf()
{
	register struct genericconf *gc;
	int unit, slice, maj, ctlr, adaptor;
	int mindev;
	int i = 2;
	char name[128];
	char strA[32], *str = strA;

#ifdef iPSC2
        rootdev = makedev(0, 1);
        return;
#endif iPSC2

	maj = B_TYPE(boottype);
	for (gc = genericconf; gc->gc_driver; gc++) {
		if (gc->gc_root == maj)
			break;
	}
	if (!gc->gc_driver) {
		printf("setroot: can not find major(%x) in table\n", maj);
		gc = &genericconf[0];
	}
	unit = B_UNIT(boottype);
	slice = B_PARTITION(boottype);
	adaptor = B_ADAPTOR(boottype);
	if (!(ctlr = B_CONTROLLER(boottype))) {
		ctlr = unit >> 3;
		unit = unit & 07;
	}
	/* mindev should be computed from ... the devinit[] */
	mindev = unit;
	mindev = (mindev << B_PARTITIONSHIFT) + slice;

	*str++ = gc->gc_name[0];
	*str++ = gc->gc_name[1];
	if ((i = mindev >> B_PARTITIONSHIFT) <= 9) 
		*str++ = '0' + i;
	else {
		*str++ = '0' + (i/10);
		*str++ = '0' + (i%10);
	}
	*str++ = slice + 'a';
	*str++ = 0;
	rootdev = (gc->gc_makedev)(maj, unit, slice);
	i = 2;

	if (boothowto & RB_ASKNAME) {
retry:
		printf("root device [%s]? ", strA);
		gets(name);
		if (*name == 0) {
			return;
		}

		for (gc = genericconf; gc->gc_driver; gc++)
			if (gc->gc_name[0] == name[0] &&
			    gc->gc_name[1] == name[1])
				break;
		if (!gc->gc_driver)
			goto bad;
		/*
		 * Syntax is: dvNP with
		 *	dv = 2 letters for the device
		 *	N  = decimal number (1|2 digits) for the unit
		 *	P  = 1 letter (a..h) for the partition
		 */

		if (name[i] >= '0' && name[i] <= '9') {
			/* two digits for unit ? */
			if (name[i+1] >= '0' && name[i+1] <= '9') {
				unit = (name[i] - '0') * 10;
				i++;
			}
			unit += name[i] - '0';
			if (name[++i] >= 'a' && name[i] <= 'h') {
				slice = name[i] - 'a';
			} else if (name[i]) {
				printf("bad partition number\n");
				goto bad;
			}

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

	for (gc = genericconf; gc->gc_driver; gc++)
		if (gc->gc_root == maj)
			goto found;
	printf("no suitable root\n");
	asm("hlt");
found:
	rootdev = (gc->gc_makedev)(gc->gc_root, unit, slice);

	bcopy(name, strA, i);
	strA[i++] = 'a' + slice;
	strA[i] = 0;

	printf("root on %s\n", strA);
}

gets(cp)
	char *cp;
{
	register char *lp;
	register c;

	lp = cp;
	for (;;) {
		c = cngetc() & 0177;
		switch (c) {
		case '\n':
		case '\r':
			*lp = '\0';
			return;
		case '\b':
			if (lp > cp) {
				lp--;
				putchar(' ');
				putchar('\b');
			}
			continue;
		case '#':
		case '\177':
			if (lp > cp)
				lp--;
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
