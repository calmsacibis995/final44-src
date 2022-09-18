/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 **********************************************************************
 * HISTORY
 * $Log:	bootavie.c,v $
 * Revision 2.3  89/03/09  21:13:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  14:18:22  gm0w
 * 	Changes for cleanup.
 * 
 **********************************************************************
 */
/*
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)bootra.c	6.2 (Berkeley) 6/8/85
 */

#include <sys/param.h>
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/vm.h>
#include <a.out.h>
#include "saio.h"
#include <sys/reboot.h>

char bootprog[] = "ra(0,0)boot";

/*
 * Boot program... arguments passed in r10 and r11
 * are passed through to the full boot program.
 */

main()
{
	register howto, devtype;	/* howto=r11, devtype=r10 */
	int io;

#ifdef	lint
	howto = 0; devtype = 0;
#endif
	printf("copying to ra(0,0)\n");
	io = open("ra(0,0)", 1);
	if (io >= 0)
		copyroot(io);
	printf("boot failed");
	_exit();
}

copyroot(io)
{
	register int i;
	int count;
	char *addr;

	i = 0;
	addr = (char *) 0x100000;
	while (i < 400*1024) {
		printf(".");
		count = write(io, addr, 512);
		if (count != 512) {
			printf("copy failed\n");
			_exit();
		}
		addr += 512;
		i += 512;
	}
	printf("copied!\n");
	_exit();
}
