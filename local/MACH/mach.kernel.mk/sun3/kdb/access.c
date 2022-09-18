/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	access.c,v $
 * Revision 2.4  89/03/09  21:33:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:35:12  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL in order to make kdb
 *	part of the kernel rather than a separate library.
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)access.c 1.1 86/02/03 SMI"; /* from UCB X.X XX/XX/XX */
#endif
/*
 * adb: rwmap data in file/process address space.
 */

#include <sun3/kdb/adb.h>
int	errno;

put(addr, space, value) 
	addr_t addr;
	int space, value;
{
	(void) rwmap('w', addr, space, value);
}

get(addr, space)
	addr_t addr;
	int space;
{

	return (rwmap('r', addr, space, 0));
}

chkget(addr, space)
	addr_t addr;
	int space;
{
	int w = get(addr, space);

	chkerr();
	return (w);
}

bchkget(addr, space) 
	addr_t addr;
	int space;
{
	long val = chkget(addr, space);
	/* try to be machine independent -- big end and little end machines */
	return ( *(char *)&val);
}

rwmap(mode, addr, space, value)
	char mode;
	addr_t addr;
	int space, value;
{
	int file, w;

	if (space == NSP)
		return (0);
	w = 0;
	if (mode == 'w' && wtflag == 0)
		error("not in write mode");
	if (kdbreadwrite(curmap, addr, mode == 'r' ? &w : &value, 
	    mode == 'r') < 0)
		rwerr(space);
	return (w);
}


rwerr(space)
	int space;
{

	if (space & DSP)
		errflg = "data address not found";
	else
		errflg = "text address not found";
}

rwphys(file, addr, aw, rw)
	int file;
	addr_t addr;
	int *aw, rw;
{
	int rc;

	if (rw == 'r')
                kdbrlong(addr, aw);
	else
		kdbwlong(addr, aw);
	return (0);
}

chkmap(addr, space)
	register addr_t *addr;
	register int space;
{
	register struct map *amap;

	amap = (space&DSP)? &datmap : &txtmap;
	if ((space&STAR) == 0 && within(*addr, amap->b1, amap->e1)) {
		*addr += amap->f1 - amap->b1;
		return (1);
	}
	if (within(*addr, amap->b2, amap->e2)) {
		*addr += amap->f2 - amap->b2;
		return (1);
	}
	rwerr(space);
	return (0);
}

within(addr, lbd, ubd)
	addr_t addr, lbd, ubd;
{

	return (addr >= lbd && addr < ubd);
}


/* rest of this stuff is machine dependent */

#ifdef	vax
#include <access.vax>
#endif
#ifdef	sun3
#include <sun3/kdb/access.68>
#endif
