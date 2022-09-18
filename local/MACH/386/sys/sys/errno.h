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
 * $Log:	errno.h,v $
 * Revision 2.7  89/03/09  22:03:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  17:53:06  gm0w
 * 	Got rid of CMUCS and MACH conditionals. Removed conditionals
 * 	on MACH_NFS and just defined both names for the conficting error
 * 	codes. Defined MACH_EMULATION error code uncoditionally.
 * 	[89/02/13            mrt]
 * 
 * Revision 2.5  89/01/18  01:15:01  jsb
 * 	Added nfs error numbers ESTALE and EREMOTE.  Handed error name
 * 	collision on EREMOTE by using the symbols ERFSREMOTE and ENFSREMOTE
 * 	inside the kernel, and defining EREMOTE as ENFSREMOTE outside of the
 * 	kernel.  Note that the error numbers for these two errors collide with
 * 	the (out-of-kernel) vice errors EVICEERR and EVICEOP; this shouldn't be
 * 	a problem, since we will never build a system with both vice and nfs.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.4  88/08/24  02:26:24  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:11:43  mwyoung]
 * 
 * Revision 2.3  88/07/19  17:48:02  mwyoung
 * Use CMUCS for user-visible additions.
 * Added ERESTART code for syscall emulation (htg_syscall
 * needs to be restarted)
 * 
 * 25-Jan-88  Sue LoVerso (sue) at Encore Computer Corporation
 *	Added ESUCCESS as 0.
 *
 * 06-Jan-88  Jay Kistler (jjk) at Carnegie Mellon University
 *	Made file reentrant.  Added declarations for __STDC__.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *
 * 05-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added ELOCAL (internal) definition.
 *	[ V5.1(F2) ]
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added definitions for EVICEOP and EVICEERR error numbers.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 22-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  added definition for new EREMOTE error number used
 *	to short-circuit standard processing for systems calls which
 *	have already been handled remotely.
 *	[V1(1)]
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)errno.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_ERRNO_H_
#define _SYS_ERRNO_H_

#ifdef	KERNEL
#include <mach_nfs.h>
#endif	KERNEL

/*
 * Error codes
 */

#define ESUCCESS	0		/* Successful */
#define EPERM		1		/* Not owner */
#define ENOENT		2		/* No such file or directory */
#define ESRCH		3		/* No such process */
#define EINTR		4		/* Interrupted system call */
#define EIO		5		/* I/O error */
#define ENXIO		6		/* No such device or address */
#define E2BIG		7		/* Arg list too long */
#define ENOEXEC		8		/* Exec format error */
#define EBADF		9		/* Bad file number */
#define ECHILD		10		/* No children */
#define EAGAIN		11		/* No more processes */
#define ENOMEM		12		/* Not enough core */
#define EACCES		13		/* Permission denied */
#define EFAULT		14		/* Bad address */
#define ENOTBLK		15		/* Block device required */
#define EBUSY		16		/* Mount device busy */
#define EEXIST		17		/* File exists */
#define EXDEV		18		/* Cross-device link */
#define ENODEV		19		/* No such device */
#define ENOTDIR		20		/* Not a directory*/
#define EISDIR		21		/* Is a directory */
#define EINVAL		22		/* Invalid argument */
#define ENFILE		23		/* File table overflow */
#define EMFILE		24		/* Too many open files */
#define ENOTTY		25		/* Not a typewriter */
#define ETXTBSY		26		/* Text file busy */
#define EFBIG		27		/* File too large */
#define ENOSPC		28		/* No space left on device */
#define ESPIPE		29		/* Illegal seek */
#define EROFS		30		/* Read-only file system */
#define EMLINK		31		/* Too many links */
#define EPIPE		32		/* Broken pipe */

/* math software */
#define EDOM		33		/* Argument too large */
#define ERANGE		34		/* Result too large */

/* non-blocking and interrupt i/o */
#define EWOULDBLOCK	35		/* Operation would block */
#define EDEADLK		EWOULDBLOCK	/* ditto */
#define EINPROGRESS	36		/* Operation now in progress */
#define EALREADY	37		/* Operation already in progress */

/* ipc/network software */

	/* argument errors */
#define ENOTSOCK	38		/* Socket operation on non-socket */
#define EDESTADDRREQ	39		/* Destination address required */
#define EMSGSIZE	40		/* Message too long */
#define EPROTOTYPE	41		/* Protocol wrong type for socket */
#define ENOPROTOOPT	42		/* Protocol not available */
#define EPROTONOSUPPORT	43		/* Protocol not supported */
#define ESOCKTNOSUPPORT	44		/* Socket type not supported */
#define EOPNOTSUPP	45		/* Operation not supported on socket */
#define EPFNOSUPPORT	46		/* Protocol family not supported */
#define EAFNOSUPPORT	47		/* Address family not supported by protocol family */
#define EADDRINUSE	48		/* Address already in use */
#define EADDRNOTAVAIL	49		/* Can't assign requested address */

	/* operational errors */
#define ENETDOWN	50		/* Network is down */
#define ENETUNREACH	51		/* Network is unreachable */
#define ENETRESET	52		/* Network dropped connection on reset */
#define ECONNABORTED	53		/* Software caused connection abort */
#define ECONNRESET	54		/* Connection reset by peer */
#define ENOBUFS		55		/* No buffer space available */
#define EISCONN		56		/* Socket is already connected */
#define ENOTCONN	57		/* Socket is not connected */
#define ESHUTDOWN	58		/* Can't send after socket shutdown */
#define ETOOMANYREFS	59		/* Too many references: can't splice */
#define ETIMEDOUT	60		/* Connection timed out */
#define ECONNREFUSED	61		/* Connection refused */

	/* */
#define ELOOP		62		/* Too many levels of symbolic links */
#define ENAMETOOLONG	63		/* File name too long */

/* should be rearranged */
#define EHOSTDOWN	64		/* Host is down */
#define EHOSTUNREACH	65		/* No route to host */
#define ENOTEMPTY	66		/* Directory not empty */

/* quotas & mush */
#define EPROCLIM	67		/* Too many processes */
#define EUSERS		68		/* Too many users */
#define EDQUOT		69		/* Disc quota exceeded */

/* error codes used by MACH_RFS */
/*
 *  The ERFSREMOTE code is used to short-circuit standard system call
 *  processing which uses the namei() routine.  When namei() determines that a
 *  valid remote name access has been made, it directly calls the remote file
 *  system call code itself to process the call.  Upon returning to its caller,
 *  however, it must return a failure indication to prevent the system call
 *  from being processed any further locally.  This error number (along with an
 *  inode pointer of NULL) is used to accomplish this.  It is recognized
 *  specially by the system call handler and cleared before completing transfer
 *  of control back to the user process.
 *
 *  The ELOCAL code is returned to namei() by the remote file system code to
 *  indicate that the remote pathname was indeed local and should continue to
 *  be processed.
 */
#define ELOCAL		126		/* namei should continue locally */
#define ERFSREMOTE	127		/* namei was handled remotely */

/*
 *  MACH_NFS errors. Note that these conflict with VICE error numbers.
 */
#define ESTALE		70		/* Stale NFS file handle */
#define ENFSREMOTE	71		/* Too many levels of remote in path */

/*  VICE error codes
 *  Vice file access errors (that can't be mapped to standard error messages)
 */
#define EVICEERR	70		/* Remote file system error -- 
					   could be anything; more precise 
					   details should be reported
					   elsewhere by the system */
#define EVICEOP		71		/* syscall was handled by Vice */


/* MACH_EMULATION error code */
#define ERESTART       	72


#ifndef	KERNEL
/*
 *  Old references to (RFS's) EREMOTE in the kernel should be changed to
 *  ERFSREMOTE. We leave EREMOTE undefined in the kernel, so that we
 *  can catch old uses of it, particularly in ${machine}/trap.c.
 *  Outside of the kernel, EREMOTE now refers to the NFS error code.
 */
#define EREMOTE		ENFSREMOTE
#endif	KERNEL

#if	defined(__STDC__) && !defined(KERNEL)
extern int errno;
extern void perror(const char *);
extern char *sys_errlist[];
extern int sys_nerr;
#endif	defined(__STDC__) && !defined(KERNEL)

#endif	_SYS_ERRNO_H_
