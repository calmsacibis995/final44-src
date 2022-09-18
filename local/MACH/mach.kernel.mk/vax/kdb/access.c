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
 * Revision 2.4  89/02/25  20:20:53  gm0w
 * 	Changes for cleanup.
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

#include <vax/kdb/defs.h>


map		txtmap;
map		datmap;
INT		wtflag;
string_t	errflg;
INT		errno;

INT		pid;

/*
 * Primitives: put a value in a space, get a value from a space
 * and get a word or byte not returning if an error occurred.
 */
put(addr, space, value)
long	addr, value;
{
	(void) access(WT, addr, space, value);
}

u_int
get(addr, space)
long	addr;
{
	return (access(RD, addr, space, 0));
};

u_int
chkget(addr, space)
long	addr;
{
	u_int w = get(addr, space);
	chkerr();
	return(w);
}

u_int
bchkget(addr, space)
long	addr;
{
	return(chkget(addr, space) & 0377);
}

/*
 * Read/write according to mode at address addr in i/d space.
 * Value is quantity to be written, if write.
 *
 * This routine decides whether to get the data from the subprocess
 * address space with ptrace, or to get it from the files being
 * debugged.
 *
 * When the kernel is being debugged with the -k flag we interpret
 * the system page tables for data space, mapping p0 and p1 addresses
 * relative to the ``current'' process (as specified by its p_addr in
 * <p) and mapping system space addresses through the system page tables.
 */
access(mode, addr, space, value)
int mode, space, value;
long	addr;
{
	int rd = mode == RD;
	int	w;

	if (space == NSP)
		return(0);
	w = 0;
	if (mode==WT && wtflag==0)
		error("not in write mode");
	if (kdbreadwrite(curmap, addr, rd ? &w : &value, rd) < 0)
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


within(addr,lbd,ubd)
u_int addr, lbd, ubd;
{
	return(addr>=lbd && addr<ubd);
}
