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
 * $Log:	rfs_syscalls.c,v $
 * Revision 2.15  89/08/08  21:50:15  jsb
 * 	Fix execve to allow both SYSV_COFF and BSD_A_OUT, simultaneously.
 * 	[89/07/31            rvb]
 * 
 * Revision 2.14  89/05/30  10:40:32  rvb
 * 	De-conditionalized a mips clause.
 * 	[89/05/16            af]
 * 
 * Revision 2.13  89/04/22  15:27:27  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.12  89/03/15  15:15:12  gm0w
 * 	changed include sys/rfs.h to rfs/rfs/h
 * 
 * Revision 2.11  89/03/09  19:30:20  rpd
 * 	More cleanup.
 * 
 * Revision 2.10  89/02/25  14:45:24  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.9  89/02/09  04:32:41  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.8  89/01/23  22:05:48  af
 * 	Added Mips, same case as the Encore Multimax.  Also, fixed the
 * 	case of 407 images on both.
 * 	[89/01/11            af]
 * 
 * Revision 2.7  89/01/18  00:40:45  jsb
 * 	Vnode support.
 * 	[89/01/16            jsb]
 * 
 * Revision 2.6  88/08/24  01:27:13  mwyoung
 * 	Removed RFS conditional entirely... this file isn't built unless
 * 	CMUCS_RFS is specified.
 * 	[88/08/23            mwyoung]
 * 	
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 * Revision 2.5  88/08/22  21:25:35  mja
 * 	Collapse conditionals;  change rfs_nyi() to return EOPNOTSUPP
 * 	rather than EACCES.
 * 	[88/08/09  09:50:39  mja]
 * 
 * Revision 2.4  88/07/15  15:32:33  mja
 * Fix rfs_readlink() to properly reflect an error code returned by
 * the remote call.
 * 
 *  1-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Update rfs_exec to sysV header file changes for multimax.  Use
 *	cpp symbol for multimax.
 *
 * 18-Nov-87  Michael Jones (mbj) at Carnegie-Mellon University
 *	Added rfs_einval routine to return EINVAL (for VICE pioctl
 *	call).
 *
 * 18-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 20-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	Removed Multimax compiler bug workaround.  Conversion of
 *	cpu_number() to a macro causes bug not to be tickled.
 *
 * 27-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	Multimax must rfsLseek file to position for second header read.
 *
 * 23-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed to make correct remote execution check for shell scripts
 *	with the second character '!' rather than null.
 *	[ V5.1(F8) ]
 *
 * 17-Mar-87  David L. Black (dlb) at Carnegie-Mellon University
 *	Support exec of coff/coff2 format files for Multimax.
 *
 * 09-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fix bug in rfs_newproc() which neglected to deal with a network
 *	error during a fork operation that could cause the current
 *	connection block to be removed from the list while the the
 *	queue was being traversed.
 *	[ V5.1(F6) ]
 *
 * 05-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed rfs_readlink() and rfs_symlink() to use new rfsUIOSend()
 *	and rfsUIOReceive() routines for all socket I/O.
 *	[ V5.1(F5) ]
 *
 * 06-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Updated rfs_stat1() to poll the remote system for the device
 *	and i-number of its root on the first call so that the the
 *	device and i-number of the local remote inode pointer can be
 *	subsituted for it in any stat structures that are detected to
 *	refer to the remote root (this makes "pwd" work and shouldn't
 *	have any other adverse consequences);  modified
 *	rfs_newproc() to avoid passing the process pathname buffer to
 *	any child and fixed bug which neglected to preserve control
 *	mode there;  modified rfs_exit() to release process pathname
 *	buffer; fixed rfs_sysnamescall() not to take the wrong EXDEV
 *	exit path (corrupting the namei buffer chain) when only the
 *	second name is detected to be remote - fix courtesy of Jay
 *	Kistler.
 *	[ V5.1(F2) ]
 *
 * 11-Dec-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified rfs_stat1() to unpad stat structure sent by server
 *	for the Sun.
 *
 * 31-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Workaround for Multimax compiler bug.
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
 * 20-Jan-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created.
 *
 */

/*	rfs_syscalls.c	CMU	82/01/20	*/

/*
 *  Remote file system - non-file descriptor based system call module
 */

#include <vice.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/dir.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/inode.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/namei.h>
#include <sys/reboot.h>
#include <rfs/rfs.h>
#include <sys/exec.h>

#include <machine/reg.h>

#undef	namei
#define namei	rnamei

#include <sysv_coff.h>
#include <bsd_a_out.h>
#if	!SYSV_COFF && !BSD_A_OUT
;YOU WILL BE SORRY;
#endif	!SYSV_COFF && !BSD_A_OUT

#if	SYSV_COFF
#include <sysV/aouthdr.h>
#include <sysV/filehdr.h>
#endif	SYSV_COFF

/*
 *  rfs_namei - remote name handler
 *
 *  ip = remote host inode link (locked)
 *	(or in mach_nfs version, its vnode is held)
 *
 *  Attach to the appropriate remote connection for the specified inode
 *  and dispatch into the proper remote system call handler routine.
 *
 *  This routine is invoked by namei() whenever a remote link inode is
 *  encountered during a pathname lookup.  The remainder of the pathname
 *  (stored in a system buffer) is supplied in u.u_dirp so that it can be
 *  passed to the remote systenm for interpretation there.
 *
 *  Return: the inode to resume namei() processing with or NULL with u.u_error
 *  set to ERFSREMOTE if the call has been completed remotely.
 */

struct inode *
rfs_namei(ip, nip)
    struct inode *ip;
    struct nameidata *nip;
{
    register struct rfsConnectionBlock *rcbp;
    struct inode *rip = NULL;

    rfs_printf3(RFSD_S_TRACEIN, "<Nami %s(i=%X)\n", syscallnames[u.u_rfscode], ip);
    if (rcbp=rfsAttach(ip))
    {
	rip = (*(rfs_sysent[u.u_rfscode]))(rcbp, nip);

	if (u.u_error == 0 && rip == NULL)
	    u.u_error = ERFSREMOTE;

	if (rcbp->rcb_flags&RFSF_ERROR)
	    rfsUnEstablish(rcbp);

	rfsDetach(rcbp);
    }
    rfs_printf3(RFSD_S_TRACEOUT, ">Nami i=%X(%d)\n", rip, u.u_error);
    return(rip);
}




/*
 *  rfs_nyi - common processing for as yet unimplemented calls
 *
 *  Return: NULL (always) with u.u_error set to abort the system call with an
 *  operation not supported error.
 */

struct inode *
rfs_nyi()
{
    u.u_error = EOPNOTSUPP;
    return(NULL);
}
#if	VICE


/*
 *  rfs_einval - used for calls like pioctl which return EINVAL for RFS files.
 *
 *  Return: NULL (always) with u.u_error set to abort the system call with an
 *  invalid argument error.
 */

struct inode *
rfs_einval()
{
    u.u_error = EINVAL;
    return(NULL);
}
#endif	VICE


/*
 *  rfs_boot - clean up before reboot
 *
 *  paniced = panic() flag passwd to boot()
 *  howto   = parameter passed to boot()
 *
 *  Zero out all passwords stored in any remote connection blocks before we go
 *  down.  If we didn't panic and it is okay to do a sync(), purge all entries
 *  from the local cache to save FSCK some work (and output) and perhaps speed
 *  the bootstrap process.
 */

void
rfs_boot(paniced, howto)
    int paniced;
    int howto;
{
    register struct rfsProcessEntry *rpep;

    for (rpep=rfsProcessTable; rpep < &rfsProcessTable[nproc]; rpep++)
    {
	register struct rfsConnectionQueue *rcbqp = &(rpep->rpe_rcbq);
	register struct rfsConnectionBlock *rcbp;

	for (rcbp = rfsConnectionFirst(rcbqp);
	     !rfsConnectionLast(rcbqp, rcbp);
	     rcbp = rfsConnectionNext(rcbp))
	{
/*
	    if (rcbp->rcb_pswd[0])
		bzero(rcbp->rcb_pswd, sizeof(rcbp->rcb_pswd));
 */
	}
    }

    if (paniced != RB_PANIC && (howto&RB_NOSYNC) == 0)
	rfsCacheSweep(TRUE);
}



/*
 *  rfs_exit - exit() system call hook
 *
 *  Track down all remote connection blocks for this process and release them.
 *  Release any remote identity record for the process.
 */

rfs_exit()
{
    register struct rfsProcessEntry *rpep = rfsCurrentProcessEntry;
    register struct rfsConnectionQueue *rcbqp = &(rpep->rpe_rcbq);
    register struct rfsConnectionBlock *rcbp;

    if (rpep->rpe_bufp)
	brelse(rpep->rpe_bufp);
    while (rcbp = rfsDeQueueConnection(rcbqp))
	rfsDetach(rcbp);
    if (rpep->rpe_rwp)
    {
	rfsDetachWho(rpep->rpe_rwp);
	rpep->rpe_rwp = NULL;
    }
}



/*
 *  rfs_stat - remote stat()/lstat() call
 *
 *  rcbp = remote connection block
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 */

struct inode *
rfs_stat(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    register struct a {
	    char	*fname;
	    struct stat *ub;
    } *uap = (struct a *)u.u_ap;

    return(rfs_stat1(rcbp, nip, 0, uap->ub, u.u_rfscode, 0));
}



/*
 *  rfs_ostat - remote old stat() call
 *
 *  rcbp = remote connection block
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 */

struct inode *
rfs_ostat(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    register struct a {
	    char	*fname;
	    struct stat *ub;
    } *uap = (struct a *)u.u_ap;

    return(rfs_stat1(rcbp, nip, 0, uap->ub, RFST_OSTAT, sizeof(struct stat)-32));
}



/*
 *  rfs_stat1 - common code for stat/lstat/fstat and old friends
 *
 *  rcbp = remote connection block
 *  stp  = user stat buffer address
 *  type = message type to send
 *  size = adjustment to chop from buffer for old versions of calls
 *
 *  Perform the appropriate remote status operation and record the returned
 *  status information in the supplied buffer.
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 */

struct inode *
rfs_stat1(rcbp, nip, desc, stp, type, size)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
    u_char desc;
    register struct stat *stp;
    unsigned size;
{
    struct rfsMsg rmsg;
    register int len;
    int error;
#ifdef	sun
    register struct padded_stat	*padstp;
#endif	sun

    if (rcbp->rcb_rdev == NODEV && (type&RFST_KERNEL) == 0)
    {
	struct nameidata ni;
	struct stat st;

	ni.ni_dirp = "/";
        ni.ni_segflg = UIO_SYSSPACE;
        rfs_stat1(rcbp, &ni, 0, &st, RFST_NSTAT|RFST_KERNEL, 0);
	if (u.u_error)
	    return(NULL);
	rcbp->rcb_rinum = st.st_ino;
	rcbp->rcb_rdev  = st.st_dev;
    }
    rmsg.rmsg_A_code = type&~RFST_KERNEL;
    rmsg.rmsg_A_desc = desc;
    rmsg.rmsg_A_ul_param = 0;
    if (rmsg.rmsg_A_code != RFST_OFSTAT && rmsg.rmsg_A_code != RFST_NFSTAT)
    {
	len = rfsNameLength(nip);
	if (len < 0)
	    return(NULL);
	rmsg.rmsg_N_len = len;
    }
    else
    {
	*ni_nbpp(&u.u_nd) = 0;
	rmsg.rmsg_N_len = 0;
    }
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, sizeof(rmsg.rmsg_header)))
	goto fail;
    if (rmsg.rmsg_A_code != RFST_OFSTAT && rmsg.rmsg_A_code != RFST_NFSTAT)
    {
	error = rfsSendString(rcbp, nip->ni_dirp, rmsg.rmsg_N_len);
	if (error)
	    goto fail;
    }
    if (error = rfsReceive(rcbp, &rmsg, 
		sizeof(rmsg.rmsg_header)+sizeof(rmsg.rmsg_N_stat)-size, (int)rmsg.rmsg_A_code))
	goto fail;
    rfsUnLock(rcbp);
    if (u.u_error = rmsg.rmsg_errno)
	return(NULL);
    if (type&RFST_KERNEL)
    {
#ifdef	sun
	/*
	 *	Copy everything out of padded stat structure except the
	 *	padding
	 */
	if (stp != NULL){
		padstp = &rmsg.rmsg_N_stat;
		stp->st_dev = padstp->st_dev;
		bcopy((caddr_t)(&padstp->st_ino), (caddr_t)(&stp->st_ino),
			(caddr_t)(&padstp->st_shortpad2)
			- (caddr_t)(&padstp->st_ino));
		bcopy((caddr_t)(&padstp->st_size), (caddr_t)(&stp->st_size),
			(caddr_t)stp + sizeof(struct stat)
			 - (caddr_t)(&stp->st_size));
	}
#else	sun
	bcopy((caddr_t)&(rmsg.rmsg_N_stat), (caddr_t)stp, sizeof(rmsg.rmsg_N_stat)-size);
#endif	sun
    }
    else
    {
	/*
	 *  Attempt to prevent remote files from appearing to be on the same
	 *  file system as any local files or other remote files.  There isn't
	 *  much we can do about the inode number since application programs
	 *  may depend on the actual number (e.g. when reading directories).
	 *  No application program should care about the major devide number
	 *  (other than whether or not it exactly matches another one), though.
	 *  The calculation below guarantees that no remote block device number
	 *  will match any local block device number.  It can potentially
	 *  result in the same block device number for different remote
	 *  systems, but we'll worry about that later.  At best we can have
	 *  (256 - nblkdev) such systems, anyway.
	 */
	if (rmsg.rmsg_N_stat.st_dev == rcbp->rcb_rdev &&
	    rmsg.rmsg_N_stat.st_ino == rcbp->rcb_rinum)
	{
	    rmsg.rmsg_N_stat.st_dev = rcbp->rcb_ip->i_dev;
	    rmsg.rmsg_N_stat.st_ino = rcbp->rcb_ip->i_number;
	}
	else
	{
	    rmsg.rmsg_N_stat.st_dev = makedev
				 (
				   major(rmsg.rmsg_N_stat.st_dev)%nblkdev
				   +
				   rcbp->rcb_majx
				 ,
				   minor(rmsg.rmsg_N_stat.st_dev)
				 );
	}
#ifdef	sun
	/*
	 *	Copy everything out of padded stat structure except the
	 *	padding
	 */
	padstp = &rmsg.rmsg_N_stat;
	u.u_error = copyout((caddr_t)(&padstp->st_dev),
				(caddr_t)(&stp->st_dev),
				sizeof(stp->st_dev));
	if (u.u_error != 0)
		return(NULL);
	u.u_error = copyout((caddr_t)(&padstp->st_ino),
				(caddr_t)(&stp->st_ino),
				(caddr_t)(&padstp->st_shortpad2)
				- (caddr_t)(&padstp->st_ino));
	if (u.u_error != 0)
		return(NULL);
	u.u_error = copyout((caddr_t)(&padstp->st_size),
				(caddr_t)(&stp->st_size),
				(caddr_t)stp + sizeof(struct stat)
				- (caddr_t)(&stp->st_size));
#else	sun
	u.u_error = copyout((caddr_t)&(rmsg.rmsg_N_stat), (caddr_t)stp, sizeof(rmsg.rmsg_N_stat)-size);
#endif	sun
    }
    return(NULL);

fail:
    rfsError(rcbp);
    u.u_error = error;
    return(NULL);
}



/*
 *  rfs_chdirec - change to remote current/root directory
 *
 *  rcbp = remote connection
 *
 *  Perform the remote call and if it succeeeds adjust our appropriate local
 *  directory pointer to indicate that it is now remote.
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 */

struct inode *
rfs_chdirec(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    register struct inode **ipp;
    int flag;

    (void) rfs_sysnamecall(rcbp, nip);
    if (u.u_error == 0)
    {
	LOCK_INODE(rcbp->rcb_ip);
	INCR_INODE(rcbp->rcb_ip);
	UNLOCK_INODE(rcbp->rcb_ip);
	switch (u.u_rfscode)
	{
	    case RFST_CHDIR:
		flag = URFS_CDIR;
		ipp = &u.u_cdir;
		break;
	    case RFST_CHROOT:
		flag = URFS_RDIR;
		ipp = &u.u_rdir;
		break;
	    default:
		panic("rfs_chdirec");
	}
	if (*ipp)
		RELEASE_INODE(*ipp);
	*ipp = rcbp->rcb_ip;
	u.u_rfs |= flag;
    }
    return(NULL);
}



/*
 *  rfs_exec - remote execv()/execve() call handler
 *
 *  rcbp - remote connection block
 *
 *  Return: the local inode from the cache to be executed or NULL with
 *  u.u_error set as appropriate.
 */

struct inode *
rfs_exec(rcbp, nip)
    struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    register struct inode *ip = NULL;
    register struct rfsFileEntry *rfep = NULL;
    register struct rfsCacheEntry *rcep;
    register char *cp;
    char *sp;
    struct stat st;
    struct uio uio;
    struct iovec iov;
    extern schar();
    int temp;
#define SHSIZE	32
	union {
		char	ex_shell[SHSIZE]; /* #! and name of interpreter */
#if	SYSV_COFF
		/* 
		 * Coff fileheader structures.
		 */
		struct {
			struct filehdr fhdr;
			struct aouthdr ohdr;
#define ahdr exdata.coff.ohdr
		} coff;
		struct {
			short	magic;
		} coff_hdr;
#endif	SYSV_COFF
#if	BSD_A_OUT
		struct	exec ex_exec;
#endif	BSD_A_OUT
	} exdata;
#if	SYSV_COFF
	int	aouthdr_offset;
#endif	SYSV_COFF

    /*
     *  Check mode of remote file to verify that it can be executed.
     *  The RFST_KERNEL bit indicates (for now) that the target buffer
     *  is in kernel rather than user address space.
     */
    rfs_stat1(rcbp, nip, 0, &st, RFST_NSTAT|RFST_KERNEL, 0);
    if (u.u_error)
	return(NULL);
    if (
	 (st.st_mode&IFMT) != IFREG
         ||
         (st.st_mode&(IEXEC|(IEXEC>>3)|(IEXEC>>6))) == 0
       )
    {
	u.u_error = EACCES;
	return(NULL);
    }

    /*
     *  If we don't currently have this file recorded in the local execution
     *  cache, we must read the first block to verify the execution header.  If
     *  we already have a cached copy, this isn't necessary since the check was
     *  already made at that point.  Should we happen to find a local cache
     *  entry (either valid or invalid), the local inode will remain locked for
     *  the duration of this call so as to help prevent race conditions when
     *  interrogating the cache.  If we exit prematurely, the cached inode is
     *  unlocked during cleanup (either at out1: or in remCache()), otherwise
     *  it is passed locked back to execv() as required.
     */
    if
    (
      (rcep=rfsInCache(&rcbp->rcb_rl.rl_addr, &st, &temp)) == NULL
      ||
      (ip=rfsValidCache(rcep, &st)) == NULL
    )
    {
	/*
	 *  Open the target execution file in the process.
	 */
	rfep = rfsOpCr(rcbp, nip, RFST_OPEN, 0, 0);
	if (rfep == NULL)
	    goto out1;

	iov.iov_base = (caddr_t)&exdata;
	iov.iov_len  = sizeof(exdata);
	uio.uio_resid  = sizeof(exdata);
	uio.uio_offset = 0;
	uio.uio_iovcnt = 1;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_iov    = &iov;
	u.u_error = rfsRdWr(rfep, &uio, RFST_READ);
	if (u.u_error)
	    goto out1;
	/*
	 *  Do essentially the same consistency checks that execv() would do to
	 *  verify that the file can probably be executed.  We do this here as
	 *  an optimization to avoid copying a file which cannot be executed.
	 */
#ifndef	lint
	if (uio.uio_resid > 0 && exdata.ex_shell[0] != '#')
	{
		u.u_error = ENOEXEC;
		goto out1;
	}
#endif	lint
#if	BSD_A_OUT
	/*
	 * Read in first few bytes of file for segment sizes, magic number:
	 *	407 = plain executable
	 *	410 = RO text
	 *	413 = demand paged RO text
	 * Also an ASCII line beginning with #! is
	 * the file name of a ``shell'' and arguments may be prepended
	 * to the argument list if given here.
	 *
	 * SHELL NAMES ARE LIMITED IN LENGTH.
	 *
	 * ONLY ONE ARGUMENT MAY BE PASSED TO THE SHELL FROM
	 * THE ASCII LINE.
	 */
	if (exdata.ex_exec.a_magic == 0413 ||
	    exdata.ex_exec.a_magic == 0410) {
		if (exdata.ex_exec.a_text == 0) {
			u.u_error = ENOEXEC;
			goto out1;
		}
		goto gotbsd;
	} else
	if (exdata.ex_exec.a_magic == 0407) {
		goto gotbsd;
	} else
#ifdef	balance
	if (exdata.ex_exec.a_magic == 0x10ea) {				/* ZMAGIC: 0@0 */
						/* no XMAGIC yet */
		exdata.ex_exec.a_magic = 0413;	/* make other code easier */
		if (exdata.ex_exec.a_text == 0) {
			u.u_error = ENOEXEC;
			goto bad;
		}
		goto gotbsd;
	} else
#endif	balance
#endif	BSD_A_OUT
#if	SYSV_COFF
#ifdef	i386
	if (exdata.coff_hdr.magic == I386MAGIC) {
		aouthdr_offset = sizeof(struct filehdr);
		goto gotcoff;
	} else
#endif	i386
#ifdef	multimax
	if (exdata.coff_hdr.magic == N16WRMAGIC ||
	    exdata.coff_hdr.magic == N16ROMAGIC) {
		aouthdr_offset = N16FILHSZ;
		goto gotcoff;
	} else if (exdata.coff_hdr.magic == NS32GMAGIC ||
		   exdata.coff_hdr.magic == NS32SMAGIC) {
		aouthdr_offset = FILHSZ;
		goto gotcoff;
	} else
#endif	multimax
#ifdef	mips
	if (exdata.coff_hdr.magic == MIPSMAGIC) {
		aouthdr_offset = FILHSZ;
		goto gotcoff;
	} else
#endif	mips
#endif	SYSV_COFF
	{
		if (exdata.ex_shell[0] != '#' || exdata.ex_shell[1] != '!')
		{
		    u.u_error = ENOEXEC;
		    goto out1;
		}
		for (cp = &exdata.ex_shell[2];
		     cp < &exdata.ex_shell[SHSIZE];
		     cp++)
		{
		    if (*cp == '\n')
			goto okshell;
		}
		u.u_error = ENOEXEC;
		goto out1;
	}
#if	SYSV_COFF
gotcoff:
	/*
	 *	Now read in a.out header to really do checks.  Must first
	 *	seek the file to the correct offset.
	 */
	u.u_error = rfsLseek(rfep, (off_t)aouthdr_offset, 0, &uio.uio_offset);
	if (u.u_error)
	    goto out1;

	iov.iov_base = (caddr_t)&ahdr;
	iov.iov_len  = sizeof(struct aouthdr);
	uio.uio_resid  = sizeof(struct aouthdr);
	uio.uio_offset = 0;
	uio.uio_iovcnt = 1;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_iov    = &iov;
	u.u_error = rfsRdWr(rfep, &uio, RFST_READ);
	if (u.u_error)
	    goto out1;

#ifdef	mips
	/*
	 * check for unaligned entry point
	 */
	if (ahdr.entry & (sizeof(int)-1)) {
		u.u_error = ENOEXEC;
		goto out1;
	}
#endif	mips
	switch (ahdr.magic) {
		case 0407:
			break;
		case 0410:
		case 0413:
			if (ahdr.tsize == 0) {
				u.u_error = ENOEXEC;
				goto out1;
			}
			break;

		default:
			u.u_error = ENOEXEC;
			goto out1;
	}
#ifdef mips
	/*
	 * Enforce (artificial) addressability limit: this covers
	 * a chip bug.
	 */
	if ((ahdr.text_start < VM_MIN_ADDRESS) || 
	      (ahdr.data_start < VM_MIN_ADDRESS)) {
		u.u_error = ENOEXEC;
		goto out1;
	}
#endif	mips
#endif	SYSV_COFF
gotbsd:
okshell:
	/*
	 *  Rewind the open remote file and add it to the cache.
	 */
	u.u_error = rfsLseek(rfep, (off_t)0, 0, &uio.uio_offset);
	if (u.u_error)
	    goto out1;
	ip = rfsCache(rcep, rfep, &st, st.st_size);	/* XXX */
    }
    /*
     *  Track down trailing pathname component of remote file name and save it
     *  in u.u_dent so that it will be available for setting u.u_comm when we
     *  get to that point.
     */
    cp = u.u_nd.ni_dirp;
    for (sp=cp; *cp; cp++)
	if (*cp == '/')
	    sp = cp;
    if (*sp == '/')
	sp++;
    u.u_nd.ni_dent.d_namlen = cp-sp;
    bcopy(sp, (caddr_t)u.u_nd.ni_dent.d_name, (unsigned)(u.u_nd.ni_dent.d_namlen + 1));

out:
    if (rfep)
	rfsFileFree(rfep);
    if (ip) {
	INCR_INODE(ip);
    }
    return(ip);

out1:
    if (rcep)
	UNLOCK_INODE(rcep->rce_ip);
    goto out;
}



/*
 *  rfs_readlink - perform remote readlink operation
 *
 *  rcbp = remote connection block
 *
 *  Send a READLINK message and process the reply.
 *
 *  Return: 0 on success or an error number as appropriate.
 */

struct inode *
rfs_readlink(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    struct rfsMsg rmsg;
    int len;
    int error;
    register struct a
    {
	char   *name;
	char   *buf;
	int	count;
    } *uap = (struct a *)u.u_ap;
    struct uio uio;
    struct iovec iov;

    rmsg.rmsg_N_code = RFST_READLINK;
    rmsg.rmsg_N_l_param = uap->count;
    len = rfsNameLength(nip);
    if (len < 0)
	return(NULL);
    rmsg.rmsg_N_len = len;
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, sizeof (rmsg.rmsg_header)))
	goto fail;
    if (error = rfsSendString(rcbp, nip->ni_dirp, rmsg.rmsg_M_len))
	goto fail;
    if (error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), RFST_READLINK))
	goto fail;
    if (rmsg.rmsg_errno)
    {
        error = rmsg.rmsg_errno;
	rfsUnLock(rcbp);
	goto out;
    }
    iov.iov_base = uap->buf;
    iov.iov_len = uap->count;
    uio.uio_iov = &iov;
    uio.uio_iovcnt = 1;
    uio.uio_resid = uap->count;
    uio.uio_segflg = UIO_USERSPACE;
    while (rmsg.rmsg_rval)
    {
	unsigned ucount;

	ucount = uio.uio_resid;
	error = rfsUIOReceive(rcbp, &uio);
	if (error)
	    break;
	rmsg.rmsg_rval -= ucount-uio.uio_resid;
    }
    rfsUnLock(rcbp);
    if (error == 0)
	u.u_r.r_val1 = uap->count-uio.uio_resid;

out:
    u.u_error = error;
    return(NULL);

fail:
    rfsError(rcbp);
    goto out;
}



/*
 *  rfs_symlink - perform remote symlink operation
 *
 *  rcbp = remote connection block
 *
 *  Send a SYMLINK message.
 *
 *  Return: 0 on success or an error number as appropriate.
 */

struct inode *
rfs_symlink(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    register char *cp;
    struct rfsMsg rmsg;
    int len;
    int error;
    register struct a
    {
	char	*target;
	char	*linkname;
    } *uap = (struct a *)u.u_ap;
    struct uio uio;
    struct iovec iov;
    char c;

    cp = uap->target;
    len = 0;
    while (c = fubyte(cp))
    {
	if (c < 0)
	{
	    error = EFAULT;
	    goto out;
	}
	cp++;
	len++;
    }
    rmsg.rmsg_P_code = RFST_SYMLINK;
    rmsg.rmsg_P_mbz  = 0;
    rmsg.rmsg_P_len1 = len;
    len = rfsNameLength(nip);
    if (len < 0)
	return(NULL);
    rmsg.rmsg_P_len2 = len;
    rmsg.rmsg_P_s_param = 0;
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, sizeof (rmsg.rmsg_header)))
	goto fail;
    iov.iov_base = uap->target;
    iov.iov_len = rmsg.rmsg_P_len1;
    uio.uio_iov = &iov;
    uio.uio_iovcnt = 1;
    uio.uio_resid = rmsg.rmsg_P_len1;
    uio.uio_segflg = UIO_USERSPACE;
    error = rfsUIOSend(rcbp, &uio);
    if (error)
	goto fail;
    if (error = rfsSendString(rcbp, nip->ni_dirp, rmsg.rmsg_P_len2))
	goto fail;
    if (error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), RFST_SYMLINK))
	goto fail;
    error = rmsg.rmsg_errno;
    rfsUnLock(rcbp);

out:
    u.u_error = error;
    return(NULL);

fail:
    rfsError(rcbp);
    goto out;
}



/*
 *  rfs_sysnamecall - common protocol handling for system calls on a name
 *
 *  rcbp = remote connection
 *
 *  Currently handles: access(), chdir(), chmod(), chown(), chroot(), mkdir(), rmdir(),
 *  unlink(), utime(), utimes().
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 *
 *  TODO:  merge common handling for other calls.
 */

struct inode *
rfs_sysnamecall(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    struct rfsMsg rmsg;
    register u_int mlen;
    register int len;
    int code = u.u_rfscode;
    int error;

    rmsg.rmsg_M_code = code;
    rmsg.rmsg_M_mbz = 0;
    len = rfsNameLength(nip);
    if (len < 0)
	return(NULL);
    rmsg.rmsg_M_len = len;
    switch(code)
    {
        case RFST_CHOWN:
        case RFST_MKNOD:
	{
	    mlen = 0;
	    rmsg.rmsg_M_s_param1 = u.u_ap[1];
	    rmsg.rmsg_M_s_param2 = u.u_ap[2];
	    break;
	}
        case RFST_MKDIR:
        case RFST_ACCESS:
        case RFST_CHMOD:
	case RFST_TRUNCATE:
	{
	    mlen = 0;
	    rmsg.rmsg_N_l_param = u.u_ap[1];
	    break;
	}
	case RFST_CHDIR:
	case RFST_CHROOT:
	case RFST_RMDIR:
	case RFST_UNLINK:
	{
	    mlen = 0;
	    rmsg.rmsg_N_l_param = 0;
	    break;
	}
	case RFST_UTIME:
	{
	    mlen = sizeof(rmsg.rmsg_M_time);
	    goto common;
	}
	case RFST_UTIMES:
	{
	    mlen = sizeof(rmsg.rmsg_M_tv);
	    goto common;
	}
	common:
	{
	    u.u_error = copyin((caddr_t)u.u_ap[1], (caddr_t)&rmsg.rmsg_body, mlen);
	    if (u.u_error)
		return(NULL);
	    rmsg.rmsg_N_l_param = 0;
	    break;
	}
        default:
	{
	    panic("rfs_sysnamecall");
	    break;
	}
    }
    mlen += sizeof(rmsg.rmsg_header);
    if ((rcbp->rcb_cmask != u.u_cmask) && (code == RFST_MKDIR || code == RFST_MKNOD))
    {
	error = rfsUmask(rcbp);
	if (error)
	    goto fail;
    }
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, mlen))
	goto fail;
    if (error = rfsSendString(rcbp, nip->ni_dirp, rmsg.rmsg_M_len))
	goto fail;
    if (error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), code))
	goto fail;
    rfsUnLock(rcbp);
    u.u_error = rmsg.rmsg_errno;
    return(NULL);

fail:
    rfsError(rcbp);
    u.u_error = error;
    return(NULL);
}



/*
 *  rfs_sysnamescall - common protocol handling for system calls on two names
 *
 *  rcbp = remote connection
 *
 *  Currently handles: link(), rename().
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 */

struct inode *
rfs_sysnamescall(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    struct inode *ip;
    NAME_LOOKUP_DECL;
    struct rfsMsg rmsg;
    register int len;
    int code = u.u_rfscode;
    int error;

    /*
     *  Each call on namei will increment the u_rfsncnt variable.  We key on
     *  this count to decide what stage of the system call we are in (since we
     *  could be called here from namei() for each name).  On a count of only
     *  1, we transferred here from namei() because the first name parameter
     *  was remote.  In this case, we bump the count variable to indicate this
     *  and use namei() on the second parameter to verify whether or not it is
     *  also remote.  If we are called back here recursively because the second
     *  name parameter is also remote, the count will be 3.  In this case, we
     *  simply return the remote inode (as the value of the namei() call made
     *  with a count of 1).  On a count of 2, only the second name parameter
     *  was remote and since the first was not (or we would have been called
     *  for it also) this is just like a local "cross-device link" error.
     */
    switch (u.u_rfsncnt)
    {
	case 3:
	{
	    LOCK_INODE(rcbp->rcb_ip);
	    INCR_INODE(rcbp->rcb_ip);
	    return(rcbp->rcb_ip);
	}
	case 2:
		u.u_error = EXDEV;
		return(NULL);
	default:
	{
	    u.u_error = EXDEV;
	    return(NULL);
	}
	case 1:
	    break;
    }

    /*
     *  Main path with count of 1.
     *
     *  If we get here, then the first name parameter was remote.  Save its
     *  trailing part since we are about to destroy the pointer and lookup the
     *  second name parameter.  We use a new namei data structure since the
     *  one in the U area is still in use by the prior call.  We also need to
     *  prevent namei() from releasing its buffer when it returns to us (below)
     *  in case the network protocol code forces us to block (and potentially
     *  allows another call on namei() to reuse the same buffer before we
     *  finish with it).  We will release it ourselves before exiting.  If this
     *  lookup succeeds, it must yield the same remote inode as did the first,
     *  otherwise we have another cross-device/cross-system link case.
     */
    u.u_rfsncnt++;
    NAME_LOOKUP((char *)u.u_ap[1], ip);
    if (ip != rcbp->rcb_ip)
    {
	error = EXDEV;
	if (ip)
	    FINISH_WITH_INODE(ip);
	goto out;
    }
    FINISH_WITH_INODE(ip);
    rmsg.rmsg_P_code = code;
    rmsg.rmsg_P_mbz = 0;
    len = NAME_LOOKUP_LENGTH();
    if (len < 0)
	goto fault;
    rmsg.rmsg_P_len2 = len;
    len = rfsNameLength(nip);
    if (len < 0)
	goto fault;
    rmsg.rmsg_P_len1 = len;
    rmsg.rmsg_P_s_param = 0;
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, sizeof(rmsg.rmsg_header)))
	goto fail;
    if (error = rfsSendString(rcbp, nip->ni_dirp, rmsg.rmsg_P_len1))
	goto fail;
    if (error = rfsSendString(rcbp, NAME_LOOKUP_PATH, rmsg.rmsg_P_len2))
	goto fail;
    if (error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), code))
	goto fail;
    rfsUnLock(rcbp);
    error = rmsg.rmsg_errno;

out:
    u.u_error = error;

fault:
    NAME_LOOKUP_FREE();
    return(NULL);

fail:
    rfsError(rcbp);
    goto out;
}



/*
 *  rfsUmask - send a umask message on connection.
 *
 *  rcbp = remote connection block
 *
 *  Send a UMASK message on the connection to update the mask in the
 *  remote server.
 */

rfsUmask(rcbp)
    register struct rfsConnectionBlock *rcbp;
{
    struct rfsMsg rmsg;
    int error;

    /*
     *  Send a UMASK message.
     */
    rmsg.rmsg_Z_code = RFST_UMASK;
    rmsg.rmsg_Z_mbz = 0;
    rmsg.rmsg_Z_s_param = 0;
    rmsg.rmsg_Z_l_param = u.u_cmask;
    rfsLock(rcbp);
    error = rfsSend(rcbp, &rmsg, sizeof(rmsg.rmsg_header));
    if (error)
	rcbp->rcb_cmask = -1;
    else
	rcbp->rcb_cmask = u.u_cmask;
    rfsUnLock(rcbp);
    return(error);
}



/*
 *  rfs_newproc() - remote fork() call hook (parent context)
 *
 *  p       = proc table entry of new process
 *  isvfork = vfork flag (currently unused)
 *
 *  This routine is called from the parent process context when a new process
 *  is being created.  It checks the state of the parent for any remote
 *  connections that must be duplicated for the child process in order to
 *  preserve the necessary state across the fork() call.  It also replicates
 *  any remote identity record associated with the process.
 */

rfs_newproc(p, isvfork)
    struct proc *p;
{
    register struct rfsProcessEntry *rpep = rfsCurrentProcessEntry;
    register struct rfsProcessEntry *crpep = &rfsProcessTable[p-proc];
    register struct rfsConnectionQueue *rcbqp = &(rpep->rpe_rcbq);
    register struct rfsConnectionBlock *rcbp;
    register int i;

#ifdef	lint
    if (isvfork)
	;
#endif	lint

    /*
     *  Erase any pending translation buffer in child.
     */
    crpep->rpe_bufp = NULL;

    /*
     *  Preserve current control mode.
     */
    crpep->rpe_rw = rpep->rpe_rw;

    /*
     *  Preserve any process state information in child process.
     */
    if (rpep->rpe_rwp) 
    {
	rfsIncrCheckWho(rpep->rpe_rwp);
	crpep->rpe_rwp = rpep->rpe_rwp;
    }
    crpep->rpe_rw = rpep->rpe_rw;
    /*
     *  The call on rfsFork() below may end up removing a block from the
     *  process connection block queue which would disturb a conventional link
     *  traversal.  Thus, make a special test for a non-empty loop at the
     *  beginning and decide before invoking any network code what the next
     *  block and last status should be.
     */
    rcbp = rfsConnectionFirst(rcbqp);
    if (!rfsConnectionLast(rcbqp, rcbp))
    {
	int last;

	for (last=0;last;)
	{
	    struct rfsConnectionBlock *nrcbp = rfsConnectionNext(rcbp);

	    last = rfsConnectionLast(rcbqp, nrcbp);
	    if (rcbp->rcb_rwp)
	    {
		rfsIncrCheck(rcbp);
		rfsFork(rcbp, p);
	    }
	    rcbp = nrcbp;
	}
    }

   /*
    *  Preserve any open remote files.
    */
    for (i = 0; i <= u.u_lastfile; i++)
    {
	register struct file *fp;

	fp = u.u_ofile[i];
	if (fp == NULL || fp->f_type != DTYPE_RFSINO)
	    continue;
	rcbp = ((struct rfsFileEntry *)(fp->f_data))->rfe_rcbp;
	rfsIncrCheck(rcbp);
	rfsFork(rcbp, p);
    }

    /*
     *  Check for a remote current directory.
     */
    if (u.u_rfs&URFS_CDIR)
	rfsForkDir(u.u_cdir, p);

    /*
     *  Check for a remote root directory.  We can re-use the connection to the
     *  new server created above if the root and current directory are remote
     *  in the same place.
     */
    if (u.u_rfs&URFS_RDIR)
	rfsForkDir(u.u_rdir, p);
}



/*
 *  rfsForkDir - duplicate a remote directory connection for a new process
 *
 *  ip = current remote connection inode pointer
 *  p  = new process top receive the connection
 *
 *  Obtain the remote connection block for the directory and duplicate its
 *  asoociated connection.
 */

void
rfsForkDir(ip, p)
    struct inode *ip;
    struct proc *p;
{
    register struct rfsConnectionBlock *rcbp;

    /*
     *  Obtain the remote control block for the connection associated with this
     *  directory.  The inode must be locked and incremented since it will be
     *  released when the connection is found.
     */
    LOCK_INODE(ip);
    INCR_INODE(ip);
    if ((rcbp = rfsAttach(ip)) == NULL)
	return;
    rfsFork(rcbp, p);
}



/*
 *  rfsFork - duplicate a remote connection for a new process
 *
 *  rcbp = current remote connection
 *  p    = new process to receive the connection
 *
 *  Establish a connection to a new remote server for the new process.
 *  If this fails, the new process will be left without the remote connection
 *  in its process table and one will be established (potentially with loss
 *  of state) when it first goes remote.
 */

void
rfsFork(rcbp, p)
register struct rfsConnectionBlock *rcbp;
struct proc *p;
{
    register struct rfsProcessEntry *rpep = &rfsProcessTable[p-proc];
    register struct rfsConnectionQueue *frcbqp = &(rpep->rpe_rcbq);
    register struct rfsConnectionBlock *frcbp;
    struct rfsMsg rmsg;

    rfs_printf2(RFSD_S_TRACEIN, "<Fork rcb=%X\n", rcbp);
    /*
     *  If we already have a connection to this server, avoid creating another.
     */
    for (frcbp = rfsConnectionFirst(frcbqp);
	 !rfsConnectionLast(frcbqp, frcbp);
	 frcbp = rfsConnectionNext(frcbp))
    {
	if (frcbp->rcb_ip == rcbp->rcb_ip)
	    goto done;
    }
    frcbp = 0;

    /*
     *  Allocate a new connection block for the child process now since if we
     *  can't get one, there is no point in going to the net.
     */
    frcbp = rfsCopy(rcbp);
    if (frcbp == NULL)
    {
	rfs_printf1(RFSD_S_TRACEOUT, "*Fork (Copy)\n");
	goto done;
    }

    /*
     *  If we don't currently have a connection, just save the copied
     *  connection.
     */
    if (rcbp->rcb_so == NULL)
	goto save;

    /*
     *  Establish a listening connection for the new server.  Since we specify a
     *  "passive" connection, it will complete asynchronously and hopefully be
     *  ready by the time we actually need it for the first remote operation in
     *  the new process.
     */
    if (rfsEstablish(frcbp, frcbp->rcb_addr, 0, 0, 0, RFSMAXRETRY))
	goto out;

    /*
     *  Send a FORK message containing the port to connect back on.
     */
    rmsg.rmsg_Z_code = RFST_FORK;
    rmsg.rmsg_Z_mbz = 0;
    rmsg.rmsg_Z_s_param = frcbp->rcb_lport;
    rmsg.rmsg_Z_l_param = p->p_pid;
    rfsLock(rcbp);
    if (rfsSend(rcbp, &rmsg, sizeof(rmsg.rmsg_header)))
	goto fail;
    rfsUnLock(rcbp);

    /*
     *  Save the new listening connection in the process table.
     */
save:
    rfsEnQueueConnection(&rpep->rpe_rcbq, frcbp);

done:
    rfsDetach(rcbp);
    rfs_printf1(RFSD_S_TRACEOUT, ">Fork\n");
    return;

fail:
    rfsError(rcbp);
out:
    rfsDetach(frcbp);
    goto done;
}



/*
 *  rfs_fork() - remote fork() call hook (child context)
 *
 *  This routine is called from the child process context after it has been
 *  created.  It scans the open file table to create new remote file entry
 *  pointers for any files shared between it and its parent.  Normally an open
 *  file which is shared between multiple processes will refer to the same file
 *  table pointer in each process.  This is still true for a remote file,
 *  however, only on the remote system where the file is actually open (and
 *  shared between the original server and any of its children).  On the local
 *  system, we cannot allow the same file table pointer to be used across
 *  processes for two reasons.  First, each local process currently
 *  communicates with the remote server on a separate connection which is
 *  referenced through the file table.  Second, there is currently an
 *  independent remote server for each local client and each needs to see a
 *  close() operation on the file when the local process finishes with it (in
 *  order to free its file descriptor) and this won't happen if other processes
 *  reference the same file table entry.  Thus, the following code is
 *  unfortunately complicated for now.
 */

rfs_fork()
{
    register struct rfsProcessEntry *rpep = rfsCurrentProcessEntry;
    register struct rfsConnectionQueue *rcbqp = &(rpep->rpe_rcbq);
    register int i;

    for (i = 0; i <= u.u_lastfile; i++)
    {
	register struct rfsConnectionBlock *rcbp;
	register struct file *fp;
	struct rfsFileEntry *frfep;
	struct inode *ip;
	int desc;
	int flag;
	off_t offset;
	char pofile;

	fp = u.u_ofile[i];
	if (fp == NULL || fp->f_type != DTYPE_RFSINO)
	    continue;

	/*
	 *  Save the necessary state from the file table entry that we will
	 *  need to replicate in the new entry and then release the current
	 *  entry.  If the replication code succeeds below, the current entry
	 *  will be replaced by a new entry with all the relevant information
	 *  duplicated but associated with a new connection.  If it fails, the
	 *  entry will refer to a closed file which is probably the best way to
	 *  indicate to the process that it has lost its remote file.
 	 *
	 *  Normally, the call on closef() will not actually do anything but
	 *  decrement the file table reference count since the file table entry
	 *  will in all probability still be in use in the parent process.  If
	 *  we have been unlucky enough that the parent managed to run and
	 *  close the file before the child could reallocate a new file table
	 *  entry, we might actually hold the last reference and the close
	 *  could initiate a CLOSE message on the connection.  This should
	 *  probably work since all access to connections is synchronized but
	 *  we still note when it happens in case it occurs in practice
	 *  often enough to warrant a better solution.
	 */
	pofile = u.u_pofile[i];
	frfep  = (struct rfsFileEntry *)(fp->f_data);
	flag   = fp->f_flag;
	offset = fp->f_offset;
	desc   = frfep->rfe_desc;
	ip     = frfep->rfe_rcbp->rcb_ip;
	u.u_ofile[i]  = NULL;
	u.u_pofile[i] = 0;
	if (fp->f_count == 1)
	    printf("rfs_fork: f_count==1");
	closef(fp);

	/*
	 *  Scan the remote connection list for this process, looking for a
	 *  connection to the host which matches the current file.  The target
	 *  inode pointer may no longer refer to the same inode as when it was
	 *  set above (if for some reason the current process didn't get a
	 *  connection replicated to that host in rfs_newproc() and the
	 *  unlikely closef() case occurs above), however, this will not matter
	 *  since it will be different from any inodes for connections that
	 *  were replicated by rfs_newproc().
	 */
	for (rcbp = rfsConnectionFirst(rcbqp);
	     !rfsConnectionLast(rcbqp, rcbp);
	     rcbp = rfsConnectionNext(rcbp))
	{
	    if (rcbp->rcb_ip == ip)
	    {
		register struct rfsFileEntry *rfep;

		/*
		 *  Allocate a new remote file entry and file table entry for
		 *  the file to be replicated.  We are guaranteed that falloc()
		 *  will not fail due to lack of file descriptors since we
		 *  closed one above (although it may still fail due to lack of
		 *  file table slots).  If it fails, it will have set an error
		 *  number which we must undo so that the fork() doesn't appear
		 *  to have failed.  If it succeeds, it will have clobbered the
		 *  first return value with the newly allocated file descriptor
		 *  which we remember before restoring the original value.
		 *  Finally, replicate all the saved state in the new file
		 *  table entry and move the file descriptor to the correct
		 *  slot if necessary.
		 */
		rfep = rfsFileAllocate();
		if (rfep)
		{
		    int rval1;
		    int j;

		    rval1 = u.u_r.r_val1;
		    fp = falloc();
		    j = u.u_r.r_val1;
		    u.u_r.r_val1 = rval1;
		    if (fp != NULL)
		    {
			extern struct fileops rfsops;

			u.u_pofile[j]  = pofile;
			rfep->rfe_desc = desc;
			rfep->rfe_rcbp = rcbp;
			rfsIncrCheck(rcbp);
			fp->f_flag   = flag;
			fp->f_type   = DTYPE_RFSINO;
			fp->f_ops    = &rfsops;
			fp->f_offset = offset;
			fp->f_data   = (caddr_t)rfep;
			if (i != j)
			{
			    dupit(i, fp, u.u_pofile[j]);
			    u.u_ofile[j] = 0;
			    u.u_pofile[j] = 0;
			    closef(fp);
			}
		    }
		    else
		    {
			rfsFileFree(rfep);
			u.u_error = 0;
		    }
		}
	    }
	}
    }
}
