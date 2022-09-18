/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	version.h,v $
 * Revision 2.11  89/10/11  23:00:16  dlb
 * 	Bump include version to 26 for new 0-31 priorities.
 * 	[89/10/11            dlb]
 * 
 * Revision 2.10  89/03/09  22:10:19  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/02/25  17:58:26  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.8  89/01/20  18:30:49  jsb
 * 	I guess I'd better not #undef _XXX_INCLUDE_VERSION.
 * 
 * Revision 2.7  89/01/20  17:22:54  jsb
 * 	Change method of allocation of include version numbers to reflect the
 * 	fact that different configurations (vide VICE, MACH_VFS) of the same
 * 	version of a kernel are incompatible.
 * 
 * Revision 2.6  88/08/24  02:53:04  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:28:01  mwyoung]
 * 
 * 13-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Update MACH_VM to #11 and non-Mach to #10.
 *	[ V5.1(XF18) ]
 *
 * 21-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Bumped MACH_VM include version to 5 for SUN debugger related
 *	fixes to the proc and pcb structures.
 *	[ V5.1(F10) ]
 *
 */ 

#ifndef	_SYS_VERSION_H_
#define _SYS_VERSION_H_

/*
 *	Each kernel has a major and minor version number.  Changes in
 *	the major number in general indicate a change in exported features.
 *	Changes in minor number usually correspond to internal-only
 *	changes that the user need not be aware of (in general).  These
 *	values are stored at boot time in the machine_info strucuture and
 *	can be obtained by user programs with the host_info kernel call.
 *	This mechanism is intended to be the formal way for Mach programs
 *	to provide for backward compatibility in future releases.
 *
 *	[ This needs to be reconciled somehow with the major/minor version
 *	  number stuffed into the version string - mja, 5/8/87 ]
 *
 *	Following is an informal history of the numbers:
 *
 *	25-March-87  Avadis Tevanian, Jr.
 *		Created version numbering scheme.  Started with major 1,
 *		minor 0.
 */

#define KERNEL_MAJOR_VERSION	1
#define KERNEL_MINOR_VERSION	0

/* 
 *  Version number of the kernel include files.
 *
 *  This number must be changed whenever an incompatible change is made to one
 *  or more of our include files which are used by application programs that
 *  delve into kernel memory.  The number should normally be simply incremented
 *  but may actually be changed in any manner so long as it differs from the
 *  numbers previously assigned to any other versions with which the current
 *  version is incompatible.  It is used at boot time to determine which
 *  versions of the system programs to install.
 *
 *  Structures that are used by system programs include
 *	user, uthread, utask, proc, file 
 *  Note that the symbol _INCLUDE_VERSION must be set to this in the symbol
 *  table.  On the VAX for example, this is done in locore.s.
 */

#define INCLUDE_VERSION	26			/* add one to me */

#endif	_SYS_VERSION_H_
