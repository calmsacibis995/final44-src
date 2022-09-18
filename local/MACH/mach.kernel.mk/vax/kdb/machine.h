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
 * $Log:	machine.h,v $
 * Revision 2.4  89/03/09  22:17:24  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/28  12:18:43  mrt
 * 	Updated ../h and ../foo references.
 * 	[89/02/28            rvb]
 * 
 * Revision 2.2  89/02/25  20:22:38  gm0w
 * 	Changes for cleanup.
 * 
 */

/*	machine.h	4.1	81/05/14	*/

#include <sys/vm.h>

#define PAGSIZ		(NBPG*CLSIZE)

#define DBNAME "kdb\n"
#define LPRMODE "%R"
#define OFFMODE "+%R"
#define TXTRNDSIZ	PAGSIZ

#define MAXINT	0x7fffffff
#define MAXSTOR ((1L<<31) - ctob(UPAGES))
#define MAXFILE 0xffffffff

/*
 * INSTACK tells whether its argument is a stack address.
 * INUDOT tells whether its argument is in the (extended) u. area.
 * These are used for consistency checking and dont have to be exact.
 *
 * INKERNEL tells whether its argument is a kernel space address.
 * KVTOPH trims a kernel virtal address back to its offset
 * in the kernel address space.
 */
#define INSTACK(x)	(((x)&0xf0000000) == 0x70000000)
#define INUDOT(x)	(((x)&0xf0000000) == 0x70000000)
#define INKERNEL(x)	(((x)&0xf0000000) == 0x80000000)

#define KVTOPH(x)	((x)&~ 0x80000000)
#define KERNOFF		0x80000000
