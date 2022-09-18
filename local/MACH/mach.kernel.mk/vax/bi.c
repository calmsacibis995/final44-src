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
 * $Log:	bi.c,v $
 * Revision 2.5  89/02/25  20:11:35  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/10/11  13:00:01  rpd
 * 	Move crd and crd_cnt to ka62a.c where it belongs.
 * 	[88/09/29            rvb]
 * 
 * Revision 2.3  88/08/10  10:12:31  rvb
 *  7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Print master processor status on a bi node err for the 820, since
 * 	we do it for everyone else.
 * 
 *  6-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Split out ka820 stuff to ka820.c.  Will soon bring bi autoconf
 * 	stuff into this file.
 * 
 *
 * 19-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	More fixes to compile (although not run) without Mach.
 *	[ V5.1(XF23) ]
 *
 *  8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Error printout on eintrcsr vector.
 *	Added code to print out all the fields of a bi node for
 *	debugging, pbi().
 *
 * 11-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added interprocessor interrupt send and receive routines.
 *	Receive is (temporarily) tied to pmap_update_interrupt.
 *
 */
/*
 *	File:	vax/bi.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr.
 *
 *	VAX BI Bus support.
 */
#include <cputypes.h>

#include <sys/types.h>
#include <vax/cpu.h>
#include <vax/bi_node.h>
#include <vaxnb/node.h>

ip_intr()
{
	pmap_update_interrupt();
}
