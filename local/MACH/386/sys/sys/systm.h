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
 * $Log:	systm.h,v $
 * Revision 2.10  89/04/22  15:32:30  gm0w
 * 	Changed extern boolean_t rpause() to rpsleep().
 * 	[89/04/20            gm0w]
 * 	Removed MACH_VFS changes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.9  89/03/09  22:08:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/25  17:56:45  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.7  89/01/30  22:08:31  rpd
 * 	Made declarations use "extern".
 * 	[89/01/25  15:23:46  rpd]
 * 
 * Revision 2.6  89/01/23  22:29:05  af
 * 	MIPS: externs to make compiler happy.
 * 	[89/01/10            af]
 * 
 * Revision 2.5  89/01/18  01:19:49  jsb
 * 	Vnode support: added bdevvp and specvp functions.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.4  88/08/24  02:45:36  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:23:41  mwyoung]
 * 
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Eliminated unused variables.
 *
 * 19-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make redefinitions of insque/remque always ifdef'ed on lint.
 *
 *  1-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Moved runrun and curpri definitions to sched.h for MACH.
 *
 * 19-Jan-86  David L. Black (dlb) at Carnegie-Mellon University
 *	MACH: runrun and curpri are now per cpu.  Removed
 *	runin, runout, wantin, and noproc.
 *
 * 17-Dec-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed declaration of icode under MACH.
 *
 * 12-Nov-86  David L. Black (dlb) at Carnegie-Mellon University
 *	ns32000: #ifdef lint'ed insque and remque casts.  These bogosities
 *	ought to be permanently #ifdef lint'ed for all systems.
 *
 *  7-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Merged Multimax changes.
 *
 * 24-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Changed to directly import declaration of boolean.
 *
 * 29-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Converted from "bool" type to "boolean_t" where necessary.
 *
 * 16-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	MACH: Removed definitions of swapdev and argdev.
 *
 * 22-Mar-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged VM and Romp versions.
 *
 * 18-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	romp: Added new definition of icode[].
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 *  4-Nov-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Add sy_parallel flag to the system call entries to specify
 *	whether or not the system call can be executed in parallel.
 *
 * 03-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RPAUSE:  Added rpause() and fspause() declarations.
 *
 * 20-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Added bootdev definition.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)systm.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_SYSTM_H_
#define _SYS_SYSTM_H_

/*
 * Structure of the system-entry table
 */
struct sysent
{
	short	sy_narg;		/* total number of arguments */
	short	sy_parallel;		/* can execute in parallel */
	int	(*sy_call)();		/* handler */
};

#ifdef	KERNEL
#include <mach/boolean.h>
#include <sys/types.h>

/*
 * Random set of variables
 * used by more than one
 * routine.
 */
extern char	version[];		/* system version */

/*
 * Nblkdev is the number of entries
 * (rows) in the block switch. It is
 * set in binit/bio.c by making
 * a pass over the switch.
 * Used in bounds checking on major
 * device numbers.
 */
extern int	nblkdev;

/*
 * Number of character switch entries.
 * Set by cinit/prim.c
 */
extern int	nchrdev;

extern int	mpid;			/* generic for unique process id's */
extern char	kmapwnt;		/* Make #if cleaner */

extern int	maxmem;			/* actual max memory per process */
extern int	physmem;		/* physical memory on this CPU */

extern int	updlock;		/* lock for sync */
extern daddr_t	rablock;		/* block to be read ahead */
extern int	rasize;			/* size of block in rablock */
extern int	intstack[];		/* stack for interrupts */
extern dev_t	rootdev;		/* device of the root */
extern dev_t	dumpdev;		/* device to take dumps on */
extern long	dumplo;			/* offset into dumpdev */

extern daddr_t	bmap();
extern caddr_t	calloc();

extern boolean_t	rpsleep();
extern boolean_t	fspause();

extern struct sysent sysent[];

extern char	*panicstr;
extern int	boothowto;		/* reboot flags, from console subsys */
extern int	show_space;
extern u_long	bootdev;		/* boot dev, from bootstrap subsys */
extern int	selwait;

#ifdef	lint
/* casts to keep lint happy */
#define insque(q,p)	_insque((caddr_t)q,(caddr_t)p)
#define remque(q)	_remque((caddr_t)q)
#endif	lint

#endif	KERNEL
#endif	_SYS_SYSTM_H_
