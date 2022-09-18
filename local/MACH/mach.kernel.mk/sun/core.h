/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	core.h,v $
 * Revision 2.5  89/07/11  13:55:07  jjc
 * 	Conditionally defined CORE_PADLEN under sun3 and added fpu
 * 	field to core structure for sparc.
 * 	[88/07/05            jjc]
 * 
 * Revision 2.4  89/03/09  21:30:01  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:28:06  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-89  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Fixed #include's as part of cleanup.
 *
 */
/*	@(#)core.h 1.1 86/09/25 SMI	*/

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#ifndef	CORE_H_
#define CORE_H_

#include <sys/exec.h>
#include <machine/reg.h>

#define CORE_MAGIC	0x080456
#define CORE_NAMELEN	16		/* Related to MAXCOMLEN in user.h */

/*
 * The size of struct fpa_regs is changed from 141 ints in 3.0 to
 * 77 ints in 3.x.  A pad of this size difference is added to struct core.
 */
#if	sun3
#define CORE_PADLEN	64
#endif	sun3

/*
 * Format of the beginning of a `new' core file.
 * The `old' core file consisted of dumping the u area.
 * In the `new' core format, this structure is followed
 * copies of the data and  stack segments.  Finally the user
 * struct is dumped at the end of the core file for programs
 * which really need to know this kind of stuff.  The length
 * of this struct in the core file can be found in the
 * c_len field.  When struct core is changed, c_fpstatus
 * and c_fparegs should start at long word boundaries (to
 * make the floating pointing signal handler run more efficiently).
 */
struct core {
	int	c_magic;		/* Corefile magic number */
	int	c_len;			/* Sizeof (struct core) */
	struct	regs c_regs;		/* General purpose registers */
	struct 	exec c_aouthdr;		/* A.out header */
	int	c_signo;		/* Killing signal, if any */
	int	c_tsize;		/* Text size (bytes) */
	int	c_dsize;		/* Data size (bytes) */
	int	c_ssize;		/* Stack size (bytes) */
	char	c_cmdname[CORE_NAMELEN + 1]; /* Command name */
#if	sparc
#ifdef FPU
	struct fpu c_fpu;		/* external FPU state */
#else
	int	c_ucode;		/* Exception no. from u_code */
#endif
#else	sparc
#if	sun3
	struct 	fp_status c_fpstatus;	/* External FPP state, if any */
	struct  fpa_regs c_fparegs;	/* FPA registers, if any */
	int	c_pad[CORE_PADLEN];	/* see comment above */
#else	sun3
	int	c_ucode;		/* Exception no. from u_code */
#endif	sun3
#endif	sparc
};
#endif	CORE_H_
