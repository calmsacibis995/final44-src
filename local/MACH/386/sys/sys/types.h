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
 * $Log:	types.h,v $
 * Revision 2.6  89/07/12  01:28:10  jjc
 * 	Added definitions of "label_t" and "physadr" for SPARC.
 * 	[88/06/06            jjc]
 * 
 * Revision 2.5  89/03/09  22:09:27  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  17:57:44  gm0w
 * 	Made all CMUCS conditionals to be unconditional.
 * 	Changed romp to ibmrt.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.3  89/01/23  22:29:21  af
 * 	Changes for I386:
 * 		define unchar
 * 		use physaddr and label_t like a vax ???
 * 	[89/01/09            rvb]
 * 	
 * 	Added Mips dependent definitions of "label_t" and "physaddr".
 * 	[89/01/04            af]
 * 
 * Revision 2.2  88/08/24  02:50:41  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:26:37  mwyoung]
 * 
 * 10-Jun-87  Mary Thompson (mrt) at Carnegie Mellon
 *	Changed dependencies on CS_GENERIC to CMU in order to
 *	eliminate include of sys/features.
 *
 * 02-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_BUGFIX:  Restored previous unsigned fixes for _quad and
 *	off_t types by Bill Bolosky although this time under a
 *	different conditional and only under -DKERNEL so that, sigh,
 *	user programs which import the file but don't use the type
 *	consistently won't break.  Of course, lseek takes an off_t as
 *	its second paramter which can be legitimately signed.  This
 *	whole thing is a hack and I suspect that eventually someone is
 *	going to have to end up rewriting some kernel code.
 *	[ V5.1(F4) ]
 *
 * 24-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added 68000 dependent definition of "label_t" and "physadr".
 *	Conditionalized on whether ASSEMBLER is undefined.
 *
 *  7-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Merged Multimax changes.
 *
 * 24-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Moved boolean declaration to its own file.
 *
 * 23-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Renamed "machtypes.h" to "types.h".
 *
 * 16-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	CS_GENERIC: changed type quad from longs to u_longs,
 *	and off_t from int to u_long.
 *
 * 19-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	romp: Added alternate definitions of label_t and physaddr.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 15-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Allow for nested calls of types.h.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)types.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_TYPES_H_
#define _SYS_TYPES_H_

#if	!defined(ASSEMBLER) && !defined(LOCORE)

/*
 * Basic system types and major/minor device constructing/busting macros.
 */

/* major part of a device */
#define major(x)	((int)(((unsigned)(x)>>8)&0377))

/* minor part of a device */
#define minor(x)	((int)((x)&0377))

/* make a device number */
#define makedev(x,y)	((dev_t)(((x)<<8) | (y)))

#include <mach/machine/vm_types.h>

typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
typedef	unsigned short	ushort;		/* sys III compat */
#ifdef	i386
typedef	unsigned char	unchar;		/* kd driver compat */
#endif	i386

#if	defined(vax) || defined(ns32000) || defined(i386)
typedef	struct	_physadr { int r[1]; } *physadr;
typedef	struct	label_t	{
	int	val[14];
} label_t;
#endif	defined(vax) || defined(ns32000) || defined(i386)
#ifdef	ibmrt
typedef	struct	_physadr { int r[1]; } *physadr;
typedef	struct	label_t	{
	int	val[16];
} label_t;
#endif	ibmrt
#ifdef	mc68000
typedef struct  _physadr { short r[1]; } *physadr;
typedef struct  label_t {
        int     val[13];
} label_t;
#endif	mc68000
#ifdef sparc
typedef struct  _physadr { int r[1]; } *physadr;
typedef struct label_t {
        int     val[2];
} label_t;
#endif
#ifdef	mips
typedef	struct	_physadr { int r[1]; } *physadr;
/*
 * WARNING:
 * this must match the definition of kernel jmpbuf's in machine/pcb.h
 */
typedef	struct	label_t	{
	int	val[12];
} label_t;
#endif	mips
#ifdef	KERNEL
typedef	struct	_quad { u_long val[2]; } quad;
#else	KERNEL
typedef	struct	_quad { long val[2]; } quad;
#endif	KERNEL
typedef	long	daddr_t;
typedef	char *	caddr_t;
typedef	u_long	ino_t;
typedef	long	swblk_t;
typedef	long	size_t;
typedef	long	time_t;
typedef	short	dev_t;
#ifdef	KERNEL
typedef	u_long	off_t;
#else	KERNEL
typedef	long	off_t;
#endif	KERNEL
typedef	u_short	uid_t;
typedef	u_short	gid_t;

#define NBBY	8		/* number of bits in a byte */
/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= NOFILE (param.h).
 */
#ifndef	FD_SETSIZE
#define FD_SETSIZE	256
#endif

typedef long	fd_mask;
#define NFDBITS	(sizeof(fd_mask) * NBBY)	/* bits per mask */
#ifndef	howmany
#define howmany(x, y)	(((x)+((y)-1))/(y))
#endif

typedef	struct fd_set {
	fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

#define FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= (1 << ((n) % NFDBITS)))
#define FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= ~(1 << ((n) % NFDBITS)))
#define FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & (1 << ((n) % NFDBITS)))
#define FD_ZERO(p)	bzero((char *)(p), sizeof(*(p)))

#endif	ASSEMBLER
#endif	_SYS_TYPES_H_
