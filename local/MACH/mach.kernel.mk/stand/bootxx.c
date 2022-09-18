/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	bootxx.c,v $
 * Revision 2.4  89/03/09  21:13:47  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  14:18:29  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/08  13:42:13  rvb
 * Cannot put r* into registers or changes will not be reflected
 * out.
 * Pass all registers to main() and have main return entry address.
 * 
 *
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed interpretation of unit number field in boot device for
 *	multiple controllers on the adpator.
 *	[ V5.1(F8) ]
 *
 **********************************************************************
 */ 
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)bootxx.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/vm.h>
#include <a.out.h>
#include "saio.h"
#include <sys/reboot.h>

char bootprog[10] = "boot";
char bootresult[20];
/*
 * Boot program... All arguments
 * are passed through to the full boot program.
 */
extern char *openstr;

main(r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,devtype,howto,ap)
{
	int io, unit, partition;
	register char *cp;
	register int ret;

#ifdef	lint
	howto = 0; devtype = 0;
#endif

	if (howto & RB_ALTBOOT)
		bcopy(".old", &bootprog[4], 5);
	openstr = bootresult;
	io = open(bootprog, 0);
	printf("\nbootxx: %s\n", bootresult);
	if (io < 0 || (ret = copyunix(howto, devtype, io)) == -1)
		_stop("boot failed\n");
	else
		return ret;
}

/*ARGSUSED*/
copyunix(howto, devtype, io)
	register howto, devtype, io;	/* howto=r11, devtype=r10 */
{
	struct exec x;
	register int i;
	char *addr;

	i = read(io, (char *)&x, sizeof x);
	if (i != sizeof x ||
	    (x.a_magic != 0407 && x.a_magic != 0413 && x.a_magic != 0410))
		_stop("Bad format\n");
	if ((x.a_magic == 0413 || x.a_magic == 0410) &&
	    lseek(io, 0x400, 0) == -1)
		goto shread;
	if (read(io, (char *)0, x.a_text) != x.a_text)
		goto shread;
	addr = (char *)x.a_text;
	if (x.a_magic == 0413 || x.a_magic == 0410)
		while ((int)addr & CLOFSET)
			*addr++ = 0;
	if (read(io, addr, x.a_data) != x.a_data)
		goto shread;
	addr += x.a_data;
	x.a_bss += 128*512;	/* slop */
	bzero(addr, x.a_bss);
	x.a_entry &= 0x7fffffff;
	return x.a_entry;
shread:
	_stop("Short read\n");
}
