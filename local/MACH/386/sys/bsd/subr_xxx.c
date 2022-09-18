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
 * $Log:	subr_xxx.c,v $
 * Revision 2.9.1.1  90/02/28  15:46:08  rvb
 * 	I386: ffs, bcmp and strlen are now in locore.s
 * 	[90/02/27            rvb]
 * 
 * Revision 2.9  89/05/30  10:35:36  rvb
 * 	Moved index here, from a bogus place in afs/afs_whatchamacallit.
 * 	[89/05/15            af]
 * 
 * Revision 2.8  89/04/22  15:21:20  gm0w
 * 	Created unconditional errsys subroutine to return EINVAL.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.7  89/02/25  14:46:01  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:33:05  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/23  22:07:06  af
 * 	Added Mips specific code selections, and errsys() to trap
 * 	illegal syscalls to in init_sysent.c
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386: define imin, imax, ffs, strlen, bcmp
 * 	 but I have some of these in rep.s, so as soon as I can
 * 	 test them in a real system I can remove the crud here.
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  89/01/18  00:41:25  jsb
 * 	Vnode support: define nullsys and errsys functions for AFS and NFS
 * 	syscall support.
 * 	[89/01/16            jsb]
 * 
 *
 *  3-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Don't include "sys/vm.h".
 *
 * 30-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 07-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Change to panic on strlen(NULL) until this is determined to be
 *	a feature instead of a bug.
 *	[ V5.1(XF18) ]
 *
 * 20-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS: Changed inodes to vnodes.  Added nullsys() and errsys().
 *
 * 05-May-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Fixed strlen() so it won't memory fault if it is passed
 *	a null pointer.
 *
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Include cputypes.h.
 *	Don't compile calloc() if BALANCE -- this is used differently.
 *	Don't compile ffs(), bcmp(), and strlen() for BALANCE.
 *
 * 23-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added Sun to list of machines that need definition of imin(),
 *	min(), etc..
 *
 *  7-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	MACH: (negatively) Conditionalized include of pte.h
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	New calloc routine using VM routines.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 16-Nov-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	CMUCS:  Fixed off by one error in ffs.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)subr_xxx.c	7.1 (Berkeley) 6/5/86
 */

#include <cputypes.h>

#include <vm/vm_map.h>
#include <vm/vm_kern.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/inode.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/fs.h>
#include <sys/uio.h>

/*
 * Routine placed in illegal entries in the bdevsw and cdevsw tables.
 */
nodev()
{

	return (ENODEV);
}

/*
 * Null routine; placed in insignificant entries
 * in the bdevsw and cdevsw tables.
 */
nulldev()
{

	return (0);
}

/*
 * Null system calls, invalid syscall, or just not configured.
 */
errsys()
{
	u.u_error = EINVAL;
}

nullsys()
{
}

#if	defined(ibmrt) || defined(ns32000) || defined(sun) || defined(i386) || defined(mips)
imin(a, b)
{

	return (a < b ? a : b);
}

imax(a, b)
{

	return (a > b ? a : b);
}

unsigned
min(a, b)
	u_int a, b;
{

	return (a < b ? a : b);
}

unsigned
max(a, b)
	u_int a, b;
{

	return (a > b ? a : b);
}
#endif	defined(ibmrt) || defined(ns32000) || defined(sun) || defined(i386) || defined(mips)

#ifdef	balance
/*
 * Sequent Balance kernel uses calloc() differently.  See sqt/startup.c.
 */
#else	balance
caddr_t calloc(size)
	int size;
{
	return((caddr_t)kmem_alloc(kernel_map, (vm_offset_t)size));
}
#endif	balance

#ifdef	GPROF
/*
 * Stub routine in case it is ever possible to free space.
 */
cfreemem(cp, size)
	caddr_t cp;
	int size;
{
	printf("freeing %x, size %d\n", cp, size);
}
#endif	GPROF


#if	!defined(vax) && !defined(balance) && !defined(mips) && !defined(i386)

ffs(mask)
	register long mask;
{
	register int i;

	for(i = 1; i <= NSIG; i++) {
		if (mask & 1)
			return (i);
		mask >>= 1;
	}
	return (0);
}

bcmp(s1, s2, len)
	register char *s1, *s2;
	register int len;
{

	while (len--)
		if (*s1++ != *s2++)
			return (1);
	return (0);
}

strlen(s1)
	register char *s1;
{
	register int len;

	if (s1 == 0)
		panic("strlen(NULL)");
	for (len = 0; *s1++ != '\0'; len++)
		/* void */;
	return (len);
}
#endif	!defined(vax) && !defined(balance) && !defined(mips) && !defined(i386)


char *
index(strp, c)
register char *strp;
register char c;
{
	for (; *strp; strp++)
		if (*strp == c)
			return(strp);
	return(NULL);
}

