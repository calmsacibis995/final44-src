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
 * $Log:	rfs.h,v $
 * Revision 2.9  89/07/30  18:37:04  gm0w
 * 	Added RFST_GETDIRENTS for getdirentries system call.  Moved
 * 	a KERNEL #ifdef back to its original (correct) location.
 * 	[89/06/17            gm0w]
 * 
 * Revision 2.8  89/04/22  15:26:35  gm0w
 * 	Removed MACH_VFS and MACH_NFS code/conditionals.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.7  89/03/15  15:12:05  gm0w
 * 	renamed _SYS_RFS_H_ to _RFS_RFS_H_ to reflect new location of file
 * 
 * Revision 2.6  89/03/09  22:07:17  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  17:56:00  gm0w
 * 	Put all the MACH_VFS stuff under #ifdef KERNEL.
 * 	Put include of kern/lock.h under #ifdef KERNEL.
 * 	[89/02/20            mrt]
 * 
 * Revision 2.4  89/01/18  01:18:52  jsb
 * 	Vnode support: include vfs/{vnode,pathname}.h.
 * 	NFS support: (invisibly) rename rfs_readlink to avoid conflict with
 * 	rnode function of same name.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.3  88/08/24  02:42:13  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:21:46  mwyoung]
 * 
 * Revision 2.2  88/08/22  21:30:13  mja
 * 	Redefine rfs_sysent[] as a macro which offsets to call #0
 * 	in the actual rfs_cmusysent[] table in order to process the
 * 	negative system call numbers without crashing.
 * 	[88/08/08  17:44:24  mja]
 * 
 * 09-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fix alignment problem in rfsInitDescriptor() that neglected to
 *	insure that the allocation size was aligned on a long-word
 *	boundary (since this matters on the RT when multiple structures
 *	are carved out of the same mbuf).
 *	[ V5.1(F6) ]
 *
 * 05-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Bumped protocol version to 2 to indicate implementation
 *	which can handle the pathname pass back (which should have been
 *	done originally when the feature was added);  added new
 *	RFST_ABORT message type;  increased flags width to 16-bits to
 *	handle new RFSF_ABORTING and RFSF_EINTR bits for aborting a
 *	remote operation; added new externs for abort fucntions.
 *	[ V5.1(F5) ]
 *
 * 05-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Add RFSF_LREPLY, RFST_LREPLY and RFSRW_LOOKUP definitions,
 *	and pathname buffer and remote device and i-number fields to
 *	remote connection block.
 *	[ V5.1(F2) ]
 *
 * 11-Dec-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Use explicitly padded stat structure in RFS message structure
 *	for the Sun.
 *
 * 01-Nov-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added new RFST_BANNER definition which is the first 32-bit
 *	value (4 bytes) sent on any new connection that can be used by
 *	the remote system to determine the local byte order.
 *	[ V5.1(F1) ]
 *
 * 30-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Converted "bool" uses to "boolean_t".
 *
 * 13-Dec-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Reorganized for new RFS name.
 *
 * 18-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Begin conversion for 4.2BSD.
 *
 * 21-Jan-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 *
 *  Remote file system - definitions and data structures
 *
 */

#ifndef	_RFS_RFS_H_
#define _RFS_RFS_H_

#ifdef	KERNEL
#include <kern/queue.h>
#endif	KERNEL

#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <netinet/in.h>

/*
 *  Fundamental constants of the implementation.
 */

#define RFSPORT		771		/* UNIX system call port */
#define RFSVERSION	2		/* protocol version #2 */
#define RFSMAXRETRY	10		/* times to retry refused connection */
					/*  attempts */
#define RFSMAXCACHE	32		/* maximum execution cache entries */

#define NRFSCACHE	31		/* length of cache array */


#ifdef	KERNEL
/*
 *  Hide these names so they don't conflict with nfs.
 */
#define		rfs_readlink	cmu_rfs_readlink
#define		rfs_symlink	cmu_rfs_symlink

/*
 *  Define this to compile-in debugging code statements.  The initial
 *  contents of the debug flag bits will be the value of the symbol.
 */
#define RFSDEBUG	0	/* default debug flags */

#ifdef	RFSDEBUG
/*
 *  Debug flag bits.
 */
#define RFSD_LOG	01	/* general log messages */
#define RFSD_PROTOCOL	02	/* protocol dialogue */
#define RFSD_S_TRACEIN	04	/* syscall procedure entry trace */
#define RFSD_S_TRACEOUT	010	/* syscall procedure exit trace */
#define RFSD_C_TRACEIN	020	/* connection procedure entry trace */
#define RFSD_C_TRACEOUT	040	/* connection procedure exit trace */
#define RFSD_P_TRACEIN	0100	/* protocol procedure entry trace */
#define RFSD_P_TRACEOUT	0200	/* protocol procedure exit trace */
#define RFSD_U_TRACEIN	0400	/* utility procedure entry trace */
#define RFSD_U_TRACEOUT	01000	/* utility procedure exit trace */

/*
 *  Common prefix and suffix for all debugging print statements.  
 *
 *  Avoid printing any additional messages until the controlling terminal
 *  output queue has drained.
 */
#define RFS_PRF(flags)		\
    if (rfsDebug&(flags))	\
    {				\
	rfsWaitTTY(u.u_ttyp);	\
	uprintf			\
	(
#define RFS_FRP()		\
	);			\
    }

/*
 *  The pre-processor doesn't really support macros with variable numbers of
 *  arguments so we're stuck with defining as many of these as there are
 *  invocations with different numbers of arguments.  We really need to have
 *  all the parameters to the printf() inside the macro definition so they will
 *  completely disappear when debugging is turned off (including string
 *  constants).
 */
#define rfs_printf1(flags, arg1) \
    RFS_PRF(flags) arg1 RFS_FRP()
#define rfs_printf2(flags, arg1, arg2) \
    RFS_PRF(flags) arg1, arg2 RFS_FRP()
#define rfs_printf3(flags, arg1, arg2, arg3) \
    RFS_PRF(flags) arg1, arg2, arg3 RFS_FRP()
#define rfs_printf4(flags, arg1, arg2, arg3, arg4) \
    RFS_PRF(flags) arg1, arg2, arg3, arg4 RFS_FRP()
#define rfs_printf5(flags, arg1, arg2, arg3, arg4, arg5) \
    RFS_PRF(flags) arg1, arg2, arg3, arg4, arg5 RFS_FRP()
#define rfs_printf6(flags, arg1, arg2, arg3, arg4, arg5, arg6) \
    RFS_PRF(flags) arg1, arg2, arg3, arg4, arg5, arg6 RFS_FRP()
#define rfs_printf7(flags, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
    RFS_PRF(flags) arg1, arg2, arg3, arg4, arg5, arg6, arg7 RFS_FRP()

extern char *syscallnames[];

#else	RFSDEBUG
/*
 *  Without debugging on, expand these to nothing.
 */
#define rfs_printf1(flags, arg1) 
#define rfs_printf2(flags, arg1, arg2) 
#define rfs_printf3(flags, arg1, arg2, arg3) 
#define rfs_printf4(flags, arg1, arg2, arg3, arg4) 
#define rfs_printf5(flags, arg1, arg2, arg3, arg4, arg5) 
#define rfs_printf6(flags, arg1, arg2, arg3, arg4, arg5, arg6) 
#define rfs_printf7(flags, arg1, arg2, arg3, arg4, arg5, arg6, arg7) 
#endif	RFSDEBUG
#endif	KERNEL



/*
 *  Utility request/reply message format.
 */

struct rfsMsg
{
    union
    {
	u_char  rmsg_h_byte[8];
	u_short rmsg_h_word[4];
	u_long  rmsg_h_long[2];
	char    rmsg_h_char[8];
	short   rmsg_h_short[4];
	long    rmsg_h_int[2];
    } rmsg_header;
    union
    {
	int	    rmsg_b_cid;
	char        rmsg_b_buff[IOCPARM_MASK+1];
#ifdef	sun
	struct padded_stat rmsg_b_stat;	/* explicitly padded stat struct. */
#else	sun
	struct stat rmsg_b_stat;
#endif	sun
	struct timeval rmsg_b_tv[2];
	time_t	    rmsg_b_time[2];
    } rmsg_body;
};

#define rmsg_code	rmsg_header.rmsg_h_byte[0]
#define rmsg_rcode	rmsg_header.rmsg_h_byte[1]
#define rmsg_errno	rmsg_header.rmsg_h_short[1]
#define rmsg_rval	rmsg_header.rmsg_h_int[1]

#define rmsg_A_code	rmsg_header.rmsg_h_byte[0]
#define rmsg_A_desc	rmsg_header.rmsg_h_byte[1]
#define rmsg_A_s_param	rmsg_header.rmsg_h_short[1]
#define rmsg_A_ul_param	rmsg_header.rmsg_h_long[1]
#define rmsg_A_buff	rmsg_body.rmsg_b_buff
#define rmsg_A_stat	rmsg_body.rmsg_b_stat

#define rmsg_B_code	rmsg_header.rmsg_h_byte[0]
#define rmsg_B_desc	rmsg_header.rmsg_h_byte[1]
#define rmsg_B_bsize	rmsg_header.rmsg_h_word[1]
#define rmsg_B_l_param	rmsg_header.rmsg_h_int[1]
#define rmsg_B_buff	rmsg_body.rmsg_b_buff

#define rmsg_C_banner	rmsg_header.rmsg_h_int[0]
#define rmsg_C_code	rmsg_header.rmsg_h_byte[0]
#define rmsg_C_vers	rmsg_header.rmsg_h_byte[3]
#define rmsg_C_usrlen	rmsg_header.rmsg_h_byte[4]
#define rmsg_C_grplen	rmsg_header.rmsg_h_byte[5]
#define rmsg_C_acclen	rmsg_header.rmsg_h_byte[6]
#define rmsg_C_pswlen	rmsg_header.rmsg_h_byte[7]
#define rmsg_C_cid	rmsg_body.rmsg_b_cid

#define rmsg_N_code	rmsg_header.rmsg_h_byte[0]
#define rmsg_N_mbz	rmsg_header.rmsg_h_byte[1]
#define rmsg_N_len	rmsg_header.rmsg_h_word[1]
#define rmsg_N_l_param	rmsg_header.rmsg_h_int[1]
#define rmsg_N_buff	rmsg_body.rmsg_b_buff
#define rmsg_N_stat	rmsg_body.rmsg_b_stat

#define rmsg_M_code	rmsg_header.rmsg_h_byte[0]
#define rmsg_M_mbz	rmsg_header.rmsg_h_byte[1]
#define rmsg_M_len	rmsg_header.rmsg_h_word[1]
#define rmsg_M_s_param1	rmsg_header.rmsg_h_short[2]
#define rmsg_M_s_param2	rmsg_header.rmsg_h_short[3]
#define rmsg_M_time	rmsg_body.rmsg_b_time
#define rmsg_M_tv	rmsg_body.rmsg_b_tv

#define rmsg_P_code	rmsg_header.rmsg_h_byte[0]
#define rmsg_P_mbz	rmsg_header.rmsg_h_byte[1]
#define rmsg_P_len1	rmsg_header.rmsg_h_word[1]
#define rmsg_P_len2	rmsg_header.rmsg_h_word[2]
#define rmsg_P_s_param	rmsg_header.rmsg_h_short[3]

#define rmsg_Z_code	rmsg_header.rmsg_h_byte[0]
#define rmsg_Z_mbz	rmsg_header.rmsg_h_byte[1]
#define rmsg_Z_s_param	rmsg_header.rmsg_h_short[1]
#define rmsg_Z_l_param	rmsg_header.rmsg_h_int[1]




/*
 *  System call message types
 */

#define RFST_FORK	2
#define RFST_READ	3
#define RFST_WRITE	4
#define RFST_OPEN	5
#define RFST_CLOSE	6
#define RFST_CREAT	8
#define RFST_LINK	9
#define RFST_UNLINK	10
#define RFST_EXEC	11
#define RFST_CHDIR	12
#define RFST_MKNOD	14
#define RFST_CHMOD	15
#define RFST_CHOWN	16
#define RFST_OSTAT	18
#define RFST_LSEEK	19
#define RFST_OFSTAT	28
#define RFST_UTIME	30
#define RFST_ACCESS	33
#define RFST_NSTAT	38
#define RFST_LSTAT	40
#define RFST_IOCTL	54
#define RFST_SYMLINK	57
#define RFST_READLINK	58
#define RFST_EXECE	59
#define RFST_UMASK	60
#define RFST_CHROOT	61
#define RFST_NFSTAT	62
#define RFST_FCNTL	92
#define RFST_FSYNC	95
#define RFST_FCHOWN	123
#define RFST_FCHMOD	124
#define RFST_RENAME	128
#define RFST_TRUNCATE	129
#define RFST_FTRUNCATE	130
#define RFST_FLOCK	131
#define RFST_MKDIR	136
#define RFST_RMDIR	137
#define RFST_UTIMES	138
#define RFST_GETDIRENTS	156

/*
 *  Control message types  
 */
#define RFST_ABORT	0370	/* abort operation */
#define RFST_LREPLY	0371	/* "is local" reply */
#define RFST_IDENTIFY	0372
#define RFST_REPLY	0373
#define RFST_CONNECT	0376
#define RFST_NOP	0377

/*
 *  Standard connection banner defined as a 32-bit value rather than as a
 *  stream of bytes so that the remote host can determine our byte order by
 *  examining the first four bytes sent on the connection.  This banner value
 *  is machine independent (contrary to what we may have previously believed)!
 */
#define RFST_BANNER	((((((RFSVERSION<<8)|(RFST_CONNECT-2))<<8)|(RFST_CONNECT-1))<<8)|RFST_CONNECT)

/*
 *  Message type modifiers
 */
#define RFST_KERNEL	0400		/* XXX */



/*
 *  Read/write modes
 *
 *  Use an enumerated type to define the values but a separate type definition
 *  for casting in storage to consume less space.
 */

enum rfsRW
{
    RFSRW_NONE,				/* undefined */
    RFSRW_USER,				/* user name */
    RFSRW_GROUP,			/* group name */
    RFSRW_ACCOUNT,			/* account name */
    RFSRW_PASSWORD,			/* password */
    RFSRW_LOOKUP,			/* remote name */
};
typedef	u_char rfsRW_t;



/*
 *  ioctl calls
 */

#define RFSIOCGETRW	_IOR(R, 0, rfsRW_t)
#define RFSIOCSETRW	_IOW(R, 1, rfsRW_t)
#define RFSIOCGETS	_IOR(R, 2, int)
#define RFSIOCSETS	_IOW(R, 3, int)
#define RFSIOCIDENTIFY	_IO (R, 4)



#ifdef	KERNEL
/*
 *  Remote file system identity entry
 */

struct rfsWho
{
    char    rw_user[8];			/* optional user name */
    char    rw_password[8];		/* password for user */
    char    rw_group[8];		/* optional group name */
    char    rw_account[8];		/* optional account name */
    u_char  rw_luser;			/* user name length */
    u_char  rw_lpassword;		/* password length */
    u_char  rw_lgroup;			/* group name length */
    u_char  rw_laccount;		/* account name length */
    u_short rw_refc;			/* reference count */
};


/*
 *  rfsIncrCheckWho - increment remote identity reference count
 *
 *  rwp = remote identity entry for increment
 *
 *  Increment the reference count and panic on overflow back to zero.
 */

#define rfsIncrCheckWho(rwp)	\
	if (++((rwp)->rw_refc) == 0) panic(rfsPanicMsg_IncrWho)
extern char *rfsPanicMsg_IncrWho;

/*
 *  rfsDecrCheckWho - decrement remote identity reference count
 *
 *  rwp = remote identity entry for decrement
 *
 *  Decrement the reference count and panic on underflow below zero.
 */

#define rfsDecrCheckWho(rwp)	\
	if (((rwp)->rw_refc)-- == 0) panic(rfsPanicMsg_DecrWho)
extern char *rfsPanicMsg_DecrWho;



/*
 *  Remote link inode contents layout
 */

struct rfsLink
{
    struct in_addr rl_addr;		/* remote IP addr */
    u_short 	   rl_fport;		/* remote contact port */
    u_char  	   rl_pvers;		/* RFS protocol version */
    u_char	   rl_pad;		/* (unused) */
};



/*
 *  Remote file system connection block
 *
 *  N.B. If you add any fields to this structure, you must make the appropriate
 *  updates to rfsGet() and rfsCopy() to respectively initialize and preserve
 *  the new fields.
 */

#define rfsConnectionQueue	Queue

struct rfsConnectionBlock
{
    struct rfsConnectionQueue
	           rcb_link;		/* forward/back link */
    struct rfsLink rcb_rl;		/* remote IP addr */
    struct socket *rcb_so;		/* socket pointer */
    struct inode  *rcb_ip;		/* remote link inode pointer */
    struct rfsWho *rcb_rwp;		/* user name/password information */
    u_short        rcb_refc;		/* reference count */
    u_short	   rcb_lport;		/* local port */
    short	   rcb_cmask;		/* file creation mask */
    short	   rcb_flags;		/* connection flags */
    dev_t	   rcb_rdev;		/* remote root device number */
    ino_t	   rcb_rinum;		/* remote root i-number */
    u_char	   rcb_majx;		/* remote block device # bias */
};
#define rcb_addr	rcb_rl.rl_addr
#define rcb_fport	rcb_rl.rl_fport
#define rcb_pvers	rcb_rl.rl_pvers
#define rcb_pad		rcb_rl.rl_pad


/* flag bits */
#define RFSF_LOCKED	01	/* lock in use */
#define RFSF_WANTED	02	/* lock needed for another use */
#define RFSF_ERROR	04	/* error on connection */
#define RFSF_RETRY	010	/* recoverable error on connection */
#define RFSF_ACCEPT	020	/* connection not yet accepted */
#define RFSF_TOUT	040	/* connection timed out */
#define RFSF_LREPLY	0100	/* local reply not error */
#define RFSF_ABORTING	0200	/* aborting request */
#define RFSF_EINTR	0400	/* interrupted request */

/*
 *  rfsConnectionFirst - return first connection block in queue
 *
 *  rcbqp = queue of connection blocks
 *
 *  Return: the first connection block in the queue
 */
#define rfsConnectionFirst(rcbpq)	\
    ((struct rfsConnectionBlock *)((rcbpq)->F))

/*
 *  rfsConnectionNext - advance to the next connection block in a queue 
 *
 *  rcbp = current connection block
 *
 *  Return: the next connection block in the queue
 */
#define rfsConnectionNext(rcbp)	\
    ((struct rfsConnectionBlock *)(rcbp->rcb_link.F))

/*
 *  rfsConnectionLast - test for end of connection block queue
 *
 *  rcbpq = connection block queue
 *  rcbp  = current connection block in queue
 *
 *  Return: true if the current connection block indicates the end of the
 *  queue, otherwise false.
 */
#define rfsConnectionLast(rcbpq, rcbp)	\
     ((rcbpq) == &(rcbp->rcb_link))

/*
 *  rfsEnQueueConnection - enqueue a connection block
 *
 *  rcbqp = queue to modify
 *  rcbp  = connection block pointer to enqueue
 */
#define rfsEnQueueConnection(rcbqp, rcbp) \
    enQueue(rcbqp, (struct Queue *)(rcbp)) 

/*
 *  rfsDeQueueConnection - dequeue a connection block
 *
 *  rcbqp = queue to modify
 *  rcbp  = connection block pointer to remqueue
 *
 *  Return: the dequeued connection block pointer or NULL if the queue was
 *  empty.
 */
#define rfsDeQueueConnection(rcbqp) \
    (struct rfsConnectionBlock *)deQueue(rcbqp) 

/*
 *  rfsRemQueueConnection - remqueue a connection block
 *
 *  rcbqp = queue to modify
 *  rcbp  = connection block pointer to remqueue
 */
#define rfsRemQueueConnection(rcbqp, rcbp) \
    remQueue(rcbqp, (struct Queue *)(rcbp))


/*
 *  rfsIncrCheck - increment remote connection reference count
 *
 *  rcbp = remote connection blcok for increment
 *
 *  Increment the reference count and panic on overflow back to zero.
 */

#define rfsIncrCheck(rcbp)	\
	if (++((rcbp)->rcb_refc) == 0) panic(rfsPanicMsg_Incr)
extern char *rfsPanicMsg_Incr;

/*
 *  rfsDecrCheck - decrement remote connection reference count
 *
 *  rcbp = remote connection blcok for decrement
 *
 *  Decrement the reference count and panic on underflow below zero.
 */

#define rfsDecrCheck(rcbp)	\
	if (((rcbp)->rcb_refc)-- == 0) panic(rfsPanicMsg_Decr)
extern char *rfsPanicMsg_Decr;



/*
 *  Open remote file entry
 */
struct rfsFileEntry
{
    struct rfsConnectionBlock
	       *rfe_rcbp;		/* associated remote connection block */
    u_char	rfe_desc;		/* remote descriptor index for file */ 
};



/*
 *  Parallel process table entry
 *
 *  N.B. If you add any fields to this structure, you must make appropriate
 *  updates to rfs_newproc() to replicate them for a child process and to
 *  rfs_exit() to release them (if necessary) on exit.
 */

struct rfsProcessEntry
{
    struct Queue   rpe_rcbq;		/* remote connection block queue */
    struct rfsWho *rpe_rwp;		/* remote identity */
    rfsRW_t        rpe_rw;		/* read/write mode */
    struct buf    *rpe_bufp;		/* pathname buffer */
};

extern struct rfsProcessEntry *rfsProcessTable;

#define rfsCurrentProcessEntry	(&rfsProcessTable[u.u_procp - proc])



/*
 *  Remote inode cache entry
 */

struct rfsCacheEntry
{
    struct rfsCacheEntry
	            *rce_next;		/* next entry in hash chain */
    struct in_addr   rce_addr;		/* remote IP addr */
    struct inode    *rce_ip;		/* local inode copy */
    time_t	     rce_used;		/* time last used */
    long	     rce_size;		/* size from remote inode */
    time_t	     rce_mtime;		/* modification time from remote inode */
    ino_t	     rce_ino;		/* number of remote inode */
    dev_t	     rce_dev;		/* device of remote inode */
    short	     rce_mt;		/* mount table index of inode file system */
};
extern struct rfsCacheEntry *rfsCacheTable[];

/*
 *  rfsCacheHash - map remote inode to cache entry chain
 *
 *  addr = remote IP address
 *  ino  = remote i-number
 *  dev  = remote device number
 *
 *  Return:  index into cache array corresponding to the chain
 *  of entries which will contain the sought inode (if it exists).
 */

#define rfsCacheHash(addr, ino, dev)			\
(							\
    ((unsigned)((addr)->s_addr*(ino)*(dev)))%NRFSCACHE	\
)


/*
 *  Remote inode cache parallel mount table
 */

struct rfsMountEntry
{
    long rme_frags;			/* fragments used in cache */
};
extern struct rfsMountEntry rfsMountTable[];



/*
 *  Dynamic memory free structure template.
 *
 *  This structure is used to maintain the linked list of free stuctures in a
 *  memory allocation descriptor.  All dynamically allocated structures are
 *  at least this large (sufficient to hold a link pointer).
 */

struct rfsFreeOverlay
{
    struct rfsFreeOverlay *rfo_next;
};


/*
 *  Dynamic memory structure allocation descriptor
 *
 *  One of these descriptors exists for each type of dynamically allocated
 *  structure.  It contains the structure size and a count of the number of
 *  strcutures which can be carved out of each allocated mbuf as well as a list
 *  of free structures which are available for reallocation.
 */

struct rfsFreeDescriptor
{
    struct rfsFreeOverlay
		     *rfd_head;		/* head of free structure list */
    short	      rfd_size;		/* size of a structure */
    short	      rfd_max;		/* maximum structures per mbuf */
};

/*
 *  Macro to (compile-time) initialize descriptor for a structure type
 */
#define rfsInitDescriptor(type)	\
    {NULL, roundup(sizeof(struct type),sizeof(int)), \
	   MLEN/roundup(sizeof(struct type),sizeof(int))}


/*
 *  Cover definitions for specific structure allocation routines
 */

#define rfsCacheAllocate()		\
    (struct rfsCacheEntry *)rfsAllocate(&rfsCacheDescriptor)

#define rfsCacheFree(rcep)	\
    rfsFree(&rfsCacheDescriptor, (struct rfsFreeOverlay *)(rcep))

extern struct rfsFreeDescriptor rfsCacheDescriptor;


#define rfsConnectionAllocate()		\
    (struct rfsConnectionBlock *)rfsAllocate(&rfsConnectionDescriptor)

#define rfsConnectionFree(rcbp)	\
    rfsFree(&rfsConnectionDescriptor, (struct rfsFreeOverlay *)(rcbp))

extern struct rfsFreeDescriptor rfsConnectionDescriptor;


#define rfsFileAllocate()		\
    (struct rfsFileEntry *)rfsAllocate(&rfsFileDescriptor)

#define rfsFileFree(rfep)	\
    rfsFree(&rfsFileDescriptor, (struct rfsFreeOverlay *)(rfep))

extern struct rfsFreeDescriptor rfsFileDescriptor;


#define rfsWhoAllocate()		\
    (struct rfsWho *)rfsAllocate(&rfsWhoDescriptor)

#define rfsWhoFree(rfep)	\
    rfsFree(&rfsWhoDescriptor, (struct rfsFreeOverlay *)(rfep))

extern struct rfsFreeDescriptor rfsWhoDescriptor;



/*
 *  Global variables
 */

#define RFS_SYSENT	9			/* offset to syscall #0 */
#define rfs_sysent	(&rfs_cmusysent[RFS_SYSENT])
extern struct inode *(*rfs_cmusysent[])();	/* system call dispatch table */

extern int rfsDebug;			/* debugging flags */



/*
 *  Procedure declarations
 */

extern struct inode		 *rfs_copen();
extern struct inode		 *rfs_stat1();
extern struct inode		 *rfs_sysdesccall();
extern struct inode		 *rfs_sysnamecall();

extern int		 	  rfsAbortOut();
extern struct rfsFreeOverlay	 *rfsAllocate();
extern struct rfsConnectionBlock *rfsAttach();
extern struct inode		 *rfsCache();
extern boolean_t	 	  rfsCachePurge();
extern void		 	  rfsCacheSweep();
extern struct rfsConnectionBlock *rfsCopy();
extern void		 	  rfsDetach();
extern void		 	  rfsDetachWho();
extern void		 	  rfsError();
extern void		 	  rfsFree();
extern void			  rfsFork();
extern void		 	  rfsForkDir();
extern struct rfsConnectionBlock *rfsGet();
extern struct rfsWho		 *rfsGetWho();
extern struct rfsCacheEntry	 *rfsInCache();
extern struct inode		 *rfsInodeAllocate();
extern void		 	  rfsLock();
extern struct rfsFileEntry       *rfsOpCr();
extern struct rfsConnectionBlock *rfsProcessConnection();
extern int		 	  rfsSendOut();
extern void		 	  rfsShutdown();
extern struct mbuf		 *rfsSocketName();
extern int		 	  rfsTimeOut();
extern void		 	  rfsUnAbort();
extern void		 	  rfsUnLock();
extern void		 	  rfsUnEstablish();
extern struct inode		 *rfsValidCache();
extern void		 	  rfsWaitTTY();

#endif	KERNEL
#endif	_RFS_RFS_H_
