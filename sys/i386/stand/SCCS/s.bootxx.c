h47964
s 00002/00002/00111
d D 8.1 93/06/11 15:57:44 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00108
d D 7.3 92/10/11 10:22:54 bostic 3 2
c make kernel includes standard
e
s 00051/00044/00061
d D 7.2 91/04/28 16:53:17 william 2 1
c merged to use features of common sys.c
e
s 00105/00000/00000
d D 7.1 90/04/24 19:56:22 william 1 0
c date and time created 90/04/24 19:56:22 by william
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 2
 * %sccs.include.noredist.c%
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "../h/param.h"
#include "../h/inode.h"
#include "../h/fs.h"
E 2
I 2
D 3
#include "param.h"
E 3
I 3
#include <sys/param.h>
#include <sys/reboot.h>
#include <sys/disklabel.h>

E 3
E 2
#include <a.out.h>
D 3
#include "saio.h"
D 2
#include "../h/reboot.h"
#include "../h/dir.h"
#include "../h/disk.h"
#include "devvm.h"
E 2
I 2
#include "reboot.h"
#include "disklabel.h"
E 3
I 3
#include <stand/saio.h>
E 3
E 2

D 2
extern	int howto, bootdev, unit, cyloffset, boottype;
extern char bootprog[] ;
E 2
I 2
char *bootprog = "/boot";
extern int opendev, bootdev, cyloffset;
extern struct disklabel disklabel;

E 2
/*
D 2
 * Boot program... arguments passed in r10 and r11
 * are passed through to the full boot program.
E 2
I 2
 * Boot program... loads /boot out of filesystem indicated by arguements.
 * We assume an autoboot unless we detect a misconfiguration.
E 2
 */

D 2
main()
E 2
I 2
main(dev, unit, off)
E 2
{
D 2
	register int io, partition; register char *bp ;
E 2
I 2
	register struct disklabel *lp;
	register int io, partition, howto;
E 2

D 2
#ifdef lint
	howto = 0; devtype = 0;
#endif
	extern struct disklabel disklabel;
E 2

	/* are we a disk, if so look at disklabel and do things */
D 2
	if (bootdev == 0 || bootdev == 3) {
E 2
I 2
	lp = &disklabel;
	if (lp->d_magic == DISKMAGIC) {
E 2
	    /*
D 2
	     * Synthesize bootdev from unit, type and partition
	     * from the ROM monitor.
	     * It's dirty work, but someone's got to do it, and
	     * we always seem to get it.
E 2
I 2
	     * Synthesize bootdev from dev, unit, type and partition
	     * information from the block 0 bootstrap.
	     * It's dirty work, but someone's got to do it.
	     * This will be used by the filesystem primatives, and
	     * drivers. Ultimately, opendev will be created corresponding
	     * to which drive to pass to top level bootstrap.
E 2
	     */
	    for (io = 0; io < 8; io++)
D 2
		if (bootdev > 0) { /* XXX should check dk_type == DTYPE_SCSI */
			if (disklabel.dk_partition[io].cyloff
				== cyloffset * disklabel.dk_secpercyl)
E 2
I 2
#ifdef notyetSCSI
		if (lp->d_type == DTYPE_SCSI) {
			if (lp->d_partitions[io].p_offset == off)
E 2
				break;
D 2
		} else {
	
			if (disklabel.dk_partition[io].cyloff == cyloffset)
E 2
I 2
		} else
#endif
		if (lp->d_partitions[io].p_offset == off*lp->d_secpercyl)
E 2
			break;
D 2
		}
	    if (io == 8) io = 0; /* probably a bad or non-existant disklabel */
	    bootdev = makedev(bootdev, make_minor(unit, io));
	} else { io = 0 ; howto = (howto&0x7) | 3 ; }
	bp = bootprog ;
	while (*bp != '0') bp++ ;	/* n-char device names instead of 2 */
	*bp++ = unit % 10 + '0' ;
	*bp += io % 10 ;
/*	bootprog[3] = unit % 10 + '0';
	bootprog[4] = io % 10 + 'a';*/
E 2
I 2

	    if (io == 8) goto screwed;
            cyloffset = off;
	} else {
screwed:
		/* probably a bad or non-existant disklabel */
		io = 0 ;
		howto |= RB_SINGLE|RB_ASKNAME ;
	}

	/* construct bootdev */
	/* currently, PC has no way of booting off alternate controllers */
	bootdev = MAKEBOOTDEV(/*i_dev*/ dev, /*i_adapt*/0, /*i_ctlr*/0,
	    unit, /*i_part*/io);

E 2
	printf("loading %s\n", bootprog);
	io = open(bootprog, 0);
	if (io >= 0)
D 2
		copyunix(io);
E 2
I 2
		copyunix(io, howto);
E 2
	_stop("boot failed\n");
}

/*ARGSUSED*/
D 2
copyunix(io)
E 2
I 2
copyunix(io, howto)
E 2
	register io;	
{
	struct exec x;
	register int i;
	char *addr;

	i = read(io, (char *)&x, sizeof x);
	if (i != sizeof x ||
	    (x.a_magic != 0407 && x.a_magic != 0413 && x.a_magic != 0410))
		_stop("Bad format\n");
I 2

E 2
	if ((x.a_magic == 0413 || x.a_magic == 0410) &&
	    lseek(io, 0x400, 0) == -1)
		goto shread;
I 2

E 2
	if (read(io, (char *)0, x.a_text) != x.a_text)
		goto shread;
I 2

E 2
	addr = (char *)x.a_text;
	if (x.a_magic == 0413 || x.a_magic == 0410)
		while ((int)addr & CLOFSET)
			*addr++ = 0;
I 2

E 2
	if (read(io, addr, x.a_data) != x.a_data)
		goto shread;
I 2

E 2
	addr += x.a_data;
D 2
	x.a_bss += 128*512;	/* slop */
E 2
	for (i = 0; i < x.a_bss; i++)
		*addr++ = 0;
D 2
	setregs();
 	(*((int (*)()) x.a_entry))();
E 2
I 2

 	(*((int (*)()) x.a_entry))(howto, opendev, cyloffset);
E 2
	return;
shread:
	_stop("Short read\n");
}
E 1
