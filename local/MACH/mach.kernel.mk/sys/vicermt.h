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
 * $Log:	vicermt.h,v $
 * Revision 2.10  89/07/12  01:28:17  jjc
 * 	Changed "#ifdef sun3" into "if defined(sun3) || defined(sun4)".
 * 	[89/05/06            jjc]
 * 
 * Revision 2.9  89/05/30  10:44:23  rvb
 * 	Bumped RMT_MAJ for mips, due to conflict with Ultrix.
 * 	[89/04/20            af]
 * 
 * Revision 2.8  89/03/09  22:10:34  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  17:58:37  gm0w
 * 	Changed to generic machine  names and eliminted include
 * 	of cputypes.h.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.6  89/01/23  22:30:03  af
 * 	RMT_MAJ for Mips.  Also, added for i386.
 * 	[89/01/09            af]
 * 
 * Revision 2.5  88/08/24  02:53:34  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:28:21  mwyoung]
 * 
 * Revision 2.4  88/08/22  21:30:53  mja
 * 	Add RT_unimpl definition.
 * 	[88/08/09  09:56:27  mja]
 * 
 * Revision 2.3  88/07/15  16:05:41  mja
 * RT_preclose => RT_tryclose.
 * 
 * 21-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added RT_preclose definition.
 *	[ V5.1(XF23) ]
 *
 * 06-Jan-88  Jay Kistler (jjk) at Carnegie Mellon University
 *	Moved the definition of struct im_arg outside the definition of
 *	struct intercept_message to satisfy the C++ translator.
 *
 * 29-Apr-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	RMT_MAJ for Sequent
 *
 *  5-Mar-87  David L. Black (dlb) at Carnegie-Mellon University
 *	Fix RT_MAX_ARGS macro, define RMT_MAJ for Multimax (10).
 *
 * 15-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Assign major numbers for RMT_MAJ as 34 for sun and 60 for vax.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	ibm032 -> romp.
 *
 * 11-Nov-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Added definition for RT_panic.
 *
 * 22-Oct-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Created from Andrew's remote.h.
 *
 */
/*
 * ITC Remote file system - kernel interface declarations
 */

#ifndef	_SYS_VICERMT_H_
#define _SYS_VICERMT_H_

#include <sys/types.h>
#include <sys/param.h>		/* for MAXPATHLEN */

#define RT_VERSION	3	/* Version number, should be incremented
				   before incompatible changes are released */
/*
 *      Version 1 - April 4/84.
 * 	Version 2 - May 4/84.
 *      Version 3 - May 30/85.
 *      Version 4 - June 19/85.
 */

/* Maximum number of arguments to a system call - from u_arg in user.h */
#define RT_MAX_ARGS		(8)

/* im_arg contains a representation of the arguments to the intercepted
       system call, when transmitted from the kernel to Venus.
       Returned values are passed back from Venus to the kernel the same way */
struct im_arg {
    int	im_aval; 	/* Value of the argument
				 OR index of argument in im_data */
    int	im_asize;	/* If im_aval is the index of an argument in
				 im_data, then this is its size in bytes.
				 Otherwise this is 0. */
};

/* Maximum size of combined string or structure arguments passed between
   the kernel and a venus */
#define RT_MAXDATASIZE		(MAXPATHLEN*2)

/* The format of the message passed between Venus and the kernel */
struct	intercept_message {
    u_short	im_type;	/* Message type */
    u_short     im_dsize;	/* Number of bytes in im_data */
    int		im_client;	/* The process id of the client side of the
    				   transaction */
    short	im_uid;		/* The effective user id of the client */
    short	im_gid;		/* The effective group id of the client */
    int		im_seq;		/* The sequence number of this transaction.
				   Never 0 */
    long	im_wdfid[3];	/* Current directory on the remote file system
    				   Vice II only. */
    int		im_error;	/* u.u_error copied from this */
    char	im_follow1;	/* 1=>follow last component of first pathname
				   if symbolic link; 0=>don't */
    char	im_follow2;	/* ditto for second pathname */
    long	im_pag;		/* process authentication group */
    struct im_arg   im_arg[RT_MAX_ARGS];
    char	im_data[RT_MAXDATASIZE];
				/* Variable length field containing string
				   or structure arguments */
    /* No fields should be added here, the record may be truncated on
       transmission in either direction to an appropriate size */
};

#define RT_HEADERSIZE	((sizeof (struct intercept_message)) - RT_MAXDATASIZE)

#ifdef	KERNEL
#include <vicefs.h>

/* The following shouldn't be done in this manner, but there doesn't
   seem to be an easy mechanism to discover the device id.  The auto-
   config stuff is only for real devices, I think.
 */
#if	defined(sun3) || defined(sun4)
#define RMT_MAJ		34
#endif	defined(sun3) || defined(sun4)
#ifdef	vax
#define RMT_MAJ		60
#endif	vax
#ifdef	ibmrt
#define RMT_MAJ		16
#endif	ibmrt
#if	multimax
#define RMT_MAJ		10
#endif	multimax
#if	balance
#define RMT_MAJ		18
#endif	balance
#ifdef	i386
#define RMT_MAJ		7
#endif	i386
#ifdef	mips
#define RMT_MAJ		12
#endif	mips
/* Sleep priorities */
#define RMT_NOINT_PRI	(PINOD+1)/* Sleep with signal handling enabled */
#define RMT_INTOK_PRI	(PSLEP-1)/* Disallow aborts due to signal handling */

/* Private data used by the remote intercept routines in the kernel */
/* Note:  this was originally designed for only a single remote device.
   To make it work for multiple devices, I simply unfolded the code
   by turning this into an array (1 entry per device) and using a macro
   in the code to reference the appropriate entry. */
struct remote {
    int		rt_flags;	/* for flag values, see below */
    int		rt_seq;		/* sequence number generator */
    char	rt_open;	/* 1 if the device is open */
    struct proc	*rt_selproc;	/* process waiting for select */
    char	rt_attach;	/* wait channel for process waiting to attach
    				   this structure */
    char	rt_read;	/* wait channel for a venus waiting for an
    				   intercept */
    char	rt_reply;	/* wait channel for a client process waiting
    				   for a reply */
    struct	intercept_message rt_imr;	/* buffer for agent reads */
    struct	intercept_message rt_imw;	/* buffer for agent writes */
};

#if	NVICEFS > 0
extern struct remote remote[NVICEFS];
#endif	NVICEFS > 0

/* Hack to unfold code for multiple devices */
#define rmt     (*rmtp)
#define devhack(dev) register struct remote *rmtp = &remote[minor(dev)]

/* Flags for rmt.rt_flags */
#define RT_RBUF		1	/* processing venus read request */
#define RT_WBUF		2	/* processing venus write request */
#define RT_SENDING	4	/* sending the structure to the venus */
#define RT_REPLY	8	/* reply from venus to client */
#define RT_SIGNAL	16	/* signal occured, want to send message to
				   venus at next opportunity */

#endif	KERNEL

/*
 * Message type codes for messages sent from the kernel.
 * NB:  the kernel ignores the type field on reply (it merely matches
 * sequence numbers).  Unexpected messages from an venus are ignored (they
 * may have been destined for a process which has died in the meantime).
 * At all times, the kernel tries to maintain its own integrity, so that
 * in the worst case an venus restart should work fine.
 */

/*
 * In the capsule descriptions below, "(?)" means that the flagged item
 * is probably a good candidate for negotiation.
 */

#define RT_BOGUS	0
/* For debugging purposes in kernel */

#define RT_access	1
/* From kernel: 0: uninterpreted part of pathname
 *		1: mode
 * NB: uid/gid for this call are the real (not effective) uid/gid's.
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 * NB: return value is implicit in im_error.
 */

#define RT_chdir	2
/* From kernel: 0: uninterpreted part of pathname
 * Vice I response:
 *		0: new pathname (with ..'s removed, symbolic
 *		   links NOT expanded).
 *		   length<MAXPATHLEN.  Null terminated.
 *		im_error
 * Vice II response:
 * 		im_wdfid:  the file identifier (volume, vnode, unique)
 * 		   of the new working directory.
 *		im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_chmod	3
/* From kernel: 0: uninterpreted part of pathname
 *		1: mode
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_chown	4
/* From kernel: 0: uninterpreted part of pathname
 *		1: new uid
 *		2: new gid
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_close	5
/* From kernel: 0: file identifier.
 *		im_error: either 0 or one of the error codes
 *			  listed below (RTE_*, see RT_open).
 * Response:	im_error (for programs that want to know)
 * N.B.: close MUST always cleanup state; it will never be issued
 * twice for the same identifier.  If RT_signal is received during
 * a close, venus can use this as a hint to return early from the
 * close.  Venus should not return EINTR for this system call, however.
 */

#define RT_fchmod	6
/* From kernel: 0: file identifier
 * 		1: mode
 * Response:	im_error
 */

#define RT_fchown	7
/* From kernel:	0: file identifier
 *		1: new uid
 *		2: new gid
 * Response:	im_error
 */

#define RT_fcntl	8
/* Not implemented */

#define RT_flock	9
/* From kernel: 0: file identifier
 *  		1: operation
 * Response:	im_error
 */

#define RT_fstat	10
/* From kernel: 0: file identifier.
 * Response:	0: struct stat
 *		im_error
 */

#define RT_fsync	11
/* From kernel: 0: file identifier.
 * Response:	im_error
 */

#define RT_ftruncate	12
/* From kernel: 0: file identifier.
 *		1: truncated length. (? right now, kernel truncates
 *		   open cached inode)
 * Response:	im_error
 */

#define RT_link		13
/* From kernel: 0: the uninterpreted part of the original path
 *		1: the uninterpreted part of the pathname which
 *		   will be the new link
 * Response:	im_error
 * if im_error == EABSPATH1 or EABSPATH2 then:
 *		0: Resolved absolute path name.
 */

#define RT_lstat	14
/* Obsolete--not generated by the kernel.  The im_follow1
   field is used in conjunction with RT_stat to implement
   lstat.  VICE I will continue to work since it does not
   distinguish between stat and lstat */

#define RT_mkdir	15
/* From kernel: 0: uninterpreted part of pathname
 *		1: mode
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_open		16
/* From kernel: 0: uninterpreted part of pathname
 *	        1: flags
 *		2: mode
 * Vice 1 Response:
 *		0: file identifier assigned (for subsequent
 * 	  	   messages dealing with open files).
 *		1: pathname of the local, cached file.	
 *		im_error
 * Note:	the returned filename is not created, truncated(?),
 *  		or otherwise fiddled with by the kernel.  It must
 *		exist and must be a plain file.  N.B: Protection modes
 *		are ignored when it is finally opened.  The exec bit,
 *		however, should never be set unless the file is
 *		really executable.  (It should never be set for
 *		directories).  If there are problems opening the
 *		file, the user gets an error, the kernel gets a close
 *		message (possibly with one of the RTE_* errors, below,
 *		set in im_error).
 * Vice 2 Response:
 *		0: file identifier assigned (for subsequent
 * 	  	   messages dealing with open files).
 *		1: device where the file resides.
 *	 	2: inode number of the file.
 * 		im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 * (?) Non-blocking open.
 */

#define RT_readlink	17
/* From kernel: 0: uninterpreted part of link pathname
 * Response:	0: number of characters read from link
 *		1: contents of link (not null terminated).  Size must not be
 *		   greater than MAXPATHLEN (because this is checked by the
 *		   kernel intercept code).
 *		im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_rename	18
/* From kernel: 0: uninterpreted part of original pathname
 *  		1: ditto for new pathname
 * Response:	im_error
 * if im_error == EABSPATH1 or EABSPATH2 then:
 *		0: Resolved absolute path name.
 */

#define RT_rmdir	19
/* From kernel: 0: uninterpreted part of pathname
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_stat		20
/* From kernel: 0: uninterpreted part of pathname
 * Response:	0: struct stat
 * 		im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 * Note:  this now implements the lstat call, as well,
 * by means of the im_follow1 field in the header.
 */

#define RT_symlink	21
/* From kernel: 0: the string value of the new symbolic link.
 *		1: the uninterpreted part of the pathname to
 *		   contain the link.
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_truncate	22
/* From kernel: 0: uninterpreted part of pathname
 *		1: truncated length
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_unlink	23
/* From kernel: 0: uninterpreted part of pathname
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_utimes	24
/* From kernel: 0: uninterpreted part of pathname
 *		1: struct timeval tvp[2]
 * Response:	im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */

#define RT_signal	25
/* Request to abort the previous operation requested WITH THE
 * SAME im_seq FIELD.  No action is expected on the part of
 * the venus--this is merely advice that the operation may
 * be completed early.  VENUS SHOULD NOT REPLY TO THIS MESSAGE.
 * The error returned on final completion by the venus need not
 * acknowledge that the system call was interrupted.  The interrupt
 * will occur at the end of the system call regardless.  EINTR
 * should be returned if the system call actually is aborted.
 * VENUS MAY RETURN EARLY FROM A   C L O S E  SYSTEM CALL, BUT MUST STILL
 * CLEANUP STATE FOR THE CLOSE--ANOTHER CLOSE CALL FOR THE SAME
 * DESCRIPTOR WILL NEVER BE ISSUED.
 * RT_signal messages for which a reply has already been issued
 * sholuld be ignored by venus.
 */

#define RT_ioctl	26
/*
 * From kernel: 0: file identifier
 *              1: command (see below)
 *              2: uninterpreted data (up to RT_MAXDATASIZE).
 * Response:    0: data to be returned to user
 *              im_error
 * NOTE:  the information passed to/from venus is not in the
 * same format as that coming to/from the user.  See the file
 * vice.h.
 */


#define RT_pioctl	27
/*
 * From kernel: 0: uninterpreted part of pathname
 * 		1: command (as in RT_ioctl)
 *		2: uninterpreted data
 * Note: argument 3, do not follow symbolic links, is
 *   obsolete; this is compatible with VICE I, since the
 *   field was ignored anyway.
 * Response:    0: data to be returned to user
 *		im_error
 * if im_error == EABSPATH1 then:
 *		0: Resolved absolute path name.
 */


#define RT_tryclose	28
/* From kernel: 0: file identifier.
 * Response:	im_error
 *
 * An error reply of ENOSPC or EDQUOT is guaranteed to be retriable.
 * Any others, along with a success indicate that venus has cleaned
 * up any state for the file and the kernel should do likewise.
 */


#define RT_unimpl	126
/*
 *  Dummy code used to detect when a system call is not supprted in
 *  the remote domain.
 */


#define RT_panic	127
/*
 *  Dummy code used to detect when a system call has illegally tried to
 *  enter the remote domain.
 */


/* Error codes -- each is set by the kernel for the explicit error indicated.
 * These are set in im_error (which should normally be 0 in every message from
 * the kernel).  Errors of this form indicate that the venus process has
 * almost certainly done something wrong.  The associated user process gets an
 * EVICEERR (remote file system error) for each of these error types.
 */

/* The following error codes all occur at open (exec?) and are sent by the
 * kernel with the associated close message for the file identifier returned
 * from the open.
 */

#define RTE_BADARG 1    /* The size of a structure or string argument returned
			   by the venus to the kernel is bogus.
			   (the im_size field is not zero, or part of the
			   argument is outside the message buffer, or the
			   argument is too large) */

#define RTE_NOFILE 2	/* The file name (or inode, in VICE II) returned to
			   the kernel, to open or exec in lieu of the original
			   name supplied by the process cannot be opened or
			   exec'd */

#define RTE_NOTREG 3    /* The file (or inode, in VICE II) returned to the
			   kernel, to open or exec in lieu of the original
			   name supplied by the process, is not a IF_REG
			   type file, i.e. it is a device, socket, or
			   directory */


/* The following error codes are set by Venus when a pathname argument supplied
 * by the kernel resolves to an absolute pathname outside of the name space 
 * of this venus.  The resolved absolute pathname is returned in argument 0.
 * The kernel is expected to retry the system call with this new information.
 * The kernel never passes this error on to the original issuer of the system
 * call.
 */
#define EABSPATH1 126	/* The first pathname, or only pathname, of a system
			   call resolved to an absolute pathname */
#define EABSPATH2 127	/* The second pathname of the rename or link system
			   call resolved to an absolute pathname */

#endif	_SYS_VICERMT_H_
