/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	bootxx.c,v $
 * Revision 2.2  89/07/12  00:10:17  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)bootxx.c 1.2 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include "saio.h"
#include <a.out.h>
#include <sys/vm.h>
#include <sys/reboot.h>
#include <mon/sunromvec.h>

int (*readfile()) ();

/*
 * Reads in the "real" boot program and jumps
 * to it.  If this attempt fails, prints "boot failed" and returns to its
 * caller.
 */
main()
{
	register struct bootparam *bp;
	register char *s, c;
	register int io;
	int (*addr)();

	extern struct boottab *(devsw[]);

	if (romp->v_bootparam == 0)
		bp = (struct bootparam *)0x2000;	/* Old Sun-1 address */
	else
		bp = *(romp->v_bootparam);		/* S-2: via romvec */

	/* If we were linked with a driver, use it in preference to PROM */
	if (*devsw)
		bp->bp_boottab = *devsw;

	s = bp->bp_argv[0];
	while (*s && *s != ')') s++;

	c = *s; *s = '\0';
	printf("Load: %s)boot\n", bp->bp_argv[0]);
	*s = c;

	io = physopen(bp, "boot", 0);

	if (io >= 0) {
		addr = readfile(io, 0);		/* Read silently */
		if ((int)addr != -1)
			_exitto(addr);
	}
	printf("boot failed\n");
	return;
}
