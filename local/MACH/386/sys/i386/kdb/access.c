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
 * $Log:	access.c,v $
 * Revision 1.4.1.1  90/01/08  13:28:35  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * 	kdb reorg
 * 	[89/03/24            rvb]
 * 
 * Revision 1.2  89/03/24  11:34:50  rvb
 * comment
 * 
 * Revision 1.1  89/03/24  11:27:50  rvb
 * Initial revision
 * 
 * Revision 1.1  89/03/22  20:21:36  rvb
 * Initial revision
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed more lint.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 16-May-86 David Golub (dbg) at Carnegie-Mellon University
 *	Support for multiple-process debugging
 *
 */

/*
 * Adb: access data in file/process address space.
 *
 * The routines in this file access referenced data using
 * the maps to access files, ptrace to access subprocesses,
 * or the system page tables when debugging the kernel,
 * to translate virtual to physical addresses.
 */

/* static	char sccsid[] = "@(#)access.c	4.7 8/11/83"; */

#include <sys/types.h>
#include <vm/vm_map.h>

extern	char		*kdberrflg;
extern	vm_map_t	 kdbcurmap;
extern	int		 kdbchkerr();

/*
 * Primitives: put a value in a space, get a value from a space
 * and get a word or byte not returning if an error occurred.
 */

kdbput(addr, value)
long	addr, value;
{
	if (kdbreadwrite(kdbcurmap, addr, &value, 0) < 0)
		kdberrflg = "can not change data";
}

u_int
kdbget(addr)
long	addr;
{
	int	w = 0;

	if (kdbreadwrite(kdbcurmap, addr, &w, 1) < 0)
		kdberrflg = "can not find address";
	return (w);
};

u_int
kdbchkget(addr)
long	addr;
{
	u_int w = kdbget(addr);
	kdbchkerr();
	return(w);
}

u_int
kdbbchkget(addr)
long	addr;
{
	u_int w = kdbget(addr);
	kdbchkerr();
	return(w&0xff);
}
