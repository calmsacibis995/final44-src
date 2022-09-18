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
 * $Log:	rfs_init.c,v $
 * Revision 2.13  90/07/03  16:46:55  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:10:55  mrt]
 * 
 * Revision 2.12  89/07/11  13:37:58  jjc
 * 	Changed "#ifdef sun3" into "if defined(sun3) || defined(sun4)".
 * 	[89/05/06            jjc]
 * 
 * Revision 2.11  89/05/30  10:40:12  rvb
 * 	Upgrade for syscall mips table: includes ultrix (empty) vectors
 * 	and enables pioctl.
 * 	[89/05/15            af]
 * 
 * Revision 2.10  89/04/22  15:26:52  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.9  89/03/15  15:13:56  gm0w
 * 	changed include sys/rfs.h to rfs/rfs/h
 * 
 * Revision 2.8  89/02/25  14:44:53  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.7  89/02/09  04:32:20  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.6  89/01/23  22:05:20  af
 * 	Changes for I386: give the same tables as a vax
 * 	[89/01/09            rvb]
 * 	
 * 	Added hooks for Mips.
 * 	[89/01/08            af]
 * 
 * Revision 2.5  89/01/18  00:39:07  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.4  88/08/25  18:11:43  mwyoung
 * 	Removed RFS conditional entirely... this file isn't built unless
 * 	CMUCS_RFS is specified.
 * 	[88/08/23            mwyoung]
 * 	
 * 	Corrected include file references.
 * 	[88/08/23  01:18:32  mwyoung]
 * 	
 * 	Eliminate hc warning in rfs_oops().
 * 	[88/08/11  18:43:45  mwyoung]
 * 
 * Revision 2.2.2.1.1.1  88/08/23  01:15:33  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 *
 * Revision 2.3  88/08/22  21:24:59  mja
 * 	Forward exect() on the IBM-RT as execve() as suggested by Rich
 * 	Sanzi.
 * 	[88/08/20  22:43:22  mja]
 * 	
 * 	Add table entries for negative system call numbers to prevent a
 * 	crash when attempted (although none will actually work through
 * 	RFS);  collapsed conditionals.
 * 	[88/08/08  14:35:58  mja]
 * 
 * 12-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added table entry for Vice pioctl() call at its new position.
 *	[ V5.1(XF24) ]
 *
 * 18-Nov-87  Michael Jones (mbj) at Carnegie-Mellon University
 *	Added entry for VICE pioctl call to fix panic rfs.  Extracted
 *	vendor specific system calls into per-machine tables as per the
 *	corresponding change in init_sysent.
 *
 *  1-Apr-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Increase size of rfs switch to be as large as syscall switch.
 *	Added entries 151 - 175.
 *
 * 17-Mar-87  David L. Black (dlb) at Carnegie-Mellon University
 *	Enable exec for Multimax; rfs_exec now supports coff.
 *
 * 29-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	MULTIMAX: Temporarily disable exec until coff changes can be made.
 *
 * 02-Jan-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS_RFS:  Split initialization into two parts since queue
 *	headers must now be valid before the possible multi-processor
 *	newproc() set up but the root file system isn't available until
 *	after.
 *	[V1(1)]
 *
 * 19-Oct-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Enabled access(), chdir(), chmod(), chroot() and unlink() system
 *	calls.
 *	[V1(1)]
 *
 */

/*	rfs_init.c	CMU	01/20/82	*/

/*
 *  Remote file system - initialization module
 */
#include <vice.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/dir.h>
#include <sys/file.h>
#include <sys/inode.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <rfs/rfs.h>
#include <sys/namei.h>

/*
 *  Initialization for common global data structures.
 */


#ifdef	RFSDEBUG
/*
 *  Non-zero to enable debug tracing messages
 */
int rfsDebug = RFSDEBUG;
#endif	RFSDEBUG


/*
 *  Parallel process table
 *
 *  Space for this table is allocated dynamically during system startup to be
 *  as large as the standard process table.
 */
struct rfsProcessEntry *rfsProcessTable = 0;

/*
 *  Dynamic structure allocation descriptors.
 */
struct rfsFreeDescriptor rfsConnectionDescriptor = rfsInitDescriptor (rfsConnectionBlock);
struct rfsFreeDescriptor rfsCacheDescriptor      = rfsInitDescriptor (rfsCacheEntry);
struct rfsFreeDescriptor rfsFileDescriptor       = rfsInitDescriptor (rfsFileEntry);
struct rfsFreeDescriptor rfsWhoDescriptor        = rfsInitDescriptor (rfsWho);

/*
 *  Panic message strings invoked in macro definitions
 */
char *rfsPanicMsg_Incr = "rfsIncr";
char *rfsPanicMsg_Decr = "rfsDecr";
char *rfsPanicMsg_IncrWho = "rfsIncrWho";
char *rfsPanicMsg_DecrWho = "rfsDecrWho";

/*
 *  Default connection port
 */
int rfsPort = RFSPORT;


/*
 *  Remote system call table.
 *
 *  This table provides the switch from rfs_namei() or rfs_finode() into the
 *  appropriate remote file system call processing code.  Only system calls
 *  which transfer into the remote code through namei() or getinode() will
 *  appear below.  Not all calls which can potentially use namei() will appear
 *  though since some operations simply don't make sense remotely and are not
 *  enabled for remote handling (by the OKREMOTE flag in their call on
 *  namei()).
 *
 *  The routines which implement the other descriptor based remote file system
 *  calls are found in the rfsops structure.  For documentation purposes, they
 *  are flagged in the table with the pseudo routine rfs_fops which is still a
 *  panic if called through this table.
 *
 *  The remaining few which need explicit hooks in the standard system calls
 *  themselves are similarly flagged as rfs_hook which again is still a
 *  panic if called here.
 */

#define		     rfs_fops		rfs_oops
#define		     rfs_hook		rfs_oops


/*
 *  Remote file system call implementation routine mappings.
 */

#define		     rfs_access		rfs_sysnamecall
#define		     rfs_chdir		rfs_chdirec
#define		     rfs_chmod		rfs_sysnamecall
#define		     rfs_chown		rfs_sysnamecall
#define		     rfs_chroot		rfs_chdirec
extern struct inode *rfs_creat();
#define		     rfs_execv		rfs_exec
#define		     rfs_execve		rfs_exec
#define		     rfs_fchmod		rfs_sysdesccall
#define		     rfs_fchown		rfs_sysdesccall
#define		     rfs_flock		rfs_sysdesccall
#define		     rfs_ftruncate	rfs_sysdesccall
#define		     rfs_fsync		rfs_sysdesccall
#define		     rfs_link		rfs_sysnamescall
extern struct inode *rfs_lseek();
#define		     rfs_lstat		rfs_stat
#define		     rfs_mkdir		rfs_sysnamecall
#define		     rfs_mknod		rfs_sysnamecall
extern struct inode *rfs_open();
extern struct inode *rfs_ofstat();
extern struct inode *rfs_ostat();
#define		     rfs_outime		rfs_sysnamecall
extern struct inode *rfs_readlink();
#define		     rfs_rename		rfs_sysnamescall
#define		     rfs_rmdir		rfs_sysnamecall
extern struct inode *rfs_stat();
extern struct inode *rfs_symlink();
#define		     rfs_truncate	rfs_sysnamecall
#define		     rfs_unlink		rfs_sysnamecall
#define		     rfs_utimes		rfs_sysnamecall
#if	VICE
extern struct inode *rfs_einval();
#define		     rfs_pioctl		rfs_einval
#else	VICE
#define		     rfs_pioctl		rfs_oops
#endif	VICE

extern struct inode *rfs_sysdesccall();	/* common descriptor system call handler */
extern struct inode *rfs_sysnamecall();	/* common name system call handler */
extern struct inode *rfs_sysnamescall();/* common names system call handler */
extern struct inode *rfs_chdirec();	/* common chdir/chroot handler*/
extern struct inode *rfs_exec();	/* common execv/execve handler*/

extern struct inode *rfs_oops();	/* can't happen */
extern struct inode *rfs_nyi();		/* not yet implemented */


/*
 *  The dispatch table proper.
 */

struct inode *(*rfs_cmusysent[])() =
{
#if	(RFS_SYSENT-9) != 0
	RFS_SYSENT_IS_OBSOLETE,
#endif
	rfs_oops,			/*  -9 = get process modes */
	rfs_oops,			/*  -8 = set process modes */
	rfs_oops,			/*  -7 = old CMU IPC */
	rfs_oops,			/*  -6 = table lookup */
	rfs_oops,			/*  -5 = resource pause */
	rfs_nyi,			/*  -4 = extended utimes() */
	rfs_oops,			/*  -3 = old chacct */
	rfs_oops,			/*  -2 = get account ID */
	rfs_oops,			/*  -1 = set account ID */
	rfs_oops,			/*   0 = indir */
	rfs_oops,			/*   1 = exit */
	rfs_hook,			/*   2 = fork */
	rfs_fops,			/*   3 = read */
	rfs_fops,			/*   4 = write */
	rfs_open,			/*   5 = open */
	rfs_fops,			/*   6 = close */
	rfs_oops,			/*   7 = old wait */
	rfs_creat,			/*   8 = creat */
	rfs_link,			/*   9 = link */
	rfs_unlink,			/*  10 = unlink */
	rfs_execv,			/*  11 = execv */
	rfs_chdir,			/*  12 = chdir */
	rfs_oops,			/*  13 = old time */
	rfs_mknod,			/*  14 = mknod */
	rfs_chmod,			/*  15 = chmod */
	rfs_chown,			/*  16 = chown; now 3 args */
	rfs_oops,			/*  17 = old break */
	rfs_ostat,			/*  18 = old stat */
	rfs_lseek,			/*  19 = lseek */
	rfs_oops,			/*  20 = getpid */
	rfs_oops,			/*  21 = mount */
	rfs_oops,			/*  22 = umount */
	rfs_oops,			/*  23 = old setuid */
	rfs_oops,			/*  24 = getuid */
	rfs_oops,			/*  25 = old stime */
	rfs_oops,			/*  26 = ptrace */
	rfs_oops,			/*  27 = old alarm */
	rfs_ofstat,			/*  28 = old fstat */
	rfs_oops,			/*  29 = opause */
	rfs_outime,			/*  30 = old utime */
	rfs_oops,			/*  31 = was stty */
	rfs_oops,			/*  32 = was gtty */
	rfs_access,			/*  33 = access */
	rfs_oops,			/*  34 = old nice */
	rfs_oops,			/*  35 = old ftime */
	rfs_oops,			/*  36 = sync */
	rfs_oops,			/*  37 = kill */
	rfs_stat,			/*  38 = stat */
	rfs_oops,			/*  39 = old setpgrp */
	rfs_lstat,			/*  40 = lstat */
	rfs_oops,			/*  41 = dup */
	rfs_oops,			/*  42 = pipe */
	rfs_oops,			/*  43 = old times */
	rfs_oops,			/*  44 = profil */
	rfs_oops,			/*  45 = nosys */
	rfs_oops,			/*  46 = old setgid */
	rfs_oops,			/*  47 = getgid */
	rfs_oops,			/*  48 = old sig */
	rfs_oops,			/*  49 = reserved for USG */
	rfs_oops,			/*  50 = reserved for USG */
	rfs_oops,			/*  51 = turn acct off/on */
	rfs_oops,			/*  52 = old set phys addr */
	rfs_oops,			/*  53 = old lock in core */
	rfs_fops,			/*  54 = ioctl */
	rfs_oops,			/*  55 = reboot */
	rfs_oops,			/*  56 = old mpxchan */
	rfs_symlink,			/*  57 = symlink */
	rfs_readlink,			/*  58 = readlink */
	rfs_execve,			/*  59 = execve */
	rfs_oops,			/*  60 = umask */
	rfs_chroot,			/*  61 = chroot */
	rfs_hook,			/*  62 = fstat */
	rfs_oops,			/*  63 = used internally */
	rfs_oops,			/*  64 = getpagesize */
	rfs_oops,			/*  65 = mremap */
	rfs_oops,			/*  66 = vfork */
	rfs_oops,			/*  67 = old vread */
	rfs_oops,			/*  68 = old vwrite */
	rfs_oops,			/*  69 = sbrk */
	rfs_oops,			/*  70 = sstk */
	rfs_oops,			/*  71 = mmap */
	rfs_oops,			/*  72 = old vadvise */
	rfs_oops,			/*  73 = munmap */
	rfs_oops,			/*  74 = mprotect */
	rfs_oops,			/*  75 = madvise */
	rfs_oops,			/*  76 = vhangup */
	rfs_oops,			/*  77 = old vlimit */
	rfs_oops,			/*  78 = mincore */
	rfs_oops,			/*  79 = getgroups */
	rfs_oops,			/*  80 = setgroups */
	rfs_oops,			/*  81 = getpgrp */
	rfs_oops,			/*  82 = setpgrp */
	rfs_oops,			/*  83 = setitimer */
	rfs_oops,			/*  84 = wait */
	rfs_oops,			/*  85 = swapon */
	rfs_oops,			/*  86 = getitimer */
	rfs_oops,			/*  87 = gethostname */
	rfs_oops,			/*  88 = sethostname */
	rfs_oops,			/*  89 = getdtablesize */
	rfs_oops,			/*  90 = dup2 */
	rfs_oops,			/*  91 = getdopt */
	rfs_oops,			/*  92 = fcntl */
	rfs_fops,			/*  93 = select */
	rfs_oops,			/*  94 = setdopt */
	rfs_fsync,			/*  95 = fsync */
	rfs_oops,			/*  96 = setpriority */
	rfs_oops,			/*  97 = socket */
	rfs_oops,			/*  98 = connect */
	rfs_oops,			/*  99 = accept */
	rfs_oops,			/* 100 = getpriority */
	rfs_oops,			/* 101 = send */
	rfs_oops,			/* 102 = recv */
	rfs_oops,			/* 103 = old socketaddr */
	rfs_oops,			/* 104 = bind */
	rfs_oops,			/* 105 = setsockopt */
	rfs_oops,			/* 106 = listen */
	rfs_oops,			/* 107 = old vtimes */
	rfs_oops,			/* 108 = sigvec */
	rfs_oops,			/* 109 = sigblock */
	rfs_oops,			/* 110 = sigsetmask */
	rfs_oops,			/* 111 = sigpause */
	rfs_oops,			/* 112 = sigstack */
	rfs_oops,			/* 113 = recvmsg */
	rfs_oops,			/* 114 = sendmsg */
	rfs_oops,			/* 115 = vtrace */
	rfs_oops,			/* 116 = gettimeofday */
	rfs_oops,			/* 117 = getrusage */
	rfs_oops,			/* 118 = getsockopt */
	rfs_oops,			/* 119 = nosys */
	rfs_oops,			/* 120 = readv */
	rfs_oops,			/* 121 = writev */
	rfs_oops,			/* 122 = settimeofday */
	rfs_fchown,			/* 123 = fchown */
	rfs_fchmod,			/* 124 = fchmod */
	rfs_oops,			/* 125 = recvfrom */
	rfs_oops,			/* 126 = setreuid */
	rfs_oops,			/* 127 = setregid */
	rfs_rename,			/* 128 = rename */
	rfs_truncate,			/* 129 = truncate */
	rfs_ftruncate,			/* 130 = ftruncate */
	rfs_flock,			/* 131 = flock */
	rfs_oops,			/* 132 = nosys */
	rfs_oops,			/* 133 = sendto */
	rfs_oops,			/* 134 = shutdown */
	rfs_oops,			/* 135 = socketpair */
	rfs_mkdir,			/* 136 = mkdir */
	rfs_rmdir,			/* 137 = rmdir */
	rfs_utimes,			/* 138 = utimes */
	rfs_oops,			/* 139 = used internally */
	rfs_oops,			/* 140 = nosys */
	rfs_oops,			/* 141 = getpeername */
	rfs_oops,			/* 142 = gethostid */
	rfs_oops,			/* 143 = sethostid */
	rfs_oops,			/* 144 = getrlimit */
	rfs_oops,			/* 145 = setrlimit */
	rfs_oops,			/* 146 = killpg */
	rfs_oops,			/* 147 = nosys */
	rfs_oops,			/* 148 = quota */
	rfs_oops,			/* 149 = qquota */
	rfs_oops,			/* 150 = getsockname */
#ifdef	ibmrt
	rfs_execve,			/* 151 = exect */
	rfs_oops,			/* 152 */
	rfs_oops,			/* 153 */
	rfs_oops,			/* 154 = iopen */
	rfs_oops,			/* 155 = iread */
	rfs_oops,			/* 156 = iwrite */
	rfs_oops,			/* 157 = iinc */
	rfs_oops,			/* 158 = idec */
	rfs_pioctl,			/* 159 = pioctl */
	rfs_oops,			/* 160 = setpag */
	rfs_oops,			/* 161 = icreate */
	rfs_oops,			/* 162 */
	rfs_oops,			/* 163 */
	rfs_oops,			/* 164 */
	rfs_oops,			/* 165 */
	rfs_oops,			/* 166 */
	rfs_oops,			/* 167 = getfloatstate */
	rfs_oops,			/* 168 = setfloatstate */
	rfs_oops,			/* 169 */
	rfs_oops,			/* 170 */
	rfs_oops,			/* 171 */
	rfs_oops,			/* 172 */
	rfs_oops,			/* 173 */
	rfs_oops,			/* 174 */
	rfs_oops,			/* 175 */
	rfs_oops,			/* 176 */
	rfs_oops,			/* 177 */
	rfs_oops,			/* 178 */
	rfs_oops,			/* 179 */
	rfs_oops,			/* 180 */
#endif	ibmrt
#if	defined(sun3) || defined(sun4)
	rfs_oops,			/* 151 */
	rfs_oops,			/* 152 */
	rfs_oops,			/* 153 */
	rfs_oops,			/* 154 */
	rfs_oops,			/* 155 */
	rfs_oops,			/* 156 = getdirentries */
	rfs_oops,			/* 157 */
	rfs_oops,			/* 158 */
	rfs_oops,			/* 159 */
	rfs_oops,			/* 160 */
	rfs_oops,			/* 161 */
	rfs_oops,			/* 162 = getdomainname */
	rfs_oops,			/* 163 = setdomainname */
	rfs_oops,			/* 164 */
	rfs_oops,			/* 165 */
	rfs_oops,			/* 166 */
	rfs_oops,			/* 167 */
        rfs_pioctl,			/* 168 = pioctl */
        rfs_oops,			/* 169 = setpag */
        rfs_oops,			/* 170 = icreate */
        rfs_oops,			/* 171 = iopen */
        rfs_oops,			/* 172 = iread */
        rfs_oops,			/* 173 = iwrite */
        rfs_oops,			/* 174 = iinc */
        rfs_oops,			/* 175 = idec */
	rfs_oops,			/* 176 */
	rfs_oops,			/* 177 */
	rfs_oops,			/* 178 */
	rfs_oops,			/* 179 */
	rfs_oops,			/* 180 */
#endif	defined(sun3) || defined(sun4)
#if	defined(vax) || defined(i386)
        rfs_oops,			/* 151 = icreate */
        rfs_oops,			/* 152 = iopen */
        rfs_oops,			/* 153 = iread */
        rfs_oops,			/* 154 = iwrite */
        rfs_oops,			/* 155 = iinc */
        rfs_oops,			/* 156 = idec */
        rfs_pioctl,			/* 157 = pioctl */
        rfs_oops,			/* 158 = setpag */
	rfs_oops,			/* 159 */
	rfs_oops,			/* 160 */
	rfs_oops,			/* 161 */
	rfs_oops,			/* 162 */
	rfs_oops,			/* 163 */
	rfs_oops,			/* 164 */
	rfs_oops,			/* 165 */
	rfs_oops,			/* 166 */
	rfs_oops,			/* 167 */
	rfs_oops,			/* 168 */
	rfs_oops,			/* 169 */
	rfs_oops,			/* 170 */
        rfs_pioctl,			/* 171 = pioctl */
        rfs_oops,			/* 172 = setpag */
        rfs_oops,			/* 173 = icreate */
        rfs_oops,			/* 174 = iopen */
        rfs_oops,			/* 175 = iread */
        rfs_oops,			/* 176 = iwrite */
        rfs_oops,			/* 177 = iinc */
        rfs_oops,			/* 178 = idec */
	rfs_oops,			/* 179 */
	rfs_oops,			/* 180 */
#endif	defined(vax) || defined(i386)
#ifdef	balance
	rfs_oops,			/* 151 = getdirentries */
	rfs_oops,			/* 152 = tmp_ctl */
	rfs_oops,			/* 153 = universe */
	rfs_oops,			/* 154 */
	rfs_oops,			/* 155 */
	rfs_oops,			/* 156 */
	rfs_oops,			/* 157 */
	rfs_oops,			/* 158 */
	rfs_oops,			/* 159 */
	rfs_oops,			/* 160 */
	rfs_oops,			/* 161 */
	rfs_oops,			/* 162 */
	rfs_oops,			/* 163 */
	rfs_oops,			/* 164 */
	rfs_oops,			/* 165 */
	rfs_oops,			/* 166 */
	rfs_oops,			/* 167 */
	rfs_oops,			/* 168 */
	rfs_oops,			/* 169 */
	rfs_oops,			/* 170 */
	rfs_oops,			/* 171 */
	rfs_oops,			/* 172 */
	rfs_oops,			/* 173 */
	rfs_oops,			/* 174 */
	rfs_oops,			/* 175 */
	rfs_oops,			/* 176 */
	rfs_oops,			/* 177 */
	rfs_oops,			/* 178 */
	rfs_oops,			/* 179 */
	rfs_oops,			/* 180 */
#endif	balance
#ifdef	mips
	rfs_oops,			/* 151 = sysmips */
	rfs_oops,			/* 152 */
	rfs_oops,			/* 153 */
	rfs_oops,			/* 154 */
	rfs_oops,			/* 155 */
	rfs_oops,			/* 156 */
	rfs_oops,			/* 157 */
	rfs_oops,			/* 158 = nfs_svc */
	rfs_oops,			/* 159 = getdirentries */
	rfs_oops,			/* 160 = statfs */
	rfs_oops,			/* 161 = fstatfs */
	rfs_oops,			/* 162 = unmount */
	rfs_oops,			/* 163 = async_daemon */
	rfs_oops,			/* 164 = nfs_getfh */
	rfs_oops,			/* 165 = getdomainname */
	rfs_oops,			/* 166 = setdomainname */
	rfs_oops,			/* 167 */
	rfs_oops,			/* 168 = quotactl */
	rfs_oops,			/* 169 = exportfs */
	rfs_oops,			/* 170 = mount */
	rfs_oops,			/* 171 */
	rfs_oops,			/* 172 */
	rfs_oops,			/* 173 */
	rfs_oops,			/* 174 */
	rfs_oops,			/* 175 */
	rfs_oops,			/* 176 */
	rfs_oops,			/* 177 */
	rfs_oops,			/* 178 */
	rfs_oops,			/* 179 */
	rfs_oops,			/* 180 */
	rfs_oops,			/* 181 */
	rfs_oops,			/* 182 */
	rfs_oops,			/* 183 */
	rfs_oops,			/* 184 */
	rfs_oops,			/* 185 */
	rfs_oops,			/* 186 */
	rfs_oops,			/* 187 */
	rfs_oops,			/* 188 */
	rfs_oops,			/* 189 */
	rfs_oops,			/* 190 = iopen */
	rfs_oops,			/* 191 = iread */
	rfs_oops,			/* 192 = iwrite */
	rfs_oops,			/* 193 = iinc */
	rfs_oops,			/* 194 = idec */
	rfs_pioctl,			/* 195 = pioctl */
	rfs_oops,			/* 196 = setpag */
	rfs_oops,			/* 197 = icreate */
	rfs_oops,			/* 198 = afs_call */
	rfs_oops,			/* 199 */
	rfs_oops,			/* 200 */
	rfs_oops,			/* 201 */
	rfs_oops,			/* 202 */
	rfs_oops,			/* 203 */
	rfs_oops,			/* 204 */
	rfs_oops,			/* 205 */
	rfs_oops,			/* 206 */
	rfs_oops,			/* 207 */
	rfs_oops,			/* 208 */
	rfs_oops,			/* 209 */
	rfs_oops,			/* 210 */
	rfs_oops,			/* 211 */
	rfs_oops,			/* 212 */
	rfs_oops,			/* 213 */
	rfs_oops,			/* 214 */
	rfs_oops,			/* 215 */
	rfs_oops,			/* 216 */
	rfs_oops,			/* 217 */
	rfs_oops,			/* 218 */
	rfs_oops,			/* 219 */
	rfs_oops,			/* 220 */
	rfs_oops,			/* 221 */
	rfs_oops,			/* 222 */
	rfs_oops,			/* 223 */
	rfs_oops,			/* 224 */
	rfs_oops,			/* 225 */
	rfs_oops,			/* 226 */
	rfs_oops,			/* 227 */
	rfs_oops,			/* 228 */
	rfs_oops,			/* 229 */
	rfs_oops,			/* 230 */
	rfs_oops,			/* 231 */
	rfs_oops,			/* 232 */
	rfs_oops,			/* 233 */
	rfs_oops,			/* 234 */
	rfs_oops,			/* 235 */
	rfs_oops,			/* 236 */
	rfs_oops,			/* 237 */
	rfs_oops,			/* 238 */
	rfs_oops,			/* 239 */
	rfs_oops,			/* 240 */
	rfs_oops,			/* 241 */
	rfs_oops,			/* 242 */
	rfs_oops,			/* 243 */
	rfs_oops,			/* 244 */
	rfs_oops,			/* 245 */
	rfs_oops,			/* 246 */
	rfs_oops,			/* 247 */
	rfs_oops,			/* 248 */
	rfs_oops,			/* 249 */
	rfs_oops,			/* 250 */
	rfs_oops,			/* 251 */
	rfs_oops,			/* 252 */
	rfs_oops,			/* 253 */
	rfs_oops,			/* 254 */
	rfs_oops,			/* 255 */
	rfs_oops,			/* 256 = getsysinfo */
	rfs_oops,			/* 257 = setsysinfo */
#endif	mips
#if	!defined(vax) && !defined(ibmrt) && !defined(sun3) && !defined(balance) && !defined(i386) && !defined(mips) && !defined(sun4)
	rfs_oops,			/* 151 */
	rfs_oops,			/* 152 */
	rfs_oops,			/* 153 */
	rfs_oops,			/* 154 */
	rfs_oops,			/* 155 */
	rfs_oops,			/* 156 */
	rfs_oops,			/* 157 */
	rfs_oops,			/* 158 */
	rfs_oops,			/* 159 */
	rfs_oops,			/* 160 */
	rfs_oops,			/* 161 */
	rfs_oops,			/* 162 */
	rfs_oops,			/* 163 */
	rfs_oops,			/* 164 */
	rfs_oops,			/* 165 */
	rfs_oops,			/* 166 */
	rfs_oops,			/* 167 */
	rfs_oops,			/* 168 */
	rfs_oops,			/* 169 */
	rfs_oops,			/* 170 */
	rfs_oops,			/* 171 */
	rfs_oops,			/* 172 */
	rfs_oops,			/* 173 */
	rfs_oops,			/* 174 */
	rfs_oops,			/* 175 */
	rfs_oops,			/* 176 */
	rfs_oops,			/* 177 */
	rfs_oops,			/* 178 */
	rfs_oops,			/* 179 */
	rfs_oops,			/* 180 */
#endif	!defined(vax) && !defined(ibmrt) && !defined(sun3) && !defined(balance) && !defined(i386) && !defined(mips) && !defined(sun4)
};



/*
 *  rfs_oops - catch an unexpected remote file system call dispatch
 *
 *  Indicate the system call number which invoked the error and panic().
 */

struct inode *
rfs_oops()
{
    printf("code=%d ", u.u_rfscode);
    panic("rfs");
#ifdef	__HC__
	return((struct inode *) 0);
#endif	__HC__
    /* NOTREACHED */
}



/*
 *  rfs_init - data structure initialization
 *
 *  Initialize the parallel process table remote connection block queue
 *  headers.
 */

rfs_init()
{
    register struct rfsProcessEntry *rpep;

    for (rpep=rfsProcessTable; rpep < &rfsProcessTable[nproc]; rpep++)
	initQueue(&rpep->rpe_rcbq);
}



/*
 *  rfs_initroot - local root directory initialization
 *
 *  Look for a local root directory (which will have all the remote file system
 *  link inodes installed above it).  If an appropriate local root directory is
 *  found, change the current and root directory pointers for this process to
 *  use it so that all future references above the root (e.g. /../<system-
 *  name/*) will be able to find the remote links.  If no appropriate directory
 *  is found, leave the current and root directory pointers at the physical
 *  root of the file system.
 *
 *  This routine is called very earlier in the system initialization
 *  procedure by process 0.
 *
 *  N.B.  It is usually prudent to always have symbolic link files for at least
 *  "/etc", "/bin" and "/dev" (and all other top level directories if possible)
 *  installed on the physical root.  This aids in switching between operating
 *  systems with and without support for the remote file system by permitting
 *  single-user bootstraps of either version of an operating system.  These
 *  symbolic links should also be relative to the physical root directory
 *  itself so that such a reorganized file system may be mounted when it is not
 *  the root without causing any nasty surprises.
 */

char *rfs_localroot[] = {"/RFS/.LOCALROOT", "/REM/.LOCALROOT", 0};
struct inode *rfs_rdir = NULL;

rfs_initroot()
{
    char **dirpp;

    for (dirpp=rfs_localroot; *dirpp; dirpp++)
    {
	struct inode *ip;

	LOOKUP_ROOT_NAME(*dirpp, ip);
	if (ip != NULL)
	{
	    if (INODE_TYPE(ip,DIR))
	    {
		LOCK_INODE(u.u_cdir);
		FINISH_WITH_INODE(u.u_cdir);
		INCR_INODE(ip);
		u.u_cdir = ip;
		u.u_rdir = ip;
		rfs_rdir = ip;
		UNLOCK_INODE(ip);
		return;
	    }
	    else
	    {
		printf("WARNING: %s is not a directory\n", *dirpp);
		FINISH_WITH_INODE(ip);
	    }
	}
    }
    printf("WARNING: no remote file system (missing %s)\n", rfs_localroot[0]);
}
